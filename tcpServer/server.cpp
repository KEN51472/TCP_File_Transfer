#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#define SERV_PORT 9877
#define LISTENQ 1024
#define	SA struct sockaddr

class Socket
{
public:
    int sock;
    Socket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    } 
    ~Socket() {
        close(sock);
        printf("socket closed success...\n");
    };
};

class Monitor
{   
public:
    int listenret;
    Monitor(int sockret) {
        listenret = listen(sockret, LISTENQ);
    }   
    ~Monitor() {
        close(listenret);
        printf("listenret closed success...\n");
    };
};

class Link
{
public:
    int accret;
    Link() {};
    void setLink(int sockret, sockaddr *cliaddr, socklen_t clilen){
        accret = accept(sockret, (SA *)&cliaddr, &clilen);
    }
    ~Link() {
        close(accret);
        printf("accret closed success...\n");
    };   
};

class ReadFile
{
public:
    int fd;  
    ReadFile(char *filepath) {
        fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0666);
    } 
    ~ReadFile() {
        close(fd);
        printf("fd closed success...\n");
    };
};

int main(int argc, char **argv) {
    int ret;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    Socket socket;
    int sockret = socket.sock;
    if (socket.sock == -1) {
        printf("Create socket error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Create socket success...\n");
   
    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    ret = bind((socket.sock), (SA *)&servaddr, sizeof(servaddr)); 
    if (ret == -1) {
        printf("Bind error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Binding the port success...\n");

    Monitor mon(sockret);
    if (mon.listenret == -1) {
        printf("Listening error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Listening success...\n");

    printf("Waiting for client connection to complete...\n");
    for (;;) {   
        clilen = sizeof(cliaddr); 
        Link link;
        link.setLink(sockret, (SA *)&cliaddr, clilen);
        if (link.accret == -1) {
            printf("Accept error...\nerrno is: %d\n", errno);
            return -1;
        }
        printf("Connect success...\n");
        
        //concurrent server
        if ((childpid = fork()) == 0) {
            close(mon.listenret);
            char file_len[16] = {0};   
            char file_name[128] = {0}; 
            char buf[4096] = {0};      
            char filepath[8192] = {0};
           
            int readn = read(link.accret, buf, sizeof(buf));  
            if (readn == -1) {
                printf("Using function read error...\nerrno is: %d\n", errno);
                return -1;
            }            
            //Get the file size (copy the first n characters of the string)                
            strncpy(file_len, buf, sizeof(file_len));                      
            //Get the file name
            strncpy(file_name, buf + sizeof(file_len), sizeof(file_name)); 
            printf("Ready to receive...... file name:[%s] file size:[%s] \n", file_name, file_len);
            
            sprintf(buf, "recv-%s", file_name);                  
            sprintf(filepath, "/home/code/tcp_download/%s", buf); 
            //mkdir file
            ReadFile rf(filepath);
            if (rf.fd == -1) {
                printf("Open error...\nerrno is: %d\n", errno);
                return -1;
            }
            //file size
            int file_size = atoi(file_len);            
            
            int received = 0;         
            while (1) {
                memset(buf, 0, 1024); 
                int rn = read(link.accret, buf, sizeof(buf));
                if (file_size == 0) {   
                    printf("Empty file transfer...\n");
                    break;
                }         
                if (rn == 0) {
                    printf("Transfer [%s] success...\n", file_name);
                    break;
                }
                if (rn < 0) {
                    printf("Function read error...\nerrno is: %d\n", errno);
                    return -1;
                }
                int left = rn;  
                while (left > 0) {
                    int wn = write(rf.fd, buf, left);
                    if (wn == -1) {
                        printf("Using function write error...\nerrno is: %d\n", errno);
                        return -1;
                    } 
                    left -= wn;
                    received += wn;
                    printf("received:%d\n", received);
                    if (left == 0) {
                        break;
                    }
                    printf("missing write size :%d\nrewrite:%d\n", left, wn); 
                }    
                printf("Uploading ... %.2f%%\n", (float)received /file_size * 100);
            }
            return 0;
        }
    }
}
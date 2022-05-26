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

int main(int argc, char **argv) {
    int sock, listenret, connret, ret;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock == -1) {
        printf("Create socket error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Create socket success...\n");
   
    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    ret = bind((sock), (SA *)&servaddr, sizeof(servaddr)); 
    if (ret == -1) {
        printf("Bind error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Binding the port success...\n");

    listenret = listen(sock, LISTENQ); 
    if (listenret == -1) {
        printf("Listening error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Listening success...\n");

    printf("Waiting for client connection to complete...\n");
    for (;;) { 
        clilen = sizeof(cliaddr);
        connret = accept(sock, (SA *)&cliaddr, &clilen); 
        if (connret == -1) {
            printf("Accept error...\nerrno is: %d\n", errno);
            return -1;
        }
        printf("Connect success...\n");
        
        //concurrent server
        if ((childpid = fork()) == 0) {
            close(listenret);
            char file_len[16] = {0};   
            char file_name[128] = {0}; 
            char buf[1024] = {0};      
            char filepath[2048] = {0};
           
            int readn = read(connret, buf, sizeof(buf));  
            if (readn == -1) {
                printf("Using function read error...\nerrno is: %d\n", errno);
                close(connret);
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
            int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                printf("Open error...\nerrno is: %d\n", errno);
                close(connret);
                return -1;
            }
            //file size
            int file_size = atoi(file_len);            
            
            int received = 0;         
            while (1) {
                memset(buf, 0, 1024); 
                int rn = read(connret, buf, sizeof(buf));
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
                    close(fd);
                    close(connret);
                    return -1;
                }
                int left = rn;  
                while (left > 0) {
                    int wn = write(fd, buf, left);
                    if (wn == -1) {
                        printf("Using function write error...\nerrno is: %d\n", errno);
                        close(fd);
                        close(sock);
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
            close(fd);
            return 0;
        }

        close(connret);
    }
}
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define SERV_PORT 9877
#define LISTENQ 1024
#define	SA	struct sockaddr

int main(int argc, char **argv) {
    int listenret, connret,sockret,bindret;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    //Create a socket and bind the port of the server
    sockret = socket(AF_INET, SOCK_STREAM, 0); 
    if(sockret == -1) {
        printf("Create socket error...\n");
        return -1;
    }
    printf("Create socket success...\n");
   
    memset(&servaddr, 0,sizeof(servaddr)); 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    bindret = bind((listenret), (SA *)&servaddr, sizeof(servaddr)); 
    if(bindret == -1) {
        printf("Bind error...\n");
        return -1;
    }
    printf("Binding the port success...\n");

    listenret = listen(listenret, LISTENQ); 
    if(listenret == -1) {
        printf("Listening error...\n");
        return -1;
    }
    printf("Listening success...\n");

    printf("Waiting for client connection to complete...\n");
    for (;;) { 
        //waiting for connect
        clilen = sizeof(cliaddr);
        
        //accept success 
        connret = accept(listenret, (SA *)&cliaddr, &clilen); 
        if(connret == -1) {
            printf("Accept error...\n");
            return -1;
        }
        printf("Connect success...\n");
        
        //concurrent server
        if ((childpid = fork()) == 0) {
            close(listenret);
            char file_len[16] = {0};   
            char file_name[128] = {0}; 
            //data buffer
            char buf[1024] = {0};      
            char filepath[2048] = {0};
           
            //Read file size and file name
            //Read everything in accept into the memory pointed to by the buf pointer
            int readn = read(connret, buf, sizeof(buf));  
            if(readn == -1) {
                printf("Using function read error...\n");
                return -1;
            }            
            //Get the file size (copy the first n characters of the string)                
            strncpy(file_len, buf, sizeof(file_len));                      
            //Get the file name
            strncpy(file_name, buf + sizeof(file_len), sizeof(file_name)); 
            printf("Ready to receive...... file name:[%s] file size:[%s] \n", file_name, file_len);
            
            //new file name 
            //Write formatted data to a string
            sprintf(buf, "recv-%s", file_name);                  
            //Specify where to receive files
            sprintf(filepath, "/home/code/tcp_download/%s", buf); 
            //mkdir file
            int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0666);
            //file size
            int size = atoi(file_len); 
            
            //Record the number of bytes written
            int wrote = 0;         
            //accept
            while (1) {
                memset(buf,0,1024); 
                int readn = read(connret, buf, sizeof(buf));
                if (readn = 0) {
                    printf("\n [recv-%s] trans finished...\n", file_name);
                    break;
                }else if (readn < 0) {
                    printf("trans error...\n");
                    break;
                }

                int writen = write(fd, buf, readn);
                if(writen == -1) {
                    printf("Using function write error...\n");
                    return -1;
                } 
                wrote += readn; 
                //Dynamic output receive input
                printf("Uploading %.2f%% \n", (float)wrote / size * 100);
            }
            return 0;
        }

        close(connret);
    }
}
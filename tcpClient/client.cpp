#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERV_PORT 9877

int main(int argc, char **argv) {
    int sockfd,connfd;
    struct sockaddr_in servaddr;
    if (argc != 2) {
        return 0;
    }
    //Create a socket, initialize the socket address structure
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        printf("Create socket error...\n");
        return -1;
    }
    printf("Create socket success...\n");
    memset(&servaddr, 0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    //Convert the string pointed to by the argv pointer, and store the binary result through the servaddr.sin_addr pointer, return 1 if successful, and return 0 if it fails.
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr); 
    //Connect to server
    connfd = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0; 
    if(connfd == -1) {
        printf("Connect error...\n");
        return -1;
    }

    char file_path[128] = {0};  
    char file_info[2048] = {0}; 
    char buf[1024] = {0};
    printf("Please enter the path of the file to be transferred: ");
    scanf("%s", file_path);
    //Get filename from filepath
    char file_name[128] = {0};
    strncpy(file_name, basename(file_path), sizeof(file_name));
    //Open the file
    int fd = open(file_path, O_RDWR);
    if (fd == -1) {
        printf("Open [%s] error...\n", file_path);
        return -1;
    }
    //Calculate file size
    int len = lseek(fd, 0, SEEK_END);
    //Offset the file cursor to the beginning of the file
    lseek(fd, 0, SEEK_SET);
    if(sizeof(len)>sizeof(file_info)) {
        printf("File is too large to transfer...\n");
        return -1;
    }
    //Store file size and file name in file_info
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
    // Tell server the name of the file to be uploaded
    int writefd = write(sockfd, file_info, 144);
    if(writefd == -1) {
        printf("using function write error...\n");
        return -1;
    }
    int sent = 0; 
    while (1) {
        memset(buf, 0,sizeof(buf));
        //Read data
        int ret = read(fd, buf, sizeof(buf));
        if (ret <= 0) {
            printf("Transfer [%s] success...\n", file_name);
            break;
        }
        //Send data
        int writefd = write(sockfd, buf, ret);
        if(writefd == -1) {
        printf("Using function write error...\n");
        return -1;
    }   
        sent += ret; 
        printf("Uploading ... %.2f%%\n", (float)sent / len * 100);
    }
    
    close(fd);
    return 0;
}
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
    int connret, sock;
    struct sockaddr_in servaddr;
    
    //Create a socket, initialize the socket address structure
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Create socket error...\n");
        return -1;
    }
    printf("Create socket success...\n");
    
    memset(&servaddr, 0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    /*Convert the string pointed to by the argv pointer, and store 
    the binary result through the servaddr.sin_addr pointer, 
    return 1 if successful, and return 0 if it fails.*/
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); 
    
    //Connect to server
    connret = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
    if (connret < 0) {
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
    int fd = open(file_path, O_RDWR);
    if (fd == 0) {
        printf("Open [%s] success...\n",file_path);
    }else if (fd == -1) {
        printf("Open [%s] error...\n", file_path);
        close(fd);
        return -1;
    }
    
    //Calculate file size
    int len = lseek(fd, 0, SEEK_END);
    //Offset the file cursor to the beginning of the file
    lseek(fd, 0, SEEK_SET);
    if (sizeof(len) > sizeof(file_info)) {
        printf("File is too large to transfer...\n");
        close(fd);
        return -1;
    }
    //Store file size and file name in file_info
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
    // Tell server the name of the file to be uploaded
    int writen = write(sock, file_info, 1024);
    
    int sent = 0; 
    while (1) {
        memset(buf, 0, sizeof(buf));
        int readn = read(fd, buf, sizeof(buf));
        if (readn == 0) {
            printf("Transfer [%s] success...\n", file_name);
            break;
        }else if (readn < 0) {
            printf("Function read error...\n");
            close(fd);
            return -1;
        }else{
            printf("read:%d\n",readn);
        }
        
        int writen = write(sock, buf, readn);
        if (writen > 0 && sizeof(writen) < sizeof(readn)) {
            printf("The disk is full, or the file length limit for a given process has been exceeded...\n");
            close(fd);
            return -1;
        }else if (writen == -1) {
            printf("Using function write error...\n");
            close(fd);
            return -1;
        }else {
            printf("write:%d\n",writen);
        } 
        sent += writen; 
        printf("Uploading ... %.2f%%\n", (float)sent / len * 100);
    }
    
    close(fd);
    return 0;
}

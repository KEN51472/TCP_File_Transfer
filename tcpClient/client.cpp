#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SERV_PORT 9877

int main(int argc, char **argv) {
    int ret, sock;
    struct sockaddr_in servaddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Create socket error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Create socket success...\n");
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); 
    
    ret = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
    if (ret < 0) {
        printf("Connect error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Connect to server success...\n");

    char file_path[128] = {0};  
    char file_info[2048] = {0}; 
    char buf[4096] = {0};
    
    printf("Please enter the path of the file to be transferred: ");
    scanf("%s", file_path);
    
    char file_name[128] = {0};
    strncpy(file_name, basename(file_path), sizeof(file_name));
    int fd = open(file_path, O_RDWR);
    if (fd == -1) {
        printf("Open [%s] error...\nerrno is: %d\n", file_path, errno);
        return -1;
    }
    printf("Open [%s] success...\n", file_path);
    
    int len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    printf("file_size : %d\n", len);
    //Store file size and file name in file_info
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
    // Tell server the name of the file to be uploaded
    int writeinfo = write(sock, file_info, 1024);
    if (writeinfo == -1) {
        printf("Using function write error...\nerrno is: %d\n", errno);
        close(fd);
        close(sock);
        return -1;
    }
    
    int sent = 0; 
    while (1) {
        memset(buf, 0, sizeof(buf));
        int rn = read(fd, buf, sizeof(buf));
        if (rn == 0) {
            printf("Transfer [%s] success...\n", file_name);
            break;
        }    
        if (rn < 0) {
            printf("Function read error...\nerrno is: %d\n", errno);
            close(fd);
            return -1;
        }
        
        int left = rn;   
        while (left > 0) {
            int wn = write(sock, buf, left);          
            if (wn == -1) {
                printf("Using function write error...\nerrno is: %d\n", errno);
                close(fd);
                close(sock);
                return -1;
            } 
            left -= wn;
            sent += wn;
            if (left == 0) {
                break;
            }
            printf("missing write size :%d\nrewrite:%d\n", left, wn); 
        }    
        printf("Uploading ... %.2f%%\n", (float)sent / len * 100);
    }
    
    close(fd);
    return 0;
}

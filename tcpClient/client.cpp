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

class Socket
{
public:
    int sock;
    Socket() {
        sock = socket(AF_INET, SOCK_STREAM, 0);
    } 
    ~Socket() {
        if(sock > 0) {
            close(sock);
            printf("socket closed success...\n");
        }     
    };
};

class ReadFile
{
public:
    int fd;  
    ReadFile(char *file_path) {
        fd = open(file_path, O_RDWR);
    } 
    ~ReadFile() {
        if (fd > 0) {
            close(fd);
            printf("fd closed success...\n");
        }
    };
};

int main(int argc, char **argv) {
    int ret;
    struct sockaddr_in servaddr;

    Socket socket;
    if (socket.sock == -1) {
        printf("Create socket error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Create socket success...\n");
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); 
    
    ret = connect(socket.sock, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
    if (ret < 0) {
        printf("Connect error...\nerrno is: %d\n", errno);
        return -1;
    }
    printf("Connect to server success...\n");
    
    char file_info[2048] = {0}; 
    char buf[65536] = {0};
    char file_path[128] = {0};
    printf("Please enter the path of the file to be transferred: ");
    scanf("%s", file_path); 
    ReadFile rf(file_path); 
    char file_name[128] = {0};
    strncpy(file_name, basename(file_path), sizeof(file_name));
    if (rf.fd == -1) {
        printf("Open [%s] error...\nerrno is: %d\n", file_path, errno);
        return -1;
    }
    printf("Open [%s] success...\n", file_path);
    
    int len = lseek(rf.fd, 0, SEEK_END);
    lseek(rf.fd, 0, SEEK_SET);
    printf("file_size : %d\n", len);
    //Store file size and file name in file_info
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
    // Tell server the name of the file to be uploaded
    int writeinfo = write(socket.sock, file_info, 1024);
    if (writeinfo == -1) {
        printf("Using function write error...\nerrno is: %d\n", errno);
        return -1;
    }
    
    int sent = 0; 
    while (1) {
        memset(buf, 0, sizeof(buf));
        int rn = read(rf.fd, buf, sizeof(buf));
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
            int wn = write(socket.sock, buf, left);          
            if (wn == -1) {
                printf("Using function write error...\nerrno is: %d\n", errno);
                return -1;
            } 
            left -= wn;
            sent += wn;
            printf("sent:%d\n",sent);
            if (left == 0) {
                break;
            }
            printf("missing write size :%d\nrewrite:%d\n", left, wn); 
        }    
        printf("Uploading ... %.2f%%\n", (float)sent / len * 100);
    }
    return 0;
}

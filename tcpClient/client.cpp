#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wrapper.h>

#define SERV_PORT 9877

int main(int argc, char **argv) {
    int ret, sock, fd;
    struct sockaddr_in servaddr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    DesWrapper socket_wrapper(sock);
    if (socket_wrapper.get() == -1) {
        cout << "Create socket error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Create socket success...\t" << "descriptor : " << socket_wrapper.get() << endl;
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); 
    
    ret = connect(socket_wrapper.get(), (struct sockaddr *)&servaddr, sizeof(servaddr)); 
    if (ret < 0) {
        cout << "Connect error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Connect to server success..." << endl;
    
    char file_info[2048] = {0}; 
    char buf[65536] = {0};
    char file_path[128] = {0};
    cout << "Please enter the path of the file to be transferred: ";
    scanf("%s", file_path);  
    fd = open(file_path, O_RDWR);
    DesWrapper fd_wrapper(fd);
    if (fd_wrapper.get() == -1) {
        cout << "Open error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open success...\t" << "descriptor : " << fd_wrapper.get() << endl;
    char file_name[128] = {0};
    strncpy(file_name, basename(file_path), sizeof(file_name));
    if (fd_wrapper.get() == -1) {
        cout << "Open [" << file_path << "] error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open [" << file_path << "] success..." << endl;
    
    int len = lseek(fd_wrapper.get(), 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    cout << "file_size : " << len << endl;
    //Store file size and file name in file_info
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
    // Tell server the name of the file to be uploaded
    int writeinfo = write(socket_wrapper.get(), file_info, 1024);
    if (writeinfo == -1) {
        cout << "Using function write error...\t" << "errno : " << errno << endl;
        return -1;
    }
    
    int sent = 0; 
    while (1) {
        memset(buf, 0, sizeof(buf));
        int rn = read(fd_wrapper.get(), buf, sizeof(buf));
        if (rn == 0) {
            cout << "Transfer [" << file_name << "] success..." << endl;
            break;
        }    
        if (rn < 0) {
            cout << "Function read error...\t" << "errno : " << errno << endl;
            return -1;
        }
        
        int left = rn;   
        while (left > 0) {
            int wn = write(socket_wrapper.get(), buf, left);          
            if (wn == -1) {
                cout << "Using function write error...\t" << "errno : " << errno << endl;
                return -1;
            } 
            left -= wn;
            sent += wn;
            cout << "sent :" << sent << endl;
            if (left == 0) {
                break;
            }
            cout << "missing write size :" << left <<"\trewrite:" << wn << endl;  
        }    
        cout << "Uploading ... " << (float)sent /len * 100 << "%" << endl;
    }
    return 0;
}

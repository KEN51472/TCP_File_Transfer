#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <thread>
#include <wrapper.h>
using namespace std;

#define SERV_PORT 9877
#define LISTENQ 1024
#define	SA struct sockaddr

int childthread(int accept_sock) {
    char file_len[16] = {0};   
    char file_name[128] = {0};
    char buf[65536] = {0};      
    char filepath[65560] = {0};

    DesWrapper accept_wrapper(accept_sock);
    int readname = read(accept_wrapper.get(), buf, 1024);  
    if (readname == -1) {
        cout << "Using function read error...\t" << "errno : " << errno << endl;
        return -1;
    }                            
    strncpy(file_len, buf, sizeof(file_len));                      
    strncpy(file_name, buf + sizeof(file_len), sizeof(file_name)); 
    int file_size = atoi(file_len);   
    cout << "Ready to receive...... file name:[" << file_name << "] file size:[" << file_len << "]" << endl;
    if (file_size == 0) {   
        cout << "Empty file transfer..." << endl;
    } 
    
    sprintf(buf, "recv-%s", file_name);                  
    sprintf(filepath, "/home/code/tcp_download/%s", buf); 
    
    int fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, 0666);
    DesWrapper fd_wrapper(fd);
    if (fd_wrapper.get() == -1) {
        cout << "Open error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open success...\t" << "descriptor : " << fd_wrapper.get() << endl;
                       
    int received = 0;            
    while (file_size != 0) {
        memset(buf, 0, sizeof(buf)); 
        int rn = read(accept_wrapper.get(), buf, sizeof(buf));
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
            int wn = write(fd_wrapper.get(), buf, left);
            if (wn == -1) {
                cout << "Using function write error...\t" << "errno : " << errno << endl;
                return -1;
            } 
            left -= wn;
            received += wn;
            cout << "received:" << received << endl;
            if (left == 0) {
                break;
            }
            cout << "missing write size :" << left <<"\trewrite:" << wn << endl; 
        }    
        cout << "Uploading ... " << (float)received /file_size * 100 << "%" << endl;
    }
    return 0;
}

int main(int argc, char **argv) {
    int ret, sock, listen_sock, accept_sock;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    DesWrapper socket_wrapper(sock);
    if (socket_wrapper.get() == -1) {
        cout << "Create socket error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Create socket success...\t" << "descriptor : " << socket_wrapper.get() << endl;
    
    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    ret = bind(sock, (SA *)&servaddr, sizeof(servaddr)); 
    if (ret == -1) {
        cout << "Bind error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Binding the port success..." << endl;

    listen_sock = listen(sock, LISTENQ);
    DesWrapper listen_wrapper(listen_sock);
    if (listen_wrapper.get() == -1) {
        cout << "Listening error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Listening success..." << endl;

    cout << "Waiting for client connection to complete..." << endl;
    while(1) { 
        clilen = sizeof(cliaddr); 
        accept_sock = accept(sock, (SA *)&cliaddr, &clilen);      
        if (accept_sock == -1) {
            cout << "Accept error...\t" << "errno : " << errno << endl;
            return -1;
        }
        cout << "Connect accept_sock " << accept_sock << " success..." << endl;    
        //concurrent server
        thread t(childthread, accept_sock);
        t.detach();                 
    }
}
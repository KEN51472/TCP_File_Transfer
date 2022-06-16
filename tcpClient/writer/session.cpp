#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include "session.h"
using namespace std;

#define SERV_PORT 9877
#define SERV_ADDR "127.0.0.1"

int Session::link() {
    struct sockaddr_in servaddr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cout << "Create socket error...\t" << "errno : " << errno << endl;
        return -1;
    }
    Session s_();
    cout << "Create socket success...\tsock: " << sock << endl;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_ADDR, &servaddr.sin_addr);

    ret = connect(sock, (struct sockaddr*)&servaddr,
                  sizeof(servaddr));
    if (ret < 0) {
        cout << "Connect error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Connect to server success..." << endl;
    return sock;
}

int Session::write_data(int sock,char *buf,int file_size) {
    int file_write = 0;
    int left = file_size;
    while (left > 0)
    {
        int wn = write(sock, buf, left); 
        if (wn == -1) {
        cout << "Using function write error...\t" << "errno : " << errno << endl;
        return -1;
        }
        left -= wn;
        file_write += wn;
        if (left == 0) {
            break;
        }
        cout << "missing write size :" << left << "\trewrite:" << wn << endl;
    }
    cout << "Uploading ... " << (float)file_write / file_size * 100 << "%" << endl;
    if (file_write = file_size) {
        cout << "Trans success!" << endl;
    }
    delete[] buf;
    return file_write;
}

int Session::write_info(int sock,int len,char *file_name)
{
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
    int writeinfo = write(sock, file_info, 1024);
    if (writeinfo == -1) {
        cout << "Using function write error...\t" << "errno : " << errno << endl;
        return -1;
    }
    return 0;

}



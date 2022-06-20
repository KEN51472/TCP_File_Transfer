#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include "session.h"
using namespace std;

#define SERV_PORT 9877
#define SERV_ADDR "127.0.0.1"

int Session::tcp_link()
{
    struct sockaddr_in servaddr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cout << "Create socket error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Create socket success...\tsock: " << sock << endl;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_ADDR, &servaddr.sin_addr);

    ret = connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (ret < 0) {
        cout << "Connect error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Connect to server success..." << endl;
    return sock;
}

int Session::do_write(char *buf,int size)
{
    int wn = write(sock, buf, size);
    return wn;
}

int Session::destroy()
{
    close(sock);
    cout << "sock " << sock << " closed success..." << endl;
    return 0;
}
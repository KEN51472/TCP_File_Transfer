#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <wrapper.h>

#define SERV_PORT 9877
#define SERV_ADDR "127.0.0.1"

int tcp_connect() {
    int ret, sock, fd;
    struct sockaddr_in servaddr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cout << "Create socket error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    DesWrapper socket_wrapper(sock);
    cout << "Create socket success...\t"
         << "descriptor : " << socket_wrapper.get() << endl;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_ADDR, &servaddr.sin_addr);

    ret = connect(socket_wrapper.get(), (struct sockaddr*)&servaddr,
                  sizeof(servaddr));
    if (ret < 0) {
        cout << "Connect error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Connect to server success..." << endl;
}

int start_write(DesWrapper socket_wrapper,char buf[],int left) {
    int wn = write(socket_wrapper.get(), buf, left);
    if (wn == -1) {
        cout << "Using function write error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
}
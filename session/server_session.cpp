#include "server_session.h"

int Server_Session::init()
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1) {
        cout << "Create socket error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    cout << "Create socket success...\tsocket:" << sock_ << endl;

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if (bind(sock_, (SA *)&servaddr, sizeof(servaddr)) == -1) {
        cout << "Bind error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    cout << "Binding the port success..." << endl;

    if (listen(sock_, LISTENQ) == -1) {
        cout << "Listening error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    cout << "Listening success..." << endl;
    cout << "Waiting for client connection to complete..." << endl;
    return 0;
}

int Server_Session::start()
{
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int accept_sock = accept(sock_, (SA *)&cliaddr, &clilen);
    if (accept_sock == -1) {
        cout << "Accept error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    cout << "Connect accept_sock " << accept_sock << " success..." << endl;
    return accept_sock;
}

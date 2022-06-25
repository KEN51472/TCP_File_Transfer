#include "session.h"

int Session::init()
{
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1)
    {
        cout << "Create socket error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    int ret = bind(sock_, (SA *)&servaddr, sizeof(servaddr));
    if (ret == -1)
    {
        cout << "Bind error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Binding the port success..." << endl;

    listen_sock_ = listen(sock_, LISTENQ);
    if (listen_sock_ == -1)
    {
        cout << "Listening error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Listening success..." << endl;

    cout << "Waiting for client connection to complete..." << endl;
    return 0;
}

int Session::start()
{
    clilen = sizeof(cliaddr);
    accept_sock_ = accept(sock_, (SA *)&cliaddr, &clilen);
    if (accept_sock_ == -1)
    {
        cout << "Accept error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Connect accept_sock " << accept_sock_ << " success..." << endl;
    return accept_sock_;
}

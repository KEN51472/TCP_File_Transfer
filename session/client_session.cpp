#include "client_session.h"

using namespace std;

int Client_Session::set(const string &address)
{
    serv_addr_ = address;
    return 0;
}

int Client_Session::open()
{
    struct sockaddr_in servaddr;
    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == -1) {
        cout << "Create socket error...\t" << "errno : " << errno << endl;
        return -1;
    }
    
    cout << "Create socket success...\tsock: " << sock_ << endl;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, serv_addr_.c_str(), &servaddr.sin_addr);

    if (connect(sock_, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        cout << "Connect error...\t" << "errno : " << errno << endl;
        return -1;
    }

    cout << "Connect to server success..." << endl;
    return 0;
}

int Client_Session::write(char *buf, int size)
{
    int left = size;
    while (left > 0) {
        int wn = ::write(sock_, buf + size - left, left);
        if (wn < 0) {
            cout << "Session using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        left -= wn;
        if (left == 0) {
            return size - left;
        }
    }

    return 0;
}

int Client_Session::destroy()
{   
    if (sock_ > 0) {
        close(sock_);
        cout << "sock " << sock_ << " closed success..." << endl;
    }

    return 0;
}
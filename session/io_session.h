#ifndef IO_SESSION_H
#define IO_SESSION_H

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "boost/any.hpp"
#include <string.h>

using namespace std;
using namespace boost;

class IO_Session
{  
public:
    IO_Session(int accept_sock):sock_(accept_sock)
    {

    };

    ~IO_Session()
    {
        if (sock_ > 0) {
            close(sock_);
            cout << "sock " << sock_ << " closed success.." << endl;
        }
    };


    int open(string file_path);
    int read(char *buf, int size);
    int write(char *buf, int size);
    int destroy();

private:
    int sock_;
    int fd_;
};

#endif
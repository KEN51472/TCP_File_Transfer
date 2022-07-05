#ifndef IO_SESSION_H
#define IO_SESSION_H

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include "boost/any.hpp"
#include <string.h>

using namespace std;
using namespace boost;

class Io_Session
{  
public:
    Io_Session(int accept_sock):sock_(accept_sock)
    {

    };

    ~Io_Session()
    {
       
    };

    int set(int file_size);
    int get_sock();
    int read(char *buf, int size);

private:
    int sock_;
};

#endif
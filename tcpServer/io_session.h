#ifndef IO_SESSION_H
#define IO_SESSION_H

#include <iostream>

using namespace std;

class Io_Session
{  
public:
    Io_Session(int accept_sock):sock_(accept_sock)
    {

    };

    ~Io_Session()
    {
        cout <<"1111111111111"<<endl;
    };

    int get_sock();
    int get_schedule();
    int get_size();

private:
    int sock_;
    int schedule_;
    int size_;
};

#endif
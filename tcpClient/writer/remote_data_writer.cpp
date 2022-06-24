#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "remote_data_writer.h"

using namespace std;

int Remote_Data_Writer::set(int port, const string &address){
    port_ = port;
    address_ = address;
    unique_ptr<Session> s(new Session(port_,address_));
    return 0;
}

int Remote_Data_Writer::open()
{   
    // Session s(port_, address_);
    int ret = s->open();
    if (ret < 0) {
        cout << "Writer connect to server error...\t" << "errno : " << errno << endl;
        return -1;
    }

    return 0;
}

int Remote_Data_Writer::write(char *buf, int size)
{   
    // Session s(port_, address_);
    int left = size;
    while (left > 0) {
        int wn = s->write(buf, left);
        if (wn == -1) {
            cout << "Writer using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }
        left -= wn;
        finished_ += wn;
        if (left == 0) {
            break;
        }
    }

    return finished_;
}

int Remote_Data_Writer::destroy()
{
    // Session s(port_, address_);
    int ret = s->destroy();
    return ret;
}
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "remote_data_writer.h"

using namespace std;



int Remote_Data_Writer::set(int port, const string &address){
    Session s(int port, const string &address);
    port_ = port;
    address_ = address;
    return 0;
}

int Remote_Data_Writer::open()
{
    int ret = s.open();
    if (ret < 0) {
        cout << "Writer connect to server error...\t" << "errno : " << errno << endl;
        return -1;
    }

    return 0;
}

int Remote_Data_Writer::write(char *buf, int size)
{   
    int left = size;
    while (left > 0) {
        int wn = s.write(buf, left);
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
    int ret = s.destroy();
    return ret;
}
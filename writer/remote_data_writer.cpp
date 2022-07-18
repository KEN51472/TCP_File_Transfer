#include "remote_data_writer.h"

using namespace std;

void Remote_Data_Writer::set(const string &address)
{
    cs_.set(address);
}

int Remote_Data_Writer::open(const string &name, any a)
{   
    int ret = cs_.open();
    if (ret < 0) {
        cout << "Writer connect to server error...\t" << "errno : " << errno << endl;
        return -1;
    }

    return 0;
}

int Remote_Data_Writer::write(char *buf, any a, int size)
{   
    int left = size;
    while (left > 0) {
        int wn = cs_.write(buf + size - left, left);
        if (wn == -1) {
            cout << "Writer using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }
        
        left -= wn;
        if (left == 0) {
            return size - left;
        }
    }

    return 0;
}

int Remote_Data_Writer::destroy(any a)
{
    return cs_.destroy();
}
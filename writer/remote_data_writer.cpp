#include "remote_data_writer.h"

using namespace std;

int Remote_Data_Writer::set(const string &address)
{
    s_.set(address);
    return 0;
}

int Remote_Data_Writer::open(const string &name, any a)
{   
    int ret = s_.open();
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
        int wn = s_.write(buf, left);
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

int Remote_Data_Writer::destroy(any a)
{
    return s_.destroy();
}
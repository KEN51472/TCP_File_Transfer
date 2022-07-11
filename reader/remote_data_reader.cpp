#include "remote_data_reader.h"

int Remote_Data_Reader::read(char *buf, any a, int size)
{
    IO_Session *is = any_cast<IO_Session *>(a);
    int left = size;
    while (left > 0) {
        int rn = is->read(buf + size - left, left);
        if (rn == -1) {
            cout << "Reader using function read error...\t" << "errno : " << errno << endl;
            return -1;
        }
        
        left -= rn;
        if (left == 0 || rn == 0) {
            return size - left;
        }
    }

    return 0;
}

bool Remote_Data_Reader::get_info(char *buf, int a, int b, string &info)
{
    for (int i = a; i < b; i++) {
        info += buf[i];
    }
    
    return 0;
}


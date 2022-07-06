#include "remote_data_reader.h"

int Remote_Data_Reader::read(char *buf, any a, int size)
{
    Io_Session *is = any_cast<Io_Session *>(a);
    int finished = 0; 
    int left = size;
    while (left > 0) {
        int rn = is->read(buf, left);
        if (rn == -1) {
            cout << "Reader using function read error...\t" << "errno : " << errno << endl;
            return -1;
        }
        
        left -= rn;
        finished += rn;
        if (left == 0 || rn == 0) {
            return finished;
        }
    }

    return 0;
}

string Remote_Data_Reader::get_info(char *buf, int a, int b)
{
    string info = "";
    for (int i = a; i < b; i++) {
        info += buf[i];
    }
    
    return info;
}


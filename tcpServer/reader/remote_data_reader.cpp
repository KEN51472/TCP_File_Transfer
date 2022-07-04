#include "remote_data_reader.h"

int Remote_Data_Reader::read(char *buf, Io_Session *is, int size)
{
    int finished = 0; 
    int left = size;
    while (left > 0) {
        int rn = is->read(buf, left);
        if (rn == -1) {
            cout << "Writer using function write error...\t" << "errno : " << errno << endl;
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

string Remote_Data_Reader::get_name(char *buf)
{
    string name_ = "";
    for (int i = 16; i < 1008; i++) {
        name_ += buf[i];
    }

    return name_;
}

int Remote_Data_Reader::get_size(char *buf)
{
    string file_size = "";
    for (int i = 0; i < 16; i++) {
        file_size += buf[i];
    }

    size_ = stoi(file_size);
    return size_;
}


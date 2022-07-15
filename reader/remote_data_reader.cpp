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

string Remote_Data_Reader::get_name(char *buf)
{   
    string info = "";
    for (int i = 0; i < 1024; i++) {
        info += buf[i];
    }
    value v;
    construct(info, v);    
    cout << "JSON :  " << v << endl;
    value::object_iterator iter= v.begin_object();
    string name = iter->value();
    ++iter;
    size_ = iter->value().get_as<int>();
   
    return name;
}

int Remote_Data_Reader::get_size()
{
    return size_;
}


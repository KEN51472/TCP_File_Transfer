#include "file_data_writer.h"

int File_Data_Writer::open(const string &name, any a)
{
    IO_Session *is = any_cast<IO_Session *>(a);
    string file_path = "/home/code/tcp_download/recv-" + name;
    is->open(file_path);
    return 0;
}

int File_Data_Writer::write(char *buf, any a, int size)
{
    IO_Session *is = any_cast<IO_Session *>(a);
    int left = size;
    while (left > 0) {
        int wn = is->write(buf + size - left, left);
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

int File_Data_Writer::destroy(any a)
{
    IO_Session *is = any_cast<IO_Session *>(a);
    is->destroy();
    return 0;
}
#include "file_data_writer.h"

int File_Data_Writer::write(int fd, char *buf, int size)
{
    int left = size;
    while (left > 0) {
        int wn = ::write(fd, buf, left);
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
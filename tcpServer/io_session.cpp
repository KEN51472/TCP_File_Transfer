#include "io_session.h"

int Io_Session::set(int file_size)
{
    size_ = file_size;
    return 0;
}

int Io_Session::get_sock()
{
    return sock_;
}

int Io_Session::read(char *buf, int size)
{   
    memset(buf, 0, size);
    int finished = 0;
    int left = size;
    while (left > 0) {
        int rn = ::read(sock_, buf, size);
        left -= rn;
        finished += rn;
        if (rn < 0) {
            cout << "Reader using read error...\t"
                 << "errno : " << errno << endl;
            return -1;
        }

        if (left == 0 || rn == 0) {
            return finished;
        }
    }

    return 0;
}

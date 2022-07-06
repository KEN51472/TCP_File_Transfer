#include "io_session.h"

int Io_Session::get_sock()
{
    return sock_;
}

int Io_Session::get_fd()
{
    return fd_;
}

int Io_Session::open(string file_path)
{
    fd_ = ::open(file_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd_ == -1) {
        cout << "Open error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    cout << "Open success...\t"
         << "fd : " << fd_ << endl;
    return 0;
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
            cout << "Session using read error...\t"
                 << "errno : " << errno << endl;
            return -1;
        }

        if (left == 0 || rn == 0) {
            return finished;
        }
    }

    return 0;
}

int Io_Session::write(char *buf, int size)
{   
    int finished = 0;
    int left = size;
    while (left > 0) {
        int wn = ::write(fd_, buf, size);
        left -= wn;
        finished += wn;
        if (wn < 0) {
            cout << "Session using write error...\t"
                 << "errno : " << errno << endl;
            return -1;
        }

        if (left == 0 ) {
            return finished;
        }
    }

    return 0;
}

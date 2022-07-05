#include "file_data_writer.h"

int File_Data_Writer::open(const string &name)
{
    string file_path = "/home/code/tcp_download/recv-" + name;
    fd_ = ::open(file_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd_ == -1) {
        cout << "Open error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    cout << "Open success...\t"
         << "fd : " << fd_ << endl;
    return fd_;
}

int File_Data_Writer::write(char *buf, int size)
{
    int left = size;
    int finished = 0;
    while (left > 0) {
        int wn = ::write(fd_, buf, left);
        if (wn == -1) {
            cout << "Writer using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        left -= wn;
        finished += wn;
        if (left == 0) {
            break;
        }
    }

    return finished;
}

int File_Data_Writer::destroy(any a)
{
    Io_Session *is = any_cast<Io_Session *>(a);
    if (fd_ > 0) {
        close(fd_);
        cout << "fd " << fd_ << " closed success..." << endl;
    }

    int sock = is->get_sock();
    if (sock > 0) {
        close(sock);
        cout << "sock " << sock << " closed success.." << endl;
    }

    return 0;
}
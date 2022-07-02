#include "remote_data_reader.h"

int Remote_Data_Reader::set()
{
    return 0;
}

int Remote_Data_Reader::open()
{
    string file_path = "/home/code/tcp_download/recv-" + name_;
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

int Remote_Data_Reader::read(char *buf, int sock, int b_size, int sent ,int size)
{
    memset(buf, 0, b_size);
    int left = b_size;
    while (left > 0) {
        int rn = ::read(sock, buf, b_size);
        left -= rn;
        sent += rn;
        if (rn < 0) {
            cout << "Reader using read error...\t"
                 << "errno : " << errno << endl;
            return -1;
        }

        if (left == 0 || sent == size) {
            return rn;
        }
    }

    return 0;
}

string Remote_Data_Reader::get_name(char *buf)
{
    name_ = "";
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

int Remote_Data_Reader::destroy()
{
    if (fd_ > 0) {
        close(fd_);
        cout << "fd " << fd_ << " closed success..." << endl;
    }

    return 0;
}

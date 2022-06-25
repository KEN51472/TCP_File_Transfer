#include "remote_data_reader.h"
#include "session.h"

int Remote_Data_Reader::init()
{
    int ret = s_.init();
    if (ret < 0)
    {
        cout << "Reader init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    return 0;
}

int Remote_Data_Reader::start()
{
    int ret = s_.start();
    if (ret < 0)
    {
        cout << "Reader init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    return 0;
}

int Remote_Data_Reader::open()
{
    string file_path = "/home/code/tcp_download/recv-" + name_;
    int fd = ::open(file_path.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        cout << "Open error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open success...\t"
         << "fd : " << fd << endl;
    return fd;
}

int Remote_Data_Reader::read(char *buf, int sock, int size)
{
    memset(buf, 0, size);
    int left = size;
    while (left > 0)
    {
        int rn = ::read(sock, buf, size);
        left -= rn;
        finished_ += rn;
        if (rn < 0)
        {
            cout << "Reader using read error...\t"
                 << "errno : " << errno << endl;
            return -1;
        }
        if (left == 0)
        {
            return rn;
            break;
        }
        if (finished_ == size)
        {
            return rn;
            break;
        }
    }

    return 0;
}

string Remote_Data_Reader::get_name(char *buf)
{
    buf_ = buf;
    for (int i = 16; i < 144; i++)
    {
        name_ += buf_[i];
    }
    return name_;
}

int Remote_Data_Reader::get_size(char *buf)
{
    string file_size = "";
    for (int i = 16; i < 144; i++)
    {
        file_size += buf_[i];
    }
    int size = stoi(file_size);
    return size;
}

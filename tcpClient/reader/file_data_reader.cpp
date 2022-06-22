#include "file_data_reader.h"

int File_Data_Reader::set(string &file_path)
{
    path_ = file_path;
    return 0;
}

int File_Data_Reader::open()
{
    fd_ = ::open(path_.c_str(), O_RDWR);
    if (fd_ == -1) {
        cout << "Open error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open [" << path_ << "] success...  \tfd: " << fd_ << endl;

    return 0;
}

int File_Data_Reader::get_size()
{
    size_ = lseek(fd_, 0, SEEK_END);
    lseek(fd_, 0, SEEK_SET);
    cout << "file_size : " << size_ << endl;
    return size_;
}

int File_Data_Reader::read_info(char *buf)
{
    memset(buf, 0, 8192);
    const char *s1 = to_string(size_).c_str();
    char *s2 = const_cast<char *>(s1);
    stpcpy(buf, s2);
    stpcpy(buf + 16, basename(path_.c_str()));
    return 0;
}

int File_Data_Reader::read(char *buf)
{
    memset(buf, 0, 8192);
    int rn = ::read(fd_, buf, 8192);
    if (rn < 0) {
        cout << "Function read error...\t" << "errno : " << errno << endl;
        return -1;
    }

    return rn;
}

int File_Data_Reader::destroy()
{
    if (fd_ > 0) {
        close(fd_);
        cout << "fd " << fd_ << " closed success..." << endl;
    }

    return 0;
}

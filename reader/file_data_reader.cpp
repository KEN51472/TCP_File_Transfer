#include "file_data_reader.h"

void File_Data_Reader::set_path(const string &file_path)
{
    path_ = file_path;
}

int File_Data_Reader::open()
{
    fd_ = ::open(path_.c_str(), O_RDWR);
    if (fd_ < 0) {
        cout << "Reader using open error...\t" << "errno : " << errno << endl;
        return -1;
    }

    cout << "Reader open [" << path_ << "] success...  \tfd is: " << fd_ << endl;

    return 0;
}

int File_Data_Reader::get_size()
{
    size_ = lseek(fd_, 0, SEEK_END);
    lseek(fd_, 0, SEEK_SET);
    cout << "file_size : " << size_ << endl;
    return size_;
}

bool File_Data_Reader::set_info(char *buf)
{
    value value;
    value.set("file_name", basename(path_.c_str()))("file_size", size_);
    string json = "{\"file_name\":\"" + string(basename(path_.c_str())) 
                    + "\", \"file_size\":" + to_string(size_) + "}";
    const char *js = json.c_str();
    strcpy(buf, js);
    return 0;
}

int File_Data_Reader::read(char *buf, any a ,int size)
{
    memset(buf, 0, size);
    int left = size;
    while (left > 0) {
        int rn = ::read(fd_, buf + size - left, left);
        left -= rn;
        if (rn < 0) {
            cout << "Reader using read error...\t" << "errno : " << errno << endl;
            return -1;
        }
        
        if (left == 0 || rn == 0) {
            return size - left;
        }
    }

    return 0;
}

int File_Data_Reader::destroy()
{
    if (fd_ > 0) {
        close(fd_);
        cout << "fd " << fd_ << " closed success..." << endl;
    }

    return 0;
}

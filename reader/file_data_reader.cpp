#include "file_data_reader.h"

void File_Data_Reader::set(const string &file_path, const string &json_path)
{
    json_path_ = json_path;
    file_path_ = file_path;
}

int File_Data_Reader::open(bool type)
{
    if (type == 0) {
        jfd_ = ::open(json_path_.c_str(), O_RDWR);
        if (jfd_ < 0) {
            cout << "Reader using open error...\t" << "errno : " << errno << endl;
            return -1;
        }
        
        cout << "Reader open [" << json_path_ << "] success...  \tfd is: " << jfd_ << endl;
    }

    if (type == 1) {
        fd_ = ::open(file_path_.c_str(), O_RDWR);
        if (fd_ < 0) {
            cout << "Reader using open error...\t" << "errno : " << errno << endl;
            return -1;
        }

        cout << "Reader open [" << file_path_ << "] success...  \tfd is: " << fd_ << endl;
    }
    
    return 0;
}

int File_Data_Reader::get_size()
{
    value::object_iterator iter= v_.begin_object();
    iter++;
    int size = iter->value().get_as<int>();
    cout << "file_size : " << size << endl;
    return size;
}

string File_Data_Reader::get_name(char *buf)
{
    string json = "";
    for (int i = 0; i < INFO_SIZE; i++) {
        json += buf[i];
    }
    construct(buf, v_);
    cout << "JSON :  " << v_ << endl;
    value::object_iterator iter= v_.begin_object();
    string name = iter->value().get_as<string>();
    return name;
}

int File_Data_Reader::read(char *buf, any a ,int size)
{   
    int type = any_cast<int>(a);
    int fd;
    if (type == 0) {fd = fd_;}
    if (type == 1) {fd = jfd_;}
    memset(buf, 0, size);
    int left = size;
    while (left > 0) {
        int rn = ::read(fd, buf + size - left, left);
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

    if (jfd_ > 0) {
        close(jfd_);
        cout << "json fd " << jfd_ << " closed success..." << endl;
    }

    return 0;
}

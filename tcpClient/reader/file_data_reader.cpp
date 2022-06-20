#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "file_data_reader.h"
using namespace std;

int File_Data_Reader::open_data(char *file_path)
{
    fd = open(file_path, O_RDWR);
    if (fd == -1) {
        cout << "Open error...\t" << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open [" << file_path << "] success...  \tfd: " << fd << endl;
    return fd;
}

int File_Data_Reader::get_data_size()
{
    len = lseek(fd, 0, SEEK_END);
    if (len <= 0) {
        return -1;
    }
    lseek(fd, 0, SEEK_SET);
    cout << "file_size : " << len << endl;
    return len;
}

char *File_Data_Reader::get_data_name(char *file_path)
{
    strcpy(file_name, basename(file_path));
    return file_name;
}

char *File_Data_Reader::init_buf()
{
    char *buf = new char[len];
    return buf;
}

int File_Data_Reader::read_data(char *file_path, char *buf)
{
    int file_read = 0;
    int rn = read(fd, buf, len);
    if (rn < 0) {
        cout << "Function read error...\t" << "errno : " << errno << endl;
        return -1;
    }
    file_read += rn;
    
    if (file_read == len) {
        cout << "Transfer [" << file_path << "] success..." << endl;
    }
    cout << "Reading ... " << (float)file_read / len * 100 << "%" << endl;
    return file_read;
}

int File_Data_Reader::destroy()
{   
    close(fd);
    cout << "fd " << fd << " closed success..." << endl;
    return 0;
}

#include "file_data_reader.h"
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
using namespace std;

int File_Data_Reader::open(char* file_path) {
    fd = ::open(file_path, O_RDWR);
    if (fd == -1) {
        cout << "Open error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    cout << "Open [" << file_path << "] success...  \tfd: " << fd << endl;
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    cout << "file_size : " << size << endl;
    return size;
}

int File_Data_Reader::read(char* buf) {
    memset(buf, 0, 8192);
    int rn = ::read(fd, buf, 8192);
    if (rn < 0) {
        cout << "Function read error...\t" << "errno : " << errno << endl;
        return -1;
    }
    return rn;
}

int File_Data_Reader::destroy() {
    close(fd);
    cout << "fd " << fd << " closed success..." << endl;
    return 0;
}

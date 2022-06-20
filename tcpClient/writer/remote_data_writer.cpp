#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "remote_data_writer.h"

using namespace std;

int Remote_Data_Writer::link()
{
    s.tcp_link();
    return 0;
}

int Remote_Data_Writer::write_data(char *buf, int len)
{
    int file_write = 0;
    int left = len;
    while (left > 0) {
        int wn = s.do_write(buf, left);
        if (wn == -1) {
            cout << "Using function write error...\t"
                 << "errno : " << errno << endl;
            return -1;
        }
        left -= wn;
        file_write += wn;
        if (left == 0) {
            break;
        }
        cout << "missing write size :" << left << "\trewrite:" << wn << endl;
    }
    cout << "Uploading ... " << (float)file_write / len * 100 << "%" << endl;
    
    if (file_write = len) {
        cout << "Trans success!" << endl;
    }
    delete[] buf;
    return file_write;
}

int Remote_Data_Writer::write_info(char *buf, char *file_name, int len)
{
    sprintf(file_info, "%d", len);
    strcpy(file_info + 16, file_name);
    int writeinfo = s.do_write(file_info, 1024);
    if (writeinfo == -1){
        cout << "Using function write error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    return writeinfo;
}

int Remote_Data_Writer::destroy()
{
    s.destroy();
    return 0;
}
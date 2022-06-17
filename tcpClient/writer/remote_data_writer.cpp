#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "remote_data_writer.h"


using namespace std;

int Remote_Data_Writer::link() 
{   
    sock = s.tcp_link();
    return sock;
}

int Remote_Data_Writer::write_data(char *buf) {
    int file_write = 0;
    int left = sizeof(buf);
    while (left > 0)
    {
        int wn = write(sock, buf, left); 
        if (wn == -1) {
        cout << "Using function write error...\t" << "errno : " << errno << endl;
        return -1;
        }
        left -= wn;
        file_write += wn;
        if (left == 0) {
            break;
        }
        cout << "missing write size :" << left << "\trewrite:" << wn << endl;
    }
    cout << "Uploading ... " << (float)file_write / sizeof(buf) * 100 << "%" << endl;
    if (file_write = sizeof(buf)) {
        cout << "Trans success!" << endl;
    }
    delete[] buf;
    return file_write;
}

int Remote_Data_Writer::write_info(char *buf,char *file_name)
{
    sprintf(file_info, "%ld", sizeof(buf));
    strcpy(file_info + 16, file_name);
    int writeinfo = write(sock, file_info, 1024);
    if (writeinfo == -1) {
        cout << "Using function write error...\t" << "errno : " << errno << endl;
        return -1;
    }
    return 0;

}
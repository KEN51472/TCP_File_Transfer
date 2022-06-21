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

int Remote_Data_Writer::write_data(char *buf, int rn, int size)
{
    left = rn;
    while (left > 0) {
        int wn = s.do_write(buf, left);
        if (wn == -1) {
            cout << "Using function write error...\t" << "errno : " << errno << endl;
            return -1;
        } 
        left -= wn;
        uploaded += wn;
        if (left == 0) {
            break;
        }
    }
    cout << "Uploading ... " << (float)uploaded / size * 100 << "%" << endl;
    
    return 0;
}

int Remote_Data_Writer::write_info(char *file_path, char *buf ,int size)
{   
    char *file_info = new char[128];
    char *file_name = new char [128];
    strcpy(file_name, basename(file_path));
    sprintf(file_info, "%d", size);
    strcpy(file_info + 16, file_name);
    int writeinfo = s.do_write(file_info, 1024);
    if (writeinfo == -1) {
        cout << "Using function write error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    delete file_info;
    delete file_name;
    return 0;
}

int Remote_Data_Writer::destroy()
{
    s.destroy();
    return 0;
}
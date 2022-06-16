#ifndef SESSION_H
#define SESSION_H

#include "remote_data_writer.h"
#include <unistd.h>
#include <iostream>
using namespace std;

class Session:public Remote_Data_Writer
{
public:
    Session()
    {

    };
    
    ~Session()
    {   
        close(sock);
        cout << "sock " << sock << " closed success..." << endl;
    };

    int link();

    int write_data(int sock, char *buf, int data_size);

    int write_info(int sock, int len, char *file_name);

private:
    int ret, sock, fd;
    char file_info[128] = {0};
};

#endif
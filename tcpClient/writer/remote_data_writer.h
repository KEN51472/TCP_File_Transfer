#ifndef REMOTE_DATA_WRITER_H
#define REMOTE_DATA_WRITER_H

#include "data_writer.h"
#include "session.h"
#include <unistd.h>
#include <iostream>
using namespace std;

class Remote_Data_Writer : public Data_Writer
{
public:
    Remote_Data_Writer()
    {

    };

    ~Remote_Data_Writer()
    {
        close(sock);
        cout << "sock " << sock << " closed success..." << endl;
    };

    virtual int link();

    virtual int write_data(char *buf, int len);

    virtual int write_info(char *buf, char *file_name, int len);

private:
    char file_info[128] = {0};
    int sock;
    Session s;
};

#endif
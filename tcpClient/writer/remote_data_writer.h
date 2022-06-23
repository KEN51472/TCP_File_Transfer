#ifndef REMOTE_DATA_WRITER_H
#define REMOTE_DATA_WRITER_H

#include "data_writer.h"
#include "session.h"


class Remote_Data_Writer : public Data_Writer
{
public:
    Remote_Data_Writer()
    {

    };

    ~Remote_Data_Writer()
    {
        
    };

    int set(int port, const string &address);
    int open();
    int write(char *buf, int size);
    int destroy();  

private:
    int finished_;
    int port_;
    string address_;
    Session s;
};

#endif
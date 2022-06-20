#ifndef CLIENT_TRANS_CONTROLLER_H
#define CLIENT_TRANS_CONTROLLER_H
#include "data_inputer.h"
#include "data_reader.h"
#include "data_writer.h"

class Client_Trans_Controller
{
public:
    Client_Trans_Controller(Data_Inputer *i_impl, Data_Reader *r_impl, Data_Writer *w_impl)
    {
        inputer = i_impl;
        reader = r_impl;
        writer = w_impl;
    }

    ~Client_Trans_Controller()
    {

    }

    int init();
    int start();
    int destroy();

private:
    char *data_path;
    char *data_name;
    char *buf;
    int data_size;
    Data_Inputer *inputer;
    Data_Reader *reader;
    Data_Writer *writer;
};

#endif
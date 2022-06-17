#ifndef CLIENT_TRANS_CONTROLLER_H
#define CLIENT_TRANS_CONTROLLER_H
#include "data_inputer.h"
#include "data_reader.h"
#include "data_writer.h"
#include "cin_data_inputer.h"
#include "file_data_reader.h"
#include "remote_data_writer.h"


class Client_Trans_Controller
{
public:
    Client_Trans_Controller()
    {
    }

    Client_Trans_Controller(Cin_Data_Inputer i_impl, File_Data_Reader r_impl, Remote_Data_Writer w_impl)
    {
       this->inputer = &i_impl;
       this->reader = &r_impl;
       this->writer = &w_impl;
    }

    ~Client_Trans_Controller()
    {    
    }

    int init();
    int start();


private:
    char *data_path;
    char *data_name;
    char *buf;
    Data_Inputer *inputer;
    Data_Reader *reader;
    Data_Writer *writer; 
};
#endif
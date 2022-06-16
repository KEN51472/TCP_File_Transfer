#ifndef CLIENT_TRANS_CONTROLLER_H
#define CLIENT_TRANS_CONTROLLER_H
#include "cin_data_inputer.h"
#include "file_data_reader.h"
#include "session.h"

class Client_Trans_Controller
{
public:
    Client_Trans_Controller(){

    };

    ~Client_Trans_Controller(){
        
    };

    int init();
    int start();

    Cin_Data_Inputer cdi;
    File_Data_Reader fdr;
    Session s;
    Data_Inputer *inputer = &cdi;
    Data_Reader *reader = &fdr;
    Data_Writer *writer = rdw;
    Remote_Data_Writer *rdw = &s;

private:
    char *data_path;
    int data_fd = 0;
    int data_size = 0;
    char *data_name;
    char *buf;
    int sock = 0;
};
#endif
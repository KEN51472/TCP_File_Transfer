#ifndef CLIENT_TRANS_CONTROLLER_H
#define CLIENT_TRANS_CONTROLLER_H
#include "cin_data_inputer.h"
#include "file_data_reader.h"
#include "session.h"

class Client_Trans_Controller
{
public:
    Client_Trans_Controller()
    {

    };
    
    ~Client_Trans_Controller()
    {

    };

    int init();
    int start();
    int destroy();

    
    Cin_Data_Inputer cdi;
    File_Data_Reader fdr;
    Session s;
    
private:
    char *cdi_get;
    int fdr_open;
    char *buf;
    int sock;
};   
#endif
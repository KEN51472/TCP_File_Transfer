#include <unistd.h>
#include <iostream>
#include "client_trans_controller.h"

using namespace std;

int Client_Trans_Controller::init(char *file_path)
{
    inputer->get_info(file_path);
    size = reader->open(file_path); 
    writer->link();
    return 0;
}

int Client_Trans_Controller::start(char *file_path, char *buf)
{
    writer->write_info(file_path, buf, size);
    while(1) {
        int rn = reader->read(buf);
        if(rn == 0) {
            cout << "Trans Success!!!" << endl;
            break;
        }
        int wn = writer->write(buf, rn, size); 
    }
    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader->destroy();
    writer->destroy();
    return 0;
}
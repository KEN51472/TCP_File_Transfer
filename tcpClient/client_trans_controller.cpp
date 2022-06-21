#include "client_trans_controller.h"

using namespace std;



int Client_Trans_Controller::init()
{
    path = inputer->get_info();
    reader->open(path); 
    size = reader->get_size();
    
    writer->open();
    return 0;
}

int Client_Trans_Controller::start()
{
    char *buf = new char[8192];
    reader->read_info(buf);
    writer->write(buf, 1024);
    while(1) {
        int rn = reader->read(buf);
        if(rn == 0) {
            cout << "Trans Success!!!" << endl;
            break;
        }
        int wn = writer->write(buf, rn); 
        cout << "Uploading ... " << (float)wn / size * 100 << "%" << endl;
    }
    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader->destroy();
    writer->destroy();
    return 0;
}
#include "client_trans_controller.h"

using namespace std;

char *buf = new char[8192];

int Client_Trans_Controller::init()
{
    path = inputer->get_info();
    reader->set(path);
    reader->open(); 
    size = reader->get_size();
    reader->read_info(buf);
    writer->open();
    return 0;
}

int Client_Trans_Controller::start()
{
    writer->write(buf, 1024);
    while(1) {
        int rn = reader->read(buf);
        if(rn == 0) {
            cout << "Trans Success!!!" << endl;
            break;
        }
        int wn = writer->write(buf, rn); 
        cout << "Uploading ... " << (float)(wn - 1024) / size * 100 << "%" << endl;
    }

    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader->destroy();
    writer->destroy();
    delete buf;
    return 0;
}
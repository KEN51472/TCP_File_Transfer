#include <unistd.h>
#include <iostream>
#include "client_trans_controller.h"

using namespace std;

int Client_Trans_Controller::init(char *file_path, int size)
{
    inputer->get_info(file_path);
    reader->open_data(file_path, size); 
    writer->link();
    return 0;
}

int Client_Trans_Controller::start(char *file_path, char *buf, int size)
{
    writer->write_info(file_path, buf, size);
    uploaded = 0;
    while(1) {
        int rn = reader->read_data(buf);
        if(rn == 0) {
            cout << "Trans Success!!!" << endl;
            break;
        }
        int left = rn;
        while (left > 0) {
            int wn = writer->write_data(buf, left);
            left -= wn;
            if (left == 0) {
                break;
            }
        }
        cout << "Uploading ... " << (float)uploaded / size * 100 << "%" << endl; 
    }
    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader->destroy();
    writer->destroy();
    return 0;
}
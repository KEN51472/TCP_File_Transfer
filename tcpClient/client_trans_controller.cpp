#include "client_trans_controller.h"

int Client_Trans_Controller::init()
{   
    string address = inputer_->get_address();
    writer_->set(address);
    if (writer_->open() < 0) {
        cout << "Controller using connect error...\t" << "errno : " << errno << endl;
        return -1;
    }

    string path = inputer_->get_path(); 
    reader_->set(path);
    if (reader_->open() < 0) {
        cout << "Controller using open error...\t" << "errno : " << errno << endl;
        return -1;
    }

    size_ = reader_->get_size();  
    return 0;
}

int Client_Trans_Controller::start()
{   
    char buf[BUFFER_SIZE] = {0};
    reader_->get_info(buf, BUFFER_SIZE);
    if (writer_->write(buf, INFO_SIZE) < 0) {
        cout << "Controller using write error...\t" << "errno : " << errno << endl;
        return -1;
    }

    while(1) {
        int rn = reader_->read(buf, BUFFER_SIZE);
        if (rn < 0) {
            cout << "Writer using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        if (rn == 0) {
            if (size_ != 0) {
                cout << "Trans Success!!!" << endl;
                break;
            }

            cout << "Empty file trans..." << endl;
            return 0;
        }

        int wn = writer_->write(buf, rn); 
        if (wn < 0) {
            cout << "Controller using write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        cout << "Uploading ... " << (float)(wn - INFO_SIZE) / size_ * 100 << "%" << endl;
    }

    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader_->destroy();
    writer_->destroy();
    return 0;
}
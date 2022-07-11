#include "client_trans_controller.h"

int Client_Trans_Controller::init()
{   
    cout << "Please enter the server address: " << endl;
    string address = "";
    inputer_->get_info(address);
    writer_->set(address);
    if (writer_->open("0", 0) < 0) {
        cout << "Controller using connect error...\t" << "errno : " << errno << endl;
        return -1;
    }

    cout << "Please enter the path of the file to be transferred: " << endl;
    string path = "";
    inputer_->get_info(path); 
    reader_->set(path);
    if (reader_->open() < 0) {
        cout << "Controller using open error...\t" << "errno : " << errno << endl;
        return -1;
    }
 
    return 0;
}

int Client_Trans_Controller::start()
{   
    char buf[BUFFER_SIZE] = {0};
    string info = "";
    reader_->get_info(buf, BUFFER_SIZE, 0, info);
    size_ = stoi(info);
    
    if (writer_->write(buf, 0, INFO_SIZE) < 0) {
        cout << "Controller using write error...\t" << "errno : " << errno << endl;
        return -1;
    }

    int sent = 0;
    while(1) {
        int rn = reader_->read(buf, 0, BUFFER_SIZE);
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

        int wn = writer_->write(buf, 0, rn); 
        if (wn < 0) {
            cout << "Controller using write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        sent += wn;
        cout << "Uploading ... " << (float) sent / size_ * 100 << "%" << endl;
    }

    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader_->destroy();
    writer_->destroy(0);
    return 0;
}
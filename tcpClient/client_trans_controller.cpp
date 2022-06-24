#include "client_trans_controller.h"

using namespace std;

int Client_Trans_Controller::init()
{   
    string path = inputer_->get_info();
    reader_->set(path);
    int ret = reader_->open(); 
    if (ret < 0) {
        cout << "Controller using open error...\t" << "errno : " << errno << endl;
        return -1;
    }
    size_ = reader_->get_size();
    reader_->read_info(buf, 8192);
    writer_->set(9877, "127.0.0.1");
    ret = writer_->open();
    if (ret < 0) {
        cout << "Controller using connect error...\t" << "errno : " << errno << endl;
        return -1;
    }

    return 0;
}

int Client_Trans_Controller::start()
{
    int wn = writer_->write(buf, 1024);
    if (wn < 0) {
        cout << "Controller using write error...\t" << "errno : " << errno << endl;
        return -1;
    }
    while(1) {
        int rn = reader_->read(buf, 8192);
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
        wn = writer_->write(buf, rn); 
        if (wn < 0) {
            cout << "Controller using write error...\t" << "errno : " << errno << endl;
            return -1;
        }
        cout << "Uploading ... " << (float)(wn - 1024) / size_ * 100 << "%" << endl;
    }

    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader_->destroy();
    writer_->destroy();
    return 0;
}
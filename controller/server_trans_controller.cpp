#include "server_trans_controller.h"

int Server_Trans_Controller::init()
{
    if (inputer_->init() < 0) {
        cout << "Controller using init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    
    return 0;
}

int Server_Trans_Controller::start()
{   
    while(1) { 
        any ret = inputer_->start();
        thread t(&Server_Trans_Controller::trans, this, any_cast<IO_Session *>(ret));
        t.detach();
    }
}

int Server_Trans_Controller::trans(IO_Session *is) {
    char buf[BUFFER_SIZE] = {0};
    if (reader_->read(buf, is, INFO_SIZE) < 0) {
        cout << "Controller using function read error...\t" << "errno : " << errno << endl;
        return -1;
    }

    string name = reader_->get_name(buf);
    int size = reader_->get_size();
    cout << "Ready to receive...... file name:[" << name << "] file size:[" << size << "]" << endl;
    if (size == 0) {
        cout << "Empty file trans..." << endl;
        return 0;
    }

    if (writer_->open(name, is) < 0) {
        cout << "Controller using function open error...\t" << "errno : " << errno << endl;
        return -1;
    }
    
    int recv = 0;
    while(1) {
        int left = BUFFER_SIZE;
        while (left > 0) {
            int rn = reader_->read(buf + BUFFER_SIZE - left, is, left);
            if (rn == -1) {
                cout << "Controller using function read error...\t" << "errno : " << errno << endl;
                return -1;
            }
        
            left -= rn;
            if (left == 0 || rn == 0) {
                break;
            }
        }
        
        int rn = BUFFER_SIZE - left;
        left = rn;
        while (left > 0) {
            int wn = writer_->write(buf + rn - left, is, left);
            if (wn == -1) {
                cout << "Controller using function write error...\t" << "errno : " << errno << endl;
                return -1;
            }
        
            left -= wn;
            if (left == 0) {
                break;
            }
        }

        recv += (rn - left);
        cout << "Uploading ... " << (float) recv / size * 100 << "%" << endl;
        if (recv == size) {
            cout << "trans success !!" << endl;
            break;
        }
    }

    writer_->destroy(is);

    return 0;

}
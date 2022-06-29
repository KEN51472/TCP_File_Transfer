#include "server_trans_controller.h"


int Server_Trans_Controller::init()
{
    if (reader_->init() < 0) {
        cout << "Controller using init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }

    return 0;
}

int Server_Trans_Controller::start()
{
    while(1) {
        int sock = reader_->start();
        if (sock < 0) {
            cout << "Controller start error...\t"
             << "errno : " << errno << endl;
            return -1;
        }

        thread t(&Server_Trans_Controller::trans, this, sock);
        t.detach();
    }
}

int Server_Trans_Controller::trans(int sock){
    char buf[BUFFER_SIZE] = {0};
    if (reader_->read(buf, sock, INFO_SIZE, 0, 1024) < 0) {
        cout << "Controller using function write error...\t" << "errno : " << errno << endl;
        return -1;
    }

    string name = reader_->get_name(buf);
    int size = reader_->get_size(buf);
    cout << "Ready to receive...... file name:[" << name << "] file size:[" << size << "]" << endl;
    int fd = reader_->open();
    
    int sent = 0;
    while(1) {
        int rn = reader_->read(buf, sock, BUFFER_SIZE, sent ,size);
        if (rn < 0) {
            cout << "Controller using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        if (rn == 0) {
            if (size != 0) {
                cout << "Trans Success!!!" << endl;
                break;
            }

            cout << "Empty file trans..." << endl;
            return 0;
        }

        int wn = writer_->write(fd, buf, rn); 
        if (wn < 0) {
            cout << "Controller using write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        sent += wn;
        cout << "Uploading ... " << (float) sent / size * 100 << "%" << endl;
    }

    reader_->destroy();

    return 0;

}
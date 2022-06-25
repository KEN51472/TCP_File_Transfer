#include "server_trans_controller.h"


int Server_Trans_Controller::init()
{
    int ret = reader_->init();
    if (ret < 0) {
        cout << "Controller using init error...\t"
             << "errno : " << errno << endl;
        return -1;
    }
    return 0;
}

int Server_Trans_Controller::start()
{
    while(1){
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
    char buf[8192] = {0};
    int rn = reader_->read(buf, sock, 1024);
    if (rn < 0) {
        cout << "Controller using function write error...\t" << "errno : " << errno << endl;
        return -1;
    }
    int size = reader_->get_size(buf);
    string name = reader_->get_name(buf);
    cout << "Ready to receive...... file name:[" << name << "] file size:[" << size << "]" << endl;
    int fd = reader_->open();
    while(1) {
        rn = reader_->read(buf, sock, 8192);
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
        cout << "Uploading ... " << (float) wn / size * 100 << "%" << endl;
    }

    return 0;

}
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
    int i = -1;
    while(1) { 
        int sock = reader_->start();
        if (sock < 0) {
            cout << "Controller start error...\t"
             << "errno : " << errno << endl;
            return -1;
        }
        
        data_info *di = new data_info();
        di->sock = sock;   
        v_.push_back(*di);
        i++;
        thread t(&Server_Trans_Controller::trans, this, ref(v_), i);
        t.detach();
    }
}

int Server_Trans_Controller::trans(vector<data_info> &v_, int i){
    char buf[BUFFER_SIZE] = {0};
    if (reader_->read(buf, v_[i].sock, INFO_SIZE, 0, INFO_SIZE) < 0) {
        cout << "Controller using function read error...\t" << "errno : " << errno << endl;
        return -1;
    }

    string name = reader_->get_name(buf);
    v_[i].size = reader_->get_size(buf);
    cout << "Ready to receive...... file name:[" << name << "] file size:[" << v_[i].size << "]" << endl;
    v_[i].fd = reader_->open();
    
    v_[i].sent = 0;
    while(1) {
        int rn = reader_->read(buf, v_[i].sock, BUFFER_SIZE, v_[i].sent , v_[i].size);
        if (rn < 0) {
            cout << "Controller using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        if (rn == 0) {
            if (v_[i].size != 0) {
                cout << "Trans Success!!!" << endl;
                break;
            }

            cout << "Empty file trans..." << endl;
            return 0;
        }

        int wn = writer_->write(v_[i].fd, buf, rn); 
        if (wn < 0) {
            cout << "Controller using write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        v_[i].sent += wn;
        cout << "Uploading ... " << (float) v_[i].sent / v_[i].size * 100 << "%" << endl;
    }

    reader_->destroy();

    return 0;

}
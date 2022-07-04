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
        variant<int, Io_Session *> ret = inputer_->start();
        thread t(&Server_Trans_Controller::trans, this, ref(get<Io_Session *>(ret)));
        t.detach();
    }
}

int Server_Trans_Controller::trans(Io_Session *is) {
    char buf[BUFFER_SIZE] = {0};
    if (reader_->read(buf, is, INFO_SIZE) < 0) {
        cout << "Controller using function read error...\t" << "errno : " << errno << endl;
        return -1;
    }

    string name = reader_->get_name(buf);
    int size = reader_->get_size(buf);
    cout << "Ready to receive...... file name:[" << name << "] file size:[" << size << "]" << endl;
    writer_->open(name);
    writer_->set(size, is);
    
    int sent = 0;
    while(1) {
        int rn = reader_->read(buf, is, BUFFER_SIZE);
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

        int wn = writer_->write(buf, rn); 
        if (wn < 0) {
            cout << "Controller using write error...\t" << "errno : " << errno << endl;
            return -1;
        }

        sent += wn;
        cout << "Uploading ... " << (float) sent / size * 100 << "%" << endl;
    }

    writer_->destroy(is);

    return 0;

}
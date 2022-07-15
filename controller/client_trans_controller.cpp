#include "client_trans_controller.h"

int Client_Trans_Controller::init()
{   
    cout << "Please enter the server address: " << endl;
    string address = "";
    if (inputer_->get_address(address) < 0) {
        cout << "Controller using get error...\t" << "errno : " << errno << endl;
        return -1;
    }
    
    writer_->set(address);
    if (writer_->open("0", 0) < 0) {
        cout << "Controller using connect error...\t" << "errno : " << errno << endl;
        return -1;
    }

    cout << "Please enter the path of the file to trans: " << endl;
    string file_path = "";
    if (inputer_->get_path(file_path) < 0) {
        cout << "Controller using get error...\t" << "errno : " << errno << endl;
        return -1;
    }

    cout << "Please enter the path of the json file: " << endl;
    string json_path = "";
    if (inputer_->get_json(json_path) < 0) {
        cout << "Controller using get error...\t" << "errno : " << errno << endl;
        return -1;
    }

    reader_->set(file_path, json_path);
    if (reader_->open(0) < 0) {
        cout << "Controller using open error...\t" << "errno : " << errno << endl;
        return -1;
    }

    if (reader_->open(1) < 0) {
        cout << "Controller using open error...\t" << "errno : " << errno << endl;
        return -1;
    }
 
    return 0;
}

int Client_Trans_Controller::start()
{   
    char buf[BUFFER_SIZE] = {0};
    reader_->read(buf, 1, INFO_SIZE);  
    reader_->get_name(buf);
    size_ = reader_->get_size();
   
    if (size_ == 0) {
        cout << "Empty file trans..." << endl;
        return 0;
    }
    
    if (writer_->write(buf, 0, INFO_SIZE) < 0) {
        cout << "Controller using write error...\t" << "errno : " << errno << endl;
        return -1;
    }

    int sent = 0;
    while(1) {
        int left = BUFFER_SIZE;
        while (left > 0) {
            int rn = reader_->read(buf + BUFFER_SIZE - left, 0, left);
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
            int wn = writer_->write(buf + rn - left, 0, left);
            if (wn == -1) {
                cout << "Controller using function write error...\t" << "errno : " << errno << endl;
                return -1;
            }
        
            left -= wn;
            if (left == 0) {
                break;
            }
        }

        sent += (rn - left);
        cout << "Uploading ... " << (float) sent / size_ * 100 << "%" << endl;
        if (sent == size_) {
            cout << "trans success !!" << endl;
            break;
        }
    }

    return 0;
}

int Client_Trans_Controller::destroy()
{
    reader_->destroy();
    writer_->destroy(0);
    return 0;
}
#include "file_data_writer.h"

int File_Data_Writer::open(const string &name, any a)
{
    Io_Session *is = any_cast<Io_Session *>(a);
    string file_path = "/home/code/tcp_download/recv-" + name;
    is->open(file_path);
    return 0;
}

int File_Data_Writer::write(char *buf, any a, int size)
{
    Io_Session *is = any_cast<Io_Session *>(a);
    int finished = 0; 
    int left = size;
    while (left > 0) {
        int wn = is->write(buf, left);
        if (wn == -1) {
            cout << "Writer using function write error...\t" << "errno : " << errno << endl;
            return -1;
        }
        
        left -= wn;
        finished += wn;
        if (left == 0) {
            return finished;
        }
    }

    return 0;
}

int File_Data_Writer::destroy(any a)
{
    Io_Session *is = any_cast<Io_Session *>(a);
    if (fd_ > 0) {
        close(fd_);
        cout << "fd " << fd_ << " closed success..." << endl;
    }

    int sock = is->get_sock();
    if (sock > 0) {
        close(sock);
        cout << "sock " << sock << " closed success.." << endl;
    }

    return 0;
}
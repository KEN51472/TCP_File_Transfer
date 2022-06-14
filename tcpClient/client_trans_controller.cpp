#include "cin_data_inputer.h"
#include "data_inputer.h"
#include "file_data_reader.h"
#include "session.h"
#include "wrapper.h"
#include <iostream>
using namespace std;

int main() 
{   
    char file_info[128] = {0};
    char buf[65536] = {0};
    char file_name[128] = {0};
    Session s;
    int sock = s.tcp_connect();
    Cin_Data_Inputer cdi;
    char* file_path = cdi.get_data();
    cout << "file_path is : " << file_path << endl;
    File_Data_Reader fdr;
    int fd = fdr.open_data(file_path,file_name,file_info); 
    int len = lseek(fd, 0, SEEK_END);
    s.write_data(sock,file_info,1024);
    int sent = 0;
    while (1) {
        int rn = fdr.read_data(fd,buf,*file_name);
        int left = rn;
        while (left > 0) {
            int wn = s.write_data(sock,buf,left);
             left -= wn;
            sent += wn;
            cout << "sent :" << sent << endl;
            if (left == 0) {
                break;
            }
            cout << "missing write size :" << left << "\trewrite:" << wn
                 << endl;
        }
        cout << "Uploading ... " << (float)sent / len * 100 << "%" << endl;
    }

    return 0;
}

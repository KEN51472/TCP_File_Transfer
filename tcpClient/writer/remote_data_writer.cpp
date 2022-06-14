#include <iostream>
#include "remote_data_writer.h"
#include "wrapper.h"

using namespace std;

int Remote_Data_Writer::tcp_connect() {
    cout << "this is data_writer" << endl;
    return 0;
}

int Remote_Data_Writer::write_data(int sock,char buf[],int left) {
    cout << "this is data_writer" << endl;
    return 0;
}
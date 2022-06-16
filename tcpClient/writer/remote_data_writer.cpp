#include <iostream>
#include "remote_data_writer.h"

using namespace std;

int Remote_Data_Writer::link() 
{
    return 0;
}

int Remote_Data_Writer::write_data(int sock, char *buf, int data_size)
{
    return 0;
}

int Remote_Data_Writer::write_info(int sock,int len,char *file_name)
{
    return 0;
}
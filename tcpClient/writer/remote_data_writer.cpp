
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "remote_data_writer.h"

using namespace std;

int Remote_Data_Writer::open()
{
    s.open();
    return 0;
}

int Remote_Data_Writer::write(char *buf, int w_size)
{
    left = w_size;
    while (left > 0) {
        int wn = s.write(buf, left);
        left -= wn;
        uploaded += wn;
        if (left == 0) {
            break;
        }
    }
    
    return uploaded;
}

int Remote_Data_Writer::destroy()
{
    s.destroy();
    return 0;
}
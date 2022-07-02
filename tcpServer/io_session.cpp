#include "io_session.h"

int Io_Session::get_sock()
{
    return sock_;
}

int Io_Session::get_schedule()
{
    return schedule_;
}

int Io_Session::get_size()
{
    return size_;
}
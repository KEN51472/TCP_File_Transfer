#ifndef DATA_INPUTER_H
#define DATA_INPUTER_H

#include "boost/variant.hpp"
#include "io_session.h"
using namespace boost;

class Data_Inputer
{
public:
    Data_Inputer()
    {

    };

    virtual ~Data_Inputer()
    {

    };

    virtual int init();
    virtual variant<int, Io_Session *> start();
};

#endif
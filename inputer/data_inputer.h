#ifndef DATA_INPUTER_H
#define DATA_INPUTER_H

#include <iostream>
#include <boost/any.hpp>

using namespace boost;
using namespace std;

class Data_Inputer
{
public:
    Data_Inputer()
    {

    };

    virtual ~Data_Inputer()
    {

    };

    virtual bool get_info(string &info);
    virtual int init();
    virtual any start();
};

#endif
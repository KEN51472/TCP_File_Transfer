#ifndef DATA_INPUTER_H
#define DATA_INPUTER_H

#include <iostream>

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

    virtual string get_path();
    virtual string get_address();
};

#endif
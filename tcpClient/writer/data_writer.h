#ifndef DATA_WRITER_H
#define DATA_WRITER_H

class Data_Writer 
{
public:
    Data_Writer()
    {

    };

    ~Data_Writer()
    {

    };
    
    virtual int link();

    virtual int write_data(int sock,char *buf);

private:
};

#endif
#ifndef DATA_WRITER_H
#define DATA_WRITER_H

class Data_Writer
{
public:
    Data_Writer()
    {

    };

    virtual ~Data_Writer()
    {

    };

    virtual int link();

    virtual int write_data(char *buf, int len);

    virtual int write_info(char *buf, char *file_name, int len);

private:
};

#endif
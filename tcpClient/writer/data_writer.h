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

    virtual int write_data(char *buf, int left);

    virtual int write_info(char *file_path, char *buf ,int size);

    virtual int destroy();

private:
};

#endif
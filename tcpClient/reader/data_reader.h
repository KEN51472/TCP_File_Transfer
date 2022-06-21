#ifndef DATA_READER_H
#define DATA_READER_H

class Data_Reader
{
public:
    Data_Reader()
    {

    };

    virtual ~Data_Reader()
    {

    };

    virtual int open(char *file_path);

    virtual int read(char *buf);

    virtual int destroy();

private:
};

#endif
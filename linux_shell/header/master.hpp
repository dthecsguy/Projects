#ifndef MASTER_H
#define MASTER_H

class Master{
public:
    Master(){};
    virtual int execute(int fdIn, int fdOut) = 0;
    virtual char** get_file() {return 0;};
};
#endif

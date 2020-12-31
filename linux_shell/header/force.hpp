#ifndef force_h
#define force_h

#include "connect.hpp"

class Force : public Connector {
    
public:
    Force() {};
    Force(Master* node1, Master* node2) : Connector(node1, node2) {};
    
    virtual int execute(int fdIn, int fdOut);
    void set_left(Master* node1) {left = node1;}
    void set_right(Master* node2) {left = node2;}
    virtual char** get_file() {return 0;};    
};

int Force :: execute(int fdIn, int fdOut) {
    
    int success;
    left->execute(fdIn, fdOut);
    
    success = right->execute(fdIn, fdOut);
    
    return success;
}

#endif

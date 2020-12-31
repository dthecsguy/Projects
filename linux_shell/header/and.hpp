#ifndef and_h
#define and_h

#include "connect.hpp"

class And : public Connector {
    
public:
    And() {};
    And(Master* node1, Master* node2) :  Connector(node1, node2) {};

    virtual int execute(int fdIn, int fdOut);
    virtual char** get_file() {return 0;};
    void set_left(Master* node1) {left = node1;}
    void set_right(Master* node2) {left = node2;}
    
};

int And :: execute(int fdIn, int fdOut) {
     
    int success = 0;
    
    success = left->execute(fdIn, fdOut);
    
    if (success == 1) {
        
        success = right->execute(fdIn, fdOut);
    }
    return success;
}

#endif

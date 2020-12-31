#ifndef or_h
#define or_h

#include "connect.hpp"

class Or : public Connector {
    
public:
    Or() {};
    Or(Master* node1, Master* node2) : Connector(node1, node2) {};
    
    virtual int execute(int fdIn, int fdOut);
    void set_left(Master* node1) {left = node1;}
    void set_right(Master* node2) {right = node2;}
    virtual char** get_file() {return 0;};

};

int Or :: execute(int fdIn, int fdOut) {
    
    int success = 0;
    
    success = left->execute(fdIn, fdOut);
    
    if (success == 0) {
        
        success = right->execute(fdIn, fdOut);
    }
    
    return success;
}

#endif

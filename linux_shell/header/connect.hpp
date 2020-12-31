#ifndef connector_h
#define connector_h

#include "master.hpp"

class Connector : public Master {
    
protected:
    Master* left, *right;
    
public:
    Connector() {};
    Connector(Master* node1, Master* node2) : Master(), left(node1), right(node2) {};
    
    virtual int execute(int fdIn, int fdOut);
    void set_left(Master* node) {left = node;}
    void set_right(Master* node) {right = node;}
    virtual char** get_file() {return 0;};    
};

int Connector:: execute(int fdIn, int fdOut) {
    
    return 0;
}

#endif

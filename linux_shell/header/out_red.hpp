#ifndef out_red_hpp
#define out_red_hpp

#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include "connect.hpp"

class Out : public Connector {
    
public:
    Out() {};
    Out(Master* node1, Master* node2) :  Connector(node1, node2) {};
    
    virtual int execute(int fdIn, int fdOut);
    void set_left(Master* node1) {left = node1;}
    void set_right(Master* node2) {left = node2;}
    virtual char** get_file() {return 0;};
};

int Out :: execute(int fdIn, int fdOut) {
    
    char* rightFile = *right->get_file();
    
    fdOut = open(rightFile, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
    
    return left->execute(fdIn, fdOut);
    
}

#endif /* in_red.hpp */

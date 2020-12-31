#ifndef pipe_hpp
#define pipe_hpp


#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include "connect.hpp"

class Pipe : public Connector {
    
public:
    Pipe() {};
    Pipe(Master* node1, Master* node2) :  Connector(node1, node2) {};
    
    virtual int execute(int fdIn, int fdOut);
    void set_left(Master* node1) {left = node1;}
    void set_right(Master* node2) {left = node2;}
    virtual char** get_file() {return 0;};
    
private:
    Master* files;
    
};

int Pipe :: execute(int fdIn, int fdOut) {
    
    int f[2];
   
    if(pipe(f) < 0) {
        perror("pipe");
        return 0;
    }
    
    
    if(!left->execute(fdIn, f[1])) {
        return 0;
    }
    
    close(f[1]);
    
    if(!right->execute(f[0], fdOut)) {
        return 0;
    }
    
    close(f[0]);
    
    return 1;
}


#endif

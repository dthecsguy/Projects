#ifndef COMMAND_H
#define COMMAND_H

#include "master.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

class COM : public Master{
public:
    COM(char** inCommand) : command(inCommand){};
    COM() {};
    virtual int execute(int in, int out);
    char** get_file() {return this->command;}

private:
    char** command;
};

// Returns true if command executed successfully
int COM::execute(int in, int out){
 
    int passed = 1;
    int status;

    if (strncmp(this->command[0], "exit", 4) == 0)
        return -1;

    pid_t process = fork();
    pid_t cpid; 

    if(process == 0){

        if(dup2(in,0) == -1) {
            perror("dup2");
            return 0;
        }
        
        if(dup2(out,1) == -1) {
            perror("dup2");
            return 0;
        }

	execvp(this->command[0], this->command);
	passed = 0;
        perror(nullptr);
        exit(1);	

    }
    else{
	cpid = waitpid(process, &status, 0);
	if(!WEXITSTATUS(status))
	    return true;
	else
	    return false;
    }

    return passed;
}   
    
#endif

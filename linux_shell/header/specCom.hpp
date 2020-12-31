#ifndef specCom_h
#define specCom_h

class SpecCOM : public COM {
public:
    SpecCOM(char** inCommand) : command(inCommand){};
    virtual int execute(int fdIn, int fdOut);
    virtual char** get_file() {return this->command;};    
private:
    char** command;
    
};

int SpecCOM :: execute(int fdIn, int fdOut) {
        
    struct stat statbuff;
    
    if (strncmp(this->command[1], "-e", 2) == 0) {
        
        int status = stat(this->command[2], &statbuff);
        
        if (status == -1) {
            std::cout << "(False)" << std::endl;
            return 0;
        } else {
            std::cout << "(True)" << std::endl;
            return 1;
        }
        
    } else if (strncmp(this->command[1], "-f", 2) == 0) {
        
        int status = stat(this->command[2], &statbuff);
        
        if (status == -1) {
            std::cout << "(False)" << std::endl;
            return 0;
        }
        
        if (S_ISREG(statbuff.st_mode)) {
            std::cout << "(True)" << std::endl;
            return 1;
        } else {
            std::cout << "(False)" << std::endl;
            return 0;
        }
        
    } else if (strncmp(this->command[1], "-d", 2) == 0) {
        
        int status = stat(this->command[2], &statbuff);
        
        if (status == -1) {
            std::cout << "(False)" << std::endl;
            return 0;
        }
        
        if (S_ISDIR(statbuff.st_mode)) {
            std::cout << "(True)" << std::endl;
            return 1;
        } else {
            std::cout << "(False)" << std::endl;
            return 0;
        }
        
    } else {
        
        int status = stat(this->command[1], &statbuff);
        
        if (status == -1) {
            std::cout << "(False)" << std::endl;
            return 0;
        } else {
            std::cout << "(True)" << std::endl;
            return 1;
        }
    }
}

#endif


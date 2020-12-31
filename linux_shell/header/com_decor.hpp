#ifndef COM_DECOR_H
#define COM_DECOR_H

#include "command.hpp"

class ComDecor : public COM{
public:
        ComDecor() : COM(nullptr){};
        virtual int execute(int fdIn, int fdOut){ return base->execute(fdIn, fdOut); }
        void set_base(Master* root){ base = root; }
        virtual char** get_file() {return 0;};

protected:
        Master* base;
};

#endif


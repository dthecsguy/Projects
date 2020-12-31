#ifndef PARENTHESES_H
#define PARENTHESES_H

#include "connect.hpp"
#include "command.hpp"
#include "com_decor.hpp"
#include <vector>

class Paren : public ComDecor{
public:
	Paren(std::vector<Connector*> iCons, std::vector<COM*> iComs) : 
		ComDecor(), cons(iCons), coms(iComs) {this->set_base(build_tree());}
	Master* build_tree();
	int execute(int fdIn, int fdOut){ return this->base->execute(fdIn, fdOut); }
        virtual char** get_file() {return 0;};
private:
	std::vector<Connector*> cons;
	std::vector<COM*> coms;	
};

Master* Paren::build_tree(){
	if(coms.size() == 1)
		return coms[0];
	
	cons[0]->set_left(coms[0]);
        cons[0]->set_right(coms[1]);

        for(int i = 1; i < cons.size(); i++){
                cons[i]->set_left(cons[i-1]);
                cons[i]->set_right(coms[i+1]);
        }

        Master* command_tree = cons[cons.size() - 1];
	
	return command_tree;
}

#endif

#include <stdio.h>
#include <iostream>
#include <string>
#include "../header/parse.hpp"
#include "../header/command.hpp"
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h>
#include <vector> 

using namespace std;

int main(int argc, char* argv[]){

    std::string input;

    if(argc == 1){

	int success = 0;

    	do{
            cout << "$ ";

	    getline(cin, input);

            Parse parser(input);
            parser.parse();
            parser.build_tree();
            success = parser.execute(0,1);;

            if(success == -1 ) {

            exit(0);
            }
	    
	    input.clear();

        } while(true);
    }
    else{
        int success;
	input = argv[1];
	Parse parser(input);
	parser.parse();
	parser.build_tree();
	success = parser.execute(0,1);
        
        if(success == -1 ) {

        exit(0);
        }
        input.clear();
	return 0;
    }
}

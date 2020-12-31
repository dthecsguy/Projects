#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include "command.hpp"
#include <vector>
#include <stack>
#include <string>
#include "connect.hpp"
#include "master.hpp"
#include "and.hpp"
#include "or.hpp"
#include "force.hpp"
#include "pipe.hpp"
#include "paren.hpp"
#include "specCom.hpp"
#include "in_red.hpp"
#include "out_red.hpp"
#include "append_out.hpp"

class Parse : public Master{
    
public:
    Parse(std::string input) { in = input; command_tree = nullptr;}
    
    void parse();
    void clear();
    char** toCommand(std::vector<char*>* command);
    std::vector<COM*> get_commands() { return commands; }
    std::vector<Connector*> get_connectors() { return connectors; }
    COM* get_command(int index) { return commands[index]; }
    Master* build_tree();
    virtual int execute(int fdIn, int fdOut);
    virtual char** get_file() {return 0;};
    char* pushIt(std::string buffer);
    
private:
    std::string in;
    std::vector<COM*> commands;
    std::vector<Connector*> connectors;
    Master* command_tree;
};

void Parse::parse() {
    
    std::vector<char*> exes, piece;
    std::vector< std::vector <char*> > args;
    std::vector<char> cons;
    std::string buffer;
    bool inQuote = false, first = true;
    
    std::size_t found = in.find("#");
    
    if(found != std::string::npos){
        std::string temp = in.substr(0, found - 1);
        in.clear();
        in = temp;
    }
    
    int x = in.length();
    char* str2 = new char[x + 1];
    strcpy(str2, in.c_str());
    
    for(int i = 0; i < in.length(); i++){
        
        char* cstr;
        
        if(in[i] == '"'){
            inQuote = !inQuote;
        }
        else if(in[i] == '(' || in[i] == ')'){
            if(!inQuote){
                if(i == (in.length() - 1)){
                    exes.push_back(pushIt(buffer));
                    buffer.clear();
                }
            }
            continue;
        }
        else if(in[i] == ';'){
            if(inQuote){
                buffer.push_back(in[i]);
                continue;
            }
            exes.push_back(pushIt(buffer));
            buffer.clear();
            continue;
        }
        else if(in[i] == '&') {
            if(inQuote){
                buffer.push_back(in[i]);
                continue;
            }
            else {
                if(in[i+1] == '&'){
                    first = true;
                    exes.push_back(pushIt(buffer));
                    buffer.clear();
                    in.erase(in.begin()+(i+1));
                    continue;
                }
            }
        } else if (in[i] == '|'){
            if(inQuote){
                buffer.push_back(in[i]);
            } else {
                
                if(in[i+1] == '|') {
                    in.erase(in.begin()+(i+1));
                }            
                first = true;
                exes.push_back(pushIt(buffer));
                buffer.clear();
            }
            continue;
        }else if (in[i] == '<' || in[i] == '>' ){
            if(inQuote){
                buffer.push_back(in[i]);
                continue;
            }
            else {
                
                if(in[i+1] == '>') {
                    in.erase(in.begin()+(i+1));
                }
                
                exes.push_back(pushIt(buffer));
                buffer.clear();
                continue;
            }
        }
        
        buffer.push_back(in[i]);
        
        if(buffer[0] == ' ')
            buffer.erase(0);
        
        if(i == (in.length() - 1)){
            exes.push_back(pushIt(buffer));
            buffer.clear();
            continue;
        }
        
    }
    
    
    inQuote = false;
    first = true;
    
    for(int i = 0; i < exes.size(); i++){
        std::string temp = exes[i];
        
        for(int j = 0; j < temp.length(); j++)  {
            if(temp[j] == ' '){
                if(!inQuote){
                    
                    piece.push_back(pushIt(buffer));
                    buffer.clear();
                    continue;
                }
            }
            else if(temp[j] == '"'){
                inQuote = !inQuote;
                
                if(!inQuote) {
                    temp[j] = NULL;
                } else {
                    temp.erase(temp.begin() + j);
                }
            }
            
            buffer.push_back(temp[j]);
            
            if(j == temp.length() - 1){
                
                piece.push_back(pushIt(buffer));
                buffer.clear();
            }
        }
        
        piece.push_back(nullptr);
        
        args.push_back(piece);
        piece.clear();
    }
    
    
    for (unsigned  int i = 0; i < args.size(); i++) {
        char** command = this->toCommand(&args[i]);
        
        if (strncmp(command[0], "test", 4) == 0  || strncmp(command[0], "[", 1) == 0){
            
            commands.push_back(new SpecCOM(command));
        } else {
            commands.push_back(new COM(command));
        }
        
    }
    
    std::string connTemp(str2);
    inQuote = false;
    first = true;
    
    for (int i = 0; i<connTemp.size(); i++) {
        char character = connTemp[i];
        if(character == '"')
            inQuote = !inQuote;
        
        else if(inQuote)
            continue;
        
        else{
            if(character == ';' || character == '(' || character == ')' || character == '>' || character == '<'){
                
                if(connTemp[i+1] == '>') {
                    connTemp.erase(connTemp.begin()+(i+1));
                    cons.push_back('@');
                } else {
                    cons.push_back(character);
                    continue;
                }
            }
            else if(character == '&' || character == '|')
                
                if(first){
                    if(character == '|' && connTemp[i+1] != '|') {
                        
                        cons.push_back('%');
                    } else {
                        first = false;
                        continue;
                    }
                } else {
                    cons.push_back(character);
                }
            first = true;
            continue;
        }
    }
    
    int front = 0;
    int back = 0;
    
    for (int i = 0; i < cons.size(); i++)
        if(cons[i] == '(')
            front++;
        else if(cons[i] == ')')
            back++;
    
    if(front != back) {
        std::cout << "Invalid entry" << std::endl;
        exit(1);
    }
            

    bool stacking = false;
    std::stack<char> conStack;
    std::stack<COM*> comStack;
    std::vector<Connector*> conVec;
    std::vector<COM*> comVec;
    int j = 0, inSpot;
    
    for(int i = 0; i < cons.size(); i++){
        if(stacking){
            if(cons[i] == '(')
                continue;
            
            else if(cons[i] == ')'){
                comStack.push(commands[j]);
                
                while(conStack.top() != '('){
                    if(conStack.top() == '|')
                        conVec.insert(conVec.begin(), new Or());
                    else if(conStack.top() == '&')
                        conVec.insert(conVec.begin(), new And());
                    else if(conStack.top() == ';')
                        conVec.insert(conVec.begin(), new Force());
                    else if(conStack.top() == '%')
                        conVec.insert(conVec.begin(), new Pipe());
                    else if(conStack.top() == '<')
                        conVec.insert(conVec.begin(), new In());
                    else if(conStack.top() == '>')
                        conVec.insert(conVec.begin(), new Out());
                    else if(conStack.top() == '@')
                        conVec.insert(conVec.begin(), new Out2());
                    
                    comVec.insert(comVec.begin(), comStack.top());
                    conStack.pop();
                    comStack.pop();
                }
                
                comVec.insert(comVec.begin(), comStack.top());
                comStack.pop();
                conStack.pop();
                comStack.push(new Paren(conVec, comVec));
                conVec.clear();
                comVec.clear();
                
                if(conStack.size() == 0){
                    stacking = false;
                    int temp = j - inSpot;
                    for(int k = 0; k <= temp; k++)
                        commands.erase(commands.begin() + (inSpot));
                    j = inSpot;
                    commands.insert(commands.begin()+(inSpot), comStack.top());
                    comStack.pop();
                }
            }
            else{
                
                conStack.push(cons[i]);
                comStack.push(commands[j]);
                j++;
            }
        }
        else{
            if(cons[i] == '|')
                connectors.push_back(new Or());
            else if(cons[i] == '&')
                connectors.push_back(new And());
            else if(cons[i] == ';')
                connectors.push_back(new Force());
            else if(cons[i] == '%')
                connectors.push_back(new Pipe());
            else if(cons[i] == '<')
                connectors.push_back(new In());
            else if(cons[i] == '>')
                connectors.push_back(new Out());
            else if(cons[i] == '@')
                connectors.push_back(new Out2());
            else if(cons[i] == '('){
                stacking = true;
                
                inSpot = j;
                conStack.push(cons[i]);
                continue;
            }
            
            j++;
        }
    }
    
    cons.clear();
    buffer.clear();
    exes.clear();
    piece.clear();
    args.clear();
    delete str2;
    for(std::vector<char*> ex : args)
        for(char* pce : ex)
            delete pce;
}


char** Parse::toCommand(std::vector<char*>* command) {
    
    char** temp = new char*[unsigned(command->size())], **here = temp;
    for (unsigned int i = 0; i < command->size(); i++) {
        here[i] = command->at(i);
    }
    
    return temp;
}

char* Parse :: pushIt(std::string buffer) {
    
    buffer.push_back('\0');
    char* cstr = new char[buffer.length()];
    buffer.copy(cstr, buffer.length(), 0);
    
    return cstr;
}


Master* Parse::build_tree(){
    
    if(connectors.size() == 0){
        this->command_tree = nullptr;
    }
    else{
        connectors[0]->set_left(commands[0]);
        connectors[0]->set_right(commands[1]);
        
        for(int i = 1; i < connectors.size(); i++){
            connectors[i]->set_left(connectors[i-1]);
            connectors[i]->set_right(commands[i+1]);
        }
        
        this->command_tree = connectors[connectors.size() - 1];
    }
    
    return this->command_tree;
}

int Parse::execute(int fdIn, int fdOut){
    
    if(command_tree == nullptr){
        return commands[0]->execute(fdIn, fdOut);
    }
    else{
        return command_tree->execute(fdIn, fdOut);
    }
}

void Parse::clear(){
    in.clear();
    commands.clear();
    connectors.clear();
    command_tree = nullptr;
}

#endif

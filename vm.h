/*
 * vm.h
 * A simple VM implementation
 * Copyright (c) 2009 Claudemiro Alves Feitosa Neto
 */
#ifndef VM_H
#define VM_H

#include "opcode.h"
#include "bytecode.h"

#include <cstdio>

#include <iostream>

using std::cout;
using std::endl;
using std::ios;
using std::cerr;


#include <fstream>

using std::ofstream;
using std::ifstream;

#include <stack>

#define MAX_PROGRAM_SIZE 256

class VM {
    public:
        VM();
        ~VM();
        int load(char *progname);
        int execute(ByteCode *);
        int run();
        void reset();
        void showBytecodes();

        int push(int value);
        int pop();
        int getop(); // get the element in stack top, but dont pop it
        void showStack();

    private:
        std::stack<int> stack;
        int pc; // program counter
        ByteCode *program[MAX_PROGRAM_SIZE];
        int current_program_size; // number of bytecodes

};

#endif


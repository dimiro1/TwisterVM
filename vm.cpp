/*
 * vm.cpp
 * Copyright (c) 2009 Claudemiro Alves Feitosa Neto
 * Edited in emacs.
 */

#include "vm.h"

VM::VM ()
{
  pc = 0;
  current_program_size = 0;
}

VM::~VM ()
{
  reset ();
}


/* load program into memory */
int 
VM::load (char *progname)
{
  ifstream infile (progname, ios::binary);
  if (!infile) 
    {
      cerr << "Cant open " << progname << endl;
      exit(1);
    }

  CompiledBytecode *cp = new CompiledBytecode ();

  infile.read ( reinterpret_cast<char *>(cp), sizeof (CompiledBytecode));
  current_program_size = cp->size;
  for (int i = 0; i < cp->size; i++)
    program[i] = &(cp->instructions[i]);

  return 0;
}

/* show bytecodes */
void 
VM::showBytecodes ()
{
  cout << "+-----------------------------+" << endl;
  cout << "|       PROGRAM BYTECODES     |" << endl;
  cout << "+----+-----------------+------+" << endl;
  cout << "| LN | OPCODE          | OPER |" << endl;
  cout << "+----+-----------------+------+" << endl;

  for ( int i = 0; i < current_program_size; i++ ) 
    {
      if( program[i]->operand != 0 )
	printf ("| %-2d | %-15s |  %-3g |", i+1, opcodeName[program[i]->opcode], program[i]->operand);
      else
	printf ("| %-2d | %-15s |      |", i+1, opcodeName[program[i]->opcode]);
      cout << endl;
    }
  cout << "+----+-----------------+------+" << endl;
  cout << "|    WRITTEN BY CLAUDEMIRO    |" << endl;
  cout << "+-----------------------------+" << endl;
}

int 
VM::execute (ByteCode *byte)
{
  int right; /* its is used in sub or div operations */
  switch (byte->opcode) 
    {
    case NOP:
      break;
    case PUSH:
      push (byte->operand);
      break;
    case POP:
      pop ();
      break;
    case ADD:
      push (pop () + pop ());
      break;
    case SUB:
      right = pop ();
      push (pop () - right);
      break;
    case MULT:
      push (pop () * pop ());
      break;
    case DIV:
      right = pop ();
      push (pop () / right);
      break;
    case PRINT:
      cout << pop ();
      break;
    case PUTS:
      cout << getop () << endl;
      break;
    case RESET:
      reset ();
      break;
    }
  return 0;
}

int 
VM::run ()
{
  for ( int i = 0; i < current_program_size; i++ ) 
    {
      execute (program[i]);
      ++pc; // increments the program counter when a bytecode is executed
    }
  return 0;
}

// empty the stack
// delete the program list
inline void 
VM::reset () 
{ 
  pc = 0; 
}

/* stack manipulation */
/* need changes */
void 
VM::showStack ()
{
  cout << "+-------+" << endl;
  cout << "| STACK |" << endl;
  cout << "+-------+" << endl;
  while (!stack.empty ()) 
    {
      printf("| %5g |\n", pop ());
    }
  cout << "+-------+" << endl;
}

/* inline because the overhead; much faster */
inline void 
VM::push (float value) 
{ 
  stack.push (value); 
}

// returns the element at top of the stack
inline float 
VM::pop () 
{ 
  float element = stack.top (); 
  stack.pop (); 
  return element; 
}

inline float 
VM::getop () 
{ 
  return stack.top (); 
}


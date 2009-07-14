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
  TwcFile *tw = new TwcFile ();
  /* magic */
  /* code len */
  /* instructions */

  /* tenta pegar o numero mágico */
  infile.read (reinterpret_cast<char *>(&tw->magic), sizeof (int));
  if (tw->magic != MAGIC_VERSION_NUM)
	 {
		cout << "not a vm file!" << endl;
		exit (1);
	 }
  infile.read (reinterpret_cast<char *>(&tw->size), sizeof (int));
  tw->alloc_instruction_section (tw->size);
  infile.read (reinterpret_cast<char *>(tw->instructions), tw->size * sizeof (Instruction));

  current_program_size = tw->size;

  program = new Instruction[tw->size];

  for (int i = 0; i < tw->size; i++)
    program[i] = tw->instructions[i]; /* verificar essa linha */

  return 0;
}


void 
VM::disassemble ()
{
  cout << "+-----------------------------+" << endl;
  cout << "|       PROGRAM BYTECODES     |" << endl;
  cout << "+----+-----------------+------+" << endl;
  cout << "| LN | OPCODE          | OPER |" << endl;
  cout << "+----+-----------------+------+" << endl;

  for ( int i = 0; i < current_program_size; i++ ) 
    {
      if( program[i].operand != 0 )
	printf ("| %-2d | %-15s |  %-3g |", i+1, opcodeName[program[i].opcode], program[i].operand);
      else
	printf ("| %-2d | %-15s |      |", i+1, opcodeName[program[i].opcode]);
      cout << endl;
    }
  cout << "+----+-----------------+------+" << endl;
  cout << "|    WRITTEN BY CLAUDEMIRO    |" << endl;
  cout << "+-----------------------------+" << endl;
}

int 
VM::execute (Instruction &instruction)
{
  int right; /* its is used in sub or div operations */
  switch (instruction.opcode) 
    {
    case NOP:
      break;
    case PUSH:
      push (instruction.operand);
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

// empty the sp
// delete the program list
inline void 
VM::reset () 
{ 
  pc = 0; 
}

/* sp manipulation */
/* need changes */
void 
VM::disassemble_sp ()
{
  cout << "+-------+" << endl;
  cout << "| SP |" << endl;
  cout << "+-------+" << endl;
  while (!sp.empty ())
	 printf("| %5g |\n", sp.top ());
  cout << "+-------+" << endl;
}

/* inline because the overhead; much faster */
inline void 
VM::push (float value) 
{ 
  sp.push (value); 
}

// returns the element at top of the sp
inline float 
VM::pop () 
{ 
  float element = sp.top (); 
  sp.pop (); 
  return element; 
}

inline float 
VM::getop () 
{ 
  return sp.top (); 
}


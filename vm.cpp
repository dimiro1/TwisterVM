/*
 * vm.cpp
 * Copyright (c) 2009 Claudemiro Alves Feitosa Neto
 * Edited in emacs.
 */

#include "vm.h"

VM::VM ()
{
  pc = 0;
  code_len = 0;
}

VM::~VM ()
{
  reset ();
}


/* load code_section into memory */
int 
VM::load (char *progname) throw (BadFileException, NotRecognizedFileException)
{
  running_file_name = progname;
  TwcFile *tw = new TwcFile ();
  ifstream infile (running_file_name, ios::binary);
  
  if (!infile.good ()) 
	 throw BadFileException (progname);

  /* tenta pegar o numero mágico */
  infile.read (reinterpret_cast<char *>(&tw->magic), sizeof (int));
  if (tw->magic != MAGIC_VERSION_NUM)
	 throw NotRecognizedFileException (progname);

  infile.read (reinterpret_cast<char *>(&tw->code_len), sizeof (int));
  tw->alloc_code_section (tw->code_len);
  infile.read (reinterpret_cast<char *>(tw->code_section), tw->code_len * sizeof (Instruction));

  code_len = tw->code_len;

  code_section = new Instruction[tw->code_len];

  /* cxarrega as instruções na TwisterVM */
  for (int i = 0; i < tw->code_len; i++)
    code_section[i] = tw->code_section[i];

  return 0;
}


void 
VM::disassemble ()
{
  /* Baseado no disasemble do lua5.1 */
  cout << " " << running_file_name 
		 << " (" << code_len 
		 << " instructions, " 
		 << sizeof (code_section) * code_len 
		 << " bytes at " 
		 << hex << code_section << ")" << endl;
  for ( int i = 0; i < code_len; i++ ) 
    {
      if( code_section[i].operand != 0 )
		  printf ("%3d %-6s %-3g", i, opcodeName[code_section[i].opcode], code_section[i].operand);
      else
		  printf ("%3d %-6s", i, opcodeName[code_section[i].opcode]);
      cout << endl;
    }
}

int 
VM::execute ()
{
  int right; /* its is used in sub or div operations */
  Instruction running;
  while (true)
	 {
		running = code_section[pc];
		switch (running.opcode) 
		  {
		  case OP_ADD:
			 push (pop () + pop ());
			 pc++;
			 break;
		  case OP_CLSP:
			 reset_sp ();
			 pc++;
			 break;
		  case OP_DIV:
			 right = pop ();
			 push (pop () / right);
			 pc++;
			 break;
		  case OP_DCARD:
			 pop ();
			 pc++;
			 break;
		  case OP_GETOP:				  /* não esta concluida */
			 top ();
			 pc++;
			 break;
		  case OP_GOTO:
			 pc = static_cast<int> (running.operand);
			 break;
		  case OP_HALT:
			 exit (0);					  /* sai normalmente */
			 break;
		  case OP_MULT:
			 push (pop () * pop ());
			 pc++;
			 break;
		  case OP_NOP:
			 pc++;
			 break;
		  case OP_POP:
			 pop ();
			 pc++;
			 break;
		  case OP_PRINT:
			 cout << pop ();
			 pc++;
			 break;
		  case OP_PUSH:
			 push (running.operand);
			 pc++;
			 break;
		  case OP_PUTS:
			 cout << top () << endl;
			 pc++;
			 break;
		  case OP_RESET:
			 reset ();
			 pc++;
			 break;
		  case OP_SUB:
			 right = pop ();
			 push (pop () - right);
			 pc++;
			 break;
		  }
	 }
  return 0; // nunca alcançado, espero!
}

// empty the sp
// reset the program counter
inline void 
VM::reset () 
{ 
  pc = 0;
  reset_sp ();
}

inline void
VM::reset_sp ()
{
  while (!sp.empty ())
	 sp.pop ();
}

/* sp manipulation */
/* need changes */
void
VM::disassemble_sp ()
{
  cout << " [ SP ] " << endl;
  while (!sp.empty ())
	 printf(" [%-4g] \n", sp.top ());
  cout << endl;
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
VM::top () 
{ 
  return sp.top (); 
}


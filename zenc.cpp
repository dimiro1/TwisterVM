/* This is the compiler. */
#include <iostream>

using std::ios;
using std::endl;
using std::cout;
using std::cerr;

#include <fstream>

using std::ofstream;
using std::ifstream;

#include <cstdlib>
#include <cstring>

#include "bytecode.h"

void 
createFile (char *progname, int size)
{
  ofstream file (progname, ios::binary);
  if (!file) 
    {
      cerr << "Cant open " << progname << endl;
      exit(1);
    }

  CompiledBytecode blank (size);
  ByteCode bt (NOP);

  for (int i = 0; i < size; i++) 
    {
      blank.instructions[i] = bt;
    }
  file.write ( reinterpret_cast<const char *>(&blank), sizeof (CompiledBytecode));
}

void 
writeData (char *progname)
{
  ofstream file (progname, ios::binary);
  if (!file) 
    {
      cerr << "Cant open " << progname << endl;
      exit (1);
    }
  // ( 1+2 ) *3 /5 * 5 + 8
  CompiledBytecode *cp = new CompiledBytecode (progname, 12);
  cp->instructions[0] = ByteCode (PUSH, 1);
  cp->instructions[1] = ByteCode (PUSH, 2);
  cp->instructions[2] = ByteCode (ADD);	  
  cp->instructions[3] = ByteCode (PUSH, 3);
  cp->instructions[4] = ByteCode (MULT);	  
  cp->instructions[5] = ByteCode (PUSH, 5);
  cp->instructions[6] = ByteCode (DIV);	  
  cp->instructions[7] = ByteCode (PUSH, 5);
  cp->instructions[8] = ByteCode (MULT);	  
  cp->instructions[9] = ByteCode (PUSH, 8);
  cp->instructions[10] = ByteCode (ADD);
  cp->instructions[11] = ByteCode (PUTS);
    

  file.seekp((0) * sizeof(CompiledBytecode));
  file.write ( reinterpret_cast<const char *>(cp), sizeof (CompiledBytecode));
}

void 
read (char *progname)
{
  ifstream infile (progname, ios::binary);
  if (!infile) 
    {
      cerr << "Cant open " << progname << endl;
      exit(1);
    }


  CompiledBytecode *cp = new CompiledBytecode();
  infile.read ( reinterpret_cast<char *>(cp), sizeof(CompiledBytecode));


  cout << "+-----------------------------+" << endl;
  printf ( "| name: %-21s |\n", cp->name);
  printf ( "| size: %-21d |\n", cp->size);
  cout << "+-----------------------------+" << endl;
  cout << "|       PROGRAM BYTECODES     |" << endl;
  cout << "+----+-----------------+------+" << endl;
  cout << "| LN | OPCODE          | OPER |" << endl;
  cout << "+----+-----------------+------+" << endl;
  for (int i = 0; i < cp->size; i++) 
    {
      if( cp->instructions[i].operand != 0 )
	printf ("| %-2d | %-15s |  %-3g |", i+1, opcodeName[cp->instructions[i].opcode], cp->instructions[i].operand);
      else
	printf ("| %-2d | %-15s |      |", i+1, opcodeName[cp->instructions[i].opcode]);
      cout << endl;
    }
  cout << "+----+-----------------+------+" << endl;
  cout << "|    WRITTEN BY CLAUDEMIRO    |" << endl;
  cout << "+-----------------------------+" << endl;
}


int 
main (int argc, char **argv)
{
  if (argc == 3) 
    {
      if (strcmp (argv[1], "-c") == 0)
	createFile (argv[2], 12);
      else if (strcmp(argv[1], "-w") == 0)
	writeData (argv[2]);
      else if(strcmp(argv[1], "-r") == 0)
	read (argv[2]);
    } 
  else
    cout << "error" << endl;
  return 0;
}

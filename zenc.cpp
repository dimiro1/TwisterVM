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
writeData (char *progname)
{
  CompiledBytecode *cp;
  ofstream file (progname, ios::binary);
  if (!file.good ()) 
    {
      cerr << "Cant open " << progname << endl;
      exit (1);
    }

  cp = new CompiledBytecode (12);
  // ( 1+2 ) *3 /5 * 5 + 8
  cp->add_instruction (ByteCode (PUSH, 1));
  cp->add_instruction (ByteCode (PUSH, 2));
  cp->add_instruction (ByteCode (ADD));
  cp->add_instruction (ByteCode (PUSH, 3));
  cp->add_instruction (ByteCode (MULT));
  cp->add_instruction (ByteCode (PUSH, 5));
  cp->add_instruction (ByteCode (DIV));
  cp->add_instruction (ByteCode (PUSH, 5));
  cp->add_instruction (ByteCode (MULT));
  cp->add_instruction (ByteCode (PUSH, 8));
  cp->add_instruction (ByteCode (ADD));
  cp->add_instruction (ByteCode (PUTS));
  

  /* magic */
  /* code len */
  /* instructions */

  /* Store name */
  file.write (reinterpret_cast<char *>(&cp->magic), sizeof (int));
  file.write (reinterpret_cast<char *>(&cp->size), sizeof (int));
  file.write (reinterpret_cast<char *>(cp->instructions), cp->size * sizeof (ByteCode));
}

void
read (char *progname)
{
  CompiledBytecode cp;
  ifstream infile (progname, ios::binary);
  if (!infile)
    {
      cerr << "Cant open " << progname << endl;
      exit(1);
    }

  /* magic */
  /* code len */
  /* instructions */

  /* tenta pegar o numero mágico */
  infile.read (reinterpret_cast<char *>(&cp.magic), sizeof (int));
  if (cp.magic != MAGIC_VERSION_NUM)
	 {
		cout << "not a vm file!" << endl;
		exit (1);
	 }
  infile.read (reinterpret_cast<char *>(&cp.size), sizeof (int));
  cp.instructions = new ByteCode[cp.size];
  infile.read (reinterpret_cast<char *>(cp.instructions), cp.size * sizeof (ByteCode));

  cout << "+-----------------------------+" << endl;
  printf ( "| size: %-21d |\n", cp.size);
  cout << "+-----------------------------+" << endl;
  cout << "|       PROGRAM BYTECODES     |" << endl;
  cout << "+----+-----------------+------+" << endl;
  cout << "| LN | OPCODE          | OPER |" << endl;
  cout << "+----+-----------------+------+" << endl;
  for (int i = 0; i < cp.size; i++)
    {
      if( cp.instructions[i].operand != 0 )
		  printf ("| %-2d | %-15s |  %-3g |", i+1, opcodeName[cp.instructions[i].opcode], cp.instructions[i].operand);
      else
		  printf ("| %-2d | %-15s |      |", i+1, opcodeName[cp.instructions[i].opcode]);
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
      if (strcmp (argv[1], "-c") == 0);
		  /* createFile (argv[2], 12); */
      else if (strcmp(argv[1], "-w") == 0)
		  writeData (argv[2]);
      else if(strcmp(argv[1], "-r") == 0)
		  read (argv[2]);
    } 
  else
    cout << "error" << endl;
  return 0;
}

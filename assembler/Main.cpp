#include "Scanner.h"
#include "Parser.h"

#include <iostream>
using std::ios;
using std::endl;
using std::cout;
using std::cerr;

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <string>
using std::string;

void 
writeData (string progname, CompiledBytecode *cp)
{
  ofstream file (progname.c_str(), ios::binary);
  file.write (reinterpret_cast<char *>(&cp->magic), sizeof (int));
  file.write (reinterpret_cast<char *>(&cp->size), sizeof (int));
  file.write (reinterpret_cast<char *>(cp->instructions), cp->size * sizeof (ByteCode));
  file.close ();
}


int
main (int argc, char **argv)
{
  Scanner *scanner;
  Parser *parser;

  scanner = new Scanner(fopen (argv[1], "r"));
  parser = new Parser(scanner);
  parser->cp = new CompiledBytecode ();
  parser->Parse();
  
  writeData ("out.zenc", parser->cp);

  delete parser;
  delete parser->cp;
  delete scanner;

  return 0;
}

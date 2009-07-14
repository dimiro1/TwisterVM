#include "Scanner.h"
#include "Parser.h"

#include <iostream>
using std::ios;
using std::endl;
using std::cout;
using std::cerr;

#include <string>
using std::string;

int
main (int argc, char **argv)
{
  Scanner *scanner;
  Parser *parser;

  scanner = new Scanner (fopen (argv[1], "r"));
  parser = new Parser (scanner);
  parser->gen = new AsmGen ("out.zenc");
  parser->Parse ();
  
  /* escreve assembled_code em arquivo */
  parser->gen->write_to_file ();

  delete parser;
  delete parser->gen;
  delete scanner;

  return 0;
}

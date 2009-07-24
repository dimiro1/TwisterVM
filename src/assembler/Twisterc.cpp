/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-24 13:31:15 BRT>
 */

#include "Scanner.h"
#include "Parser.h"

#include <iostream>
using std::ios;
using std::endl;
using std::cout;
using std::cerr;

#include <string>
using std::string;

#include <getopt.h>

void
show_usage ()
{

  fprintf (stderr,
  "usage: assembler [options] [asmfile].\n"
  "Available options are:\n"
  "  -o <outfilename> \tplace the output in <outfilename>\n"
  "  -[h?]\t\t\tshow this help\n");
  fflush (stderr);
}

int
main (int argc, char **argv)
{
  bool hflag = false;
  int c;
  Scanner *scanner;
  Parser *parser;
  string out_file_name = "out.twc";

  while ( (c = getopt( argc, argv, "ho:")) != -1) {
	 switch( c ) {
	 case 'o':
		out_file_name = optarg;
		break;
	 case 'h':
	 case '?':
		hflag = true;
		break;
	 default:
		hflag = true;
		break;
	 }
  }

  argv += optind;
  if (argc < 2 || hflag)
	 {
		show_usage ();
		exit (1);
	 }
  else
	 {
		scanner = new Scanner (fopen (argv[0], "r"));
		parser = new Parser (scanner);
		parser->gen = new AsmGen (out_file_name);
		parser->Parse ();

		/* escreve assembled_code em arquivo */
		parser->gen->assemble ();
		delete parser;
		delete parser->gen;
		delete scanner;
	 }
  return 0;
}

/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-24 21:41:23 BRT>
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

class TwistercMain {
public:
  TwistercMain ()
	 : hflag (false),
		cflag (false),
		vflag (false),
		out_file_name ("out.twc") {}

  ~TwistercMain ()
  {
	 delete parser;
	 delete parser->gen;
	 delete scanner;
  }

  void main (int argc, char **argv);
  void show_copyright ();
  void show_usage ();
  void show_version ();
private:
  Scanner *scanner;
  Parser *parser;
  string out_file_name;
  bool hflag;
  bool cflag;
  bool vflag;
};

inline void TwistercMain::show_copyright ()
{
  cout << "TwisterCompiler - Copyright (C) 2009 Claudemiro Alves Feitosa Neto" << endl;
}

inline void TwistercMain::show_version ()
{
  cout << "TwisterCompiler v" << VM_VERSION_MAJOR
		 << "." << VM_VERSION_MINOR << endl;
}

void TwistercMain::show_usage ()
{
  cerr << "usage: assembler [options] [twfile]." << endl
		 << "Available options are:" << endl
		 << "  -o <outfilename> \tplace the output in <outfilename>" << endl
		 << "  -c\t\t\tshow copyright" << endl
		 << "  -v\t\t\tshow version" << endl
		 << "  -[h?]\t\t\tshow this help" << endl;
}

void TwistercMain::main (int argc, char **argv)
{
  int c;

  while ( (c = getopt( argc, argv, "vcho:")) != -1)
	 {
		switch (c)
		  {
		  case 'o':
			 out_file_name = optarg;
			 break;
		  case 'h':
		  case '?':
			 hflag = true;
			 break;
		  case 'c':
			 cflag = true;
			 break;
		  case 'v':
			 vflag = true;
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
  else if (cflag)
	 {
		show_copyright ();
		exit (1);
	 }
  else if (vflag)
	 {
		show_version ();
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
	 }
}

int
main (int argc, char **argv)
{
  TwistercMain compiler;
  compiler.main (argc, argv);
  return 0;
}


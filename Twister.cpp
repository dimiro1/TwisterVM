#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include "vm.h"

static char *execname; // executable name

inline void
showCopyright ()
{
  cout << "TwisterVm - Copyright (C) 2009 Claudemiro Alves Feitosa Neto" << endl;
}

void
showUsage ()
{

  fprintf(stderr,
  "usage: %s [options] [script file].\n"
  "Available options are:\n"
  "  -d [disassemble] \t\tdisassemble code\n"
  "  -h [help]\t\t\tshow this help\n"
  "  -c [copyright]\t\tcopyright information\n\n"
  ,
  execname);
  fflush(stderr);
  showCopyright();
}

/* execute, disassemble, help and copyright flags */
int eflag, dflag, hflag, cflag;

int
main (int argc, char **argv)
{
  VM vm; // instantiate a new vm
  int option_index = 0;
  int c;

  execname = argv[0];

  static struct option long_options[] = {
	 {"copyright",   no_argument, 0, 'c'      },
	 {"disassemble", no_argument, 0, 'd'},
	 {"help",        no_argument, 0, 'h'      },
	 {0,0,0,0}
  };

  eflag = 1;
  while( (c = getopt_long( argc, argv, "cdh", long_options, &option_index )) != -1) {
	 switch( c ) {
	 case 'c':
		cflag = 1;
		break;
	 case 'd':
		eflag = 0;
		dflag = 1;
		break;
	 case 'h':
	 case '?':
		hflag = 1;
		break;
	 default:
		hflag = 1;
		break;
	 }
  }

  argv += optind;
  if (argc < 2)
	 {
		showUsage ();
		exit (0);
	 }
  if (cflag)
	 {
		showCopyright ();
		exit (0);
	 }
  if (hflag)
	 {
		showUsage ();
		exit (0);
	 }
  else
	 {
		try {
		  vm.load (argv[0]);
		} catch (NotRecognizedFileException e) {
		  cout << e.what () << endl;
		} catch (BadFileException e) {
		  cout << e.what () << endl;
		}

		if (dflag)
		  vm.disassemble ();
		if (eflag)
		  vm.execute ();
	 }
  return 0;
}

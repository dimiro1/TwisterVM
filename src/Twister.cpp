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
  "  -l [list] \t\tlist code\n"
  "  -h [help]\t\tshow this help\n"
  "  -c [copyright]\tcopyright information\n\n"
  ,
  execname);
  fflush(stderr);
  showCopyright();
}

/* execute, list, help and copyright flags */
bool eflag, lflag, hflag, cflag;

int
main (int argc, char **argv)
{
  VM vm; // instantiate a new vm
  int option_index = 0;
  int c;

  execname = argv[0];

  static struct option long_options[] = {
	 {"copyright",   no_argument, 0, 'c'      },
	 {"list", no_argument, 0, 'd'},
	 {"help",        no_argument, 0, 'h'      },
	 {0,0,0,0}
  };

  eflag = true;
  while( (c = getopt_long( argc, argv, "clh", long_options, &option_index )) != -1) {
	 switch( c ) {
	 case 'c':
		cflag = true;
		break;
	 case 'l':
		eflag = false;
		lflag = true;
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
  if (argc < 2 || hflag )
	 {
		showUsage ();
		exit (0);
	 }
  if (cflag)
	 {
		showCopyright ();
		exit (0);
	 }
  else
	 {
		try
		  {
			 vm.load (string (argv[0]));
		  } 
		catch (NotRecognizedFileException e)
		  {
			 cout << e.what () << endl;
		  } 
		catch (BadFileException e) 
		  {
			 cout << e.what () << endl;
		  }

		if (lflag)
		  vm.list ();
		if (eflag)
		  vm.execute ();
	 }
  return 0;
}

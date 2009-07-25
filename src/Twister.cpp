/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-24 21:41:33 BRT>
 */

#include "global.h"
#include "vm.h"
#include <getopt.h>

class TwisterMain {
public:
  TwisterMain ()
	 : eflag (true),
		vflag (false),
		lflag (false),
		hflag (false),
		cflag (false) {}

  void main (int argc, char **argv);
  void show_copyright ();
  void show_usage ();
  void show_version ();
private:
  VM vm;
  string stream_name;
  /* execute, version, list, help and copyright flags */
  bool eflag;
  bool vflag;
  bool lflag;
  bool hflag;
  bool cflag;
};

void TwisterMain::main (int argc, char **argv)
{
  int option_index = 0;
  int c;

  static struct option long_options[] = {
	 {"copyright", no_argument, 0, 'c'},
	 {"list", no_argument, 0, 'l'},
	 {"version", no_argument, 0, 'v'},
	 {"help", no_argument, 0, 'h'},
	 {0, 0, 0, 0}
  };

  while ( (c = getopt_long ( argc, argv, "vclh",
									  long_options, &option_index )) != -1)
	 {
		switch (c)
		  {
		  case 'c':
			 cflag = true;
			 break;
		  case 'v':
			 vflag = true;
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

  stream_name = argv[0];
  argv += optind;
  if (argc < 2 || hflag )
	 {
		show_usage ();
		exit (0);
	 }
  if (cflag)
	 {
		show_copyright ();
		exit (0);
	 }
  if (vflag)
	 {
		show_version ();
		exit (0);
	 }
  else
	 {
		try {
		  vm.load (string (argv[0]));
		}
		catch (NotRecognizedFileException e) {
		  cout << e.what () << endl;
		}
		catch (BadFileException e) {
		  cout << e.what () << endl;
		}

		if (lflag)
		  vm.list ();
		if (eflag)
		  vm.execute ();
	 }
}

inline void TwisterMain::show_version ()
{
    cout << "TwisterVm v" << VM_VERSION_MAJOR
         << "." << VM_VERSION_MINOR
#ifdef HAVE_COMPUTED_GOTO
         << " (Computed goto activated)" << endl;
#else
         << " (Computed goto desactivated)" << endl;
#endif

}

inline void TwisterMain::show_copyright ()
{
  cout << "TwisterVm - Copyright (C) 2009 Claudemiro Alves Feitosa Neto" << endl;
}

void TwisterMain::show_usage ()
{
  cerr << "usage: " << stream_name << " [options] [twcfile]." << endl
		 << "Available options are:" << endl
		 << "  -l [list] \t\tlist code" << endl
		 << "  -v [version] \tshow version" << endl
		 << "  -h [help]\t\tshow this help" << endl
		 << "  -c [copyright]\tcopyright information" << endl << endl;
  show_copyright ();
}

int
main (int argc, char **argv)
{
  TwisterMain tw;
  tw.main (argc, argv);
  return 0;
}

#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include "vm.h"

static char *execname; // executable name

inline void showCopyright() { cout << "zen - Copyright (C) 2009 Claudemiro Alves Feitosa Neto" << endl; }

void showUsage()
{

  fprintf(stderr,
  "usage: %s [options] [script file].\n"
  "Available options are:\n"
  "  -d [disassemble] filename\tdisassemble code\n"
  "  -e [execute] filename\t\texecute filename\n"
  "  -s [stack] filename\t\tshow initial stack\n"
  "  -h [help]\t\t\tshow this help\n"
  "  -c [copyright]\t\tcopyright information\n\n"
  ,
  execname);
  fflush(stderr);
  showCopyright();

}

int main(int argc, char **argv)
{
    VM vm; // instantiate a new vm

    execname = argv[0];

    static struct option long_options[] = {
        {"copyright",   no_argument, 0, 'c'      },
        {"disassemble", required_argument, 0, 'd'},
        {"execute",     required_argument, 0, 'e'},
        {"help",        no_argument, 0, 'h'      },
        {0,0,0,0}
    };

    int option_index = 0;
    int c;

    while( (c = getopt_long( argc, argv, "cd:e:h", long_options, &option_index )) != -1) {
        switch( c ) {
            case 'c':
                showCopyright();
                break;
            case 'd':
                vm.load(optarg);
                vm.showBytecodes();
                break;
            case 'e':
                vm.load(optarg);
                vm.run();
                break;
            case 'h':
            case '?':
                showUsage();
                break;
            default:
                abort();
                break;
       }
    }
    return 0;
}


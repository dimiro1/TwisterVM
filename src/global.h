/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-25 17:04:03 BRT>
 */

/* Mão modifique a sequencia de includes. */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* version */
#define VM_VERSION_MAJOR 0
#define VM_VERSION_MINOR 5

#define MAGIC_VERSION_NUM 0x05 // version 0.5
#define EOS '\0'

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;

#include <fstream>
using std::ifstream;

#include <iomanip>
using std::hex;
using std::dec;
using std::setprecision;

#include <string>
using std::string;

#include <cstring>
#include <cstdlib>

/* Exceptions */
#include <new>
using std::bad_alloc;
#include <stdexcept>
using std::out_of_range;

#include <map>
#include <vector>

#include "not_recognized_file_exception.h"
#include "bad_file_exception.h"

#include <cmath>
#include "error.h"

/* VM types */
#include "types.h"

#endif /* _GLOBAL_H_ */

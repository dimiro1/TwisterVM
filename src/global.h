/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-20 14:23:33 BRT>
 */

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <dispatch_config.h>

/* version */
#define VM_VERSION_MAJOR 0
#define VM_VERSION_MINOR 2

#define MAGIC_VERSION_NUM 0x02 // version 0.2
#define EOS '\0'

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;

#include <iomanip>
using std::hex;
using std::dec;

#include <string>
using std::string;

#include <cstring>
#include <cstdlib>

/* Exceptions */
#include <new>
using std::bad_alloc;

#include "not_recognized_file_exception.h"
#include "bad_file_exception.h"


#endif /* _GLOBAL_H_ */

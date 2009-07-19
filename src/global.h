/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-18 21:37:45 BRT>
 */

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define MAGIC_VERSION_NUM 0x01 // version 0.1
#define EOS '\0'

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::cerr;

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

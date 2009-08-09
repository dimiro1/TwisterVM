/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-08-09 19:16:31 BRT>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licences>
 */

/* Mão modifique a sequencia de includes. */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* version */
#define VM_VERSION_MAJOR 0
#define VM_VERSION_MINOR 6
#define VM_VERSION_PATH 4

#define MAGIC_VERSION_NUM 0x06
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
#include <ctime>

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

#include "IO.h"

#endif /* _GLOBAL_H_ */

/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 19:40:41 BRT>
 */

#include <iostream>
using std::cerr;
using std::endl;

#ifndef _ERRORS_H_
#define _ERRORS_H_

enum ERRORS
{
  OUT_OF_RANGE,
  ZERO_DIVISION,
  COMMAND_NOT_FOUND,				  /* system */
  ENV_NOT_FOUND
};

class Error {
public:
  void emit (const ERRORS err);
};


#endif /* _ERRORS_H_ */

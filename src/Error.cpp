/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-18 14:06:56 BRT>
 */

#include "Error.h"

void Error::emit (ERRORS err)
{
  switch (err)
	 {
	 case OUT_OF_RANGE:
		cerr << "error: invalid index. (out_of_range)" << endl;
		break;
	 case ZERO_DIVISION:
		cerr << "error: division by zero." << endl;
		break;
	 }
}

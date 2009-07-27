/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-27 09:38:05 BRT>
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

#include "error.h"

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
	 case COMMAND_NOT_FOUND:
		cerr << "error: command not found." << endl;
		break;
	 case ENV_NOT_FOUND:
		cerr << "error: environment variable not found." << endl;
		break;
	 }
}

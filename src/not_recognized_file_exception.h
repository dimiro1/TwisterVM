/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 19:47:11 BRT>
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

#ifndef _NOT_RECOGNIZED_FILE_EXCEPTION_H_
#define _NOT_RECOGNIZED_FILE_EXCEPTION_H_

#include <string>
using std::string;

#include <sstream>
using std::ostringstream;


class NotRecognizedFileException {
public:
  NotRecognizedFileException (const string file_name)
  {
	 ostringstream temp;
	 temp << "\"" << file_name << "\"" << " is not a valid file!";
	 msg = temp.str ();
  }

  NotRecognizedFileException (char *file_name)
  {
	 ostringstream temp;
	 temp << "\"" << file_name << "\"" << " is not a valid file!";
	 msg = temp.str ();
  }

  inline string what () { return msg; }

private:
  string msg;
};



#endif /* _NOT_RECOGNIZED_FILE_EXCEPTION_H_ */

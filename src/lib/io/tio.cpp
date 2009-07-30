/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-07-29 21:55:08 BRT>
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

#include "tio.h"

void TIO::print_num (const double n, bool has_new_line)
{
  cout << n;
  if (has_new_line)
	 cout << endl;
}

void TIO::print_string (const string s, bool has_new_line)
{
  cout << s;
  if (has_new_line)
	 cout << endl;
}

void TIO::read_num (double &n)
{
  cin >> n;
}

void TIO::read_string (string &s)
{
  cin >> s;
}

/*
 *   Copyright (C) 2009 by Claudemiro Alves Feitosa Neto
 *   <dimiro1@gmail.com>
 *   Modified: <2009-08-18 23:05:35 BRT>
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

#include "VM.h"

TwisterVM::~TwisterVM ()
{
  delete current_context;
}

void TwisterVM::run ()
{
  dispatch ();
}

/* load code_section into memory */
void TwisterVM::load (const string progname)
{
  current_context = new ExecContext ();

  try {
	 current_context->load_file (progname);
  }
  catch (BadFileException e) {
	 cerr << e.what () << endl;
	 abort ();
  }
  catch (NotRecognizedFileException e) {
	 cerr << e.what () << endl;
	 abort ();
  }
  catch (bad_alloc e) {
	 cerr << e.what () << endl;
	 abort ();
  }
}


void TwisterVM::list () const
{
  auto Instruction current;

  cout << " twisterc v" << current_context->header.major_version
       << "." << current_context->header.minor_version
       << "." << current_context->header.path_version
       << " (" << current_context->header.code_len
       << " instructions)" << endl;
  for (int i = 0; i < current_context->header.code_len; i++)
	 {
      current = current_context->code_section[i];
      cout << std::setw (3) << i << ": "
           << mneumonic[current.opcode] << " ";
      switch (current.opcode)
		  {
        case OP_STORE_S:
          cout << "\"" << current_context->get_string(current.A)
               << "\" $" << current.C;
          break;
        case OP_PUT_S: case OP_PRINT_S:
          cout << "$" << current.A;
          break;
        case OP_STORE_N:
          cout  << current_context->get_num (current.A)
                << " $" << current.C;
          break;
        case OP_PUT_N: case OP_PRINT_N:
          cout << "$" << current.A;
          break;
        case OP_CONCAT_S:
          cout  << "$" << current.A
                << " $" << current.B
                << " $" << current.C ;
          break;
        case OP_MOV_N: case OP_MOV_S:
          cout  << "$" << current.A
                << " $" << current.C ;
          break;
        case OP_INPUT_N: case OP_INPUT_S:
          cout  << "$" << current.C;
          break;
        case OP_GOTO:
          cout << current.A;
          break;
        case OP_SYSTEM_S:
          cout << "$" << current.A;
          break;
        case OP_RAND_N:
          cout << "$" << current.C;
          break;
        case OP_GETENV_S:
          cout << "$" << current.A
               << " $" << current.C;
          break;
        case OP_ADD_N:  case OP_SUB_N:
        case OP_MULT_N: case OP_DIV_N:
        case OP_MOD_N:
          cout  << "$" << current.A
                << " $" << current.B
                << " $" << current.C ;
          break;
        case OP_POW_N:
          cout  << "$" << current.A
                << " $" << current.C ;
          break;
        case OP_NEG_N:
          cout  << "$" << current.A;
          break;
        case OP_ABS_N:  case OP_SIN_N:
        case OP_COS_N:  case OP_TAN_N:
        case OP_ASIN_N: case OP_ACOS_N:
        case OP_ATAN_N: case OP_LOG_N:
        case OP_SQRT_N: case OP_CEIL_N:
        case OP_FLOOR_N:
          cout  << "$" << current.A
                << " $" << current.C ;
          break;
        case OP_INC_N:
          cout  << "$" << current.A;
          break;
        case OP_DEC_N:
          cout  << "$" << current.A;
          break;
        case OP_CHARAT_S:
          cout << current_context->get_string (current.A)
               << " " << current.B << " $" << current.C;
          break;
		  case OP_ZERO_N: case OP_NOT_ZERO_N:
          cout  << "$" << current.A
                << " " << current.C;
          break;
        case OP_LT_S:
        case OP_GT_S:
        case OP_LTE_S:
        case OP_GTE_S:
        case OP_EQ_S:
        case OP_NOT_LT_S:
        case OP_NOT_GT_S:
        case OP_NOT_LTE_S:
        case OP_NOT_GTE_S:
        case OP_NOT_EQ_S:
        case OP_LT_N:
        case OP_GT_N:
        case OP_LTE_N:
        case OP_GTE_N:
        case OP_EQ_N:
        case OP_NOT_LT_N:
        case OP_NOT_GT_N:
        case OP_NOT_LTE_N:
        case OP_NOT_GTE_N:
        case OP_NOT_EQ_N:
          cout  << "$" << current.A
                << " $" << current.B
                << " " << current.C;
          break;
		  }
      cout << endl;
	 }
}

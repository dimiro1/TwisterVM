#ifndef _BAD_FILE_EXCEPTION_H_
#define _BAD_FILE_EXCEPTION_H_

#include <string>
using std::string;

#include <sstream>
using std::ostringstream;

class BadFileException {
public:
  BadFileException (string file_name)
  {
	 ostringstream temp;
	 temp << "\"" << file_name << "\"" << " could not be open!";
	 msg = temp.str ();
  }

  BadFileException (char *file_name)
  {
	 ostringstream temp;
	 temp << "\"" << file_name << "\"" << " could not be open!";
	 msg = temp.str ();
  }
  
  inline string what () { return msg; }

private:
  string msg;
};


#endif /* _BAD_FILE_EXCEPTION_H_ */

#ifndef _BAD_FILE_EXCEPTION_H_
#define _BAD_FILE_EXCEPTION_H_

#include <string>
using std::string;

class BadFileException {
public:
  BadFileException (string file_name)
  {
	 msg = "Can't open file.";
  }

  BadFileException (char *file_name)
  {
	 msg = "Can't open file.";
  }
  
  string what ()
  {
	 return msg;
  }

private:
  string msg;
};


#endif /* _BAD_FILE_EXCEPTION_H_ */

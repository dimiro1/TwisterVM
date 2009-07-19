#ifndef _NOT_RECOGNIZED_FILE_EXCEPTION_H_
#define _NOT_RECOGNIZED_FILE_EXCEPTION_H_

#include <string>
using std::string;

#include <sstream>
using std::ostringstream;


class NotRecognizedFileException {
public:
  NotRecognizedFileException (string file_name)
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

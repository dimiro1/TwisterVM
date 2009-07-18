#ifndef _NOT_RECOGNIZED_FILE_EXCEPTION_H_
#define _NOT_RECOGNIZED_FILE_EXCEPTION_H_

#include <string>
using std::string;

class NotRecognizedFileException {
public:
  NotRecognizedFileException (string file_name)
  {
  	 msg = "Not recognized file.";
  }

  NotRecognizedFileException (char *file_name)
  {
  	 msg = "Not recognized file.";
  }
  
  string what ()
  {
	 return msg;
  }

private:
  string msg;
};



#endif /* _NOT_RECOGNIZED_FILE_EXCEPTION_H_ */

#include <exception>
#include <string>

using namespace std;

struct QueryException : public exception
{
   string error;
   
   QueryException(string default) : error(default) {
   
   }
   
   ~QueryException() throw () {
   
   } 
   
   const char* what() const throw() { 
	   return error.c_str(); 
   }
};
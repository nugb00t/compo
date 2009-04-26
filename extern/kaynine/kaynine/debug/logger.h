/*******************************************************//**
       
	@file

	@brief	String conversion functions (covered in test/LoggerTest.*)

	@date	16.09.2004

	@author Andrew S. Gresyk

*//********************************************************/
#ifndef _KN_LOGGER_INCLUDED_
#define _KN_LOGGER_INCLUDED_

#include <tchar.h>

#ifndef UNUSED
# define UNUSED(x)
#endif


namespace kaynine {

	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Logger
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Logger {
protected:
	FILE*		file_;
	time_t		tZero_;


public:
	explicit Logger(const TCHAR* path, bool append = false);
	~Logger();


	/**
		@brief	Log the string 

		@param	format specificators
		@param	data
	*/
	void writeF(const char* file, const int line, const char* func, const TCHAR* format, ...);
	void writeFLF(const char* file, const int line, const char* func, const TCHAR* format, ...);


	/**
		@brief	Log the string without FLF part

		@param	format specificators
		@param	data
	*/
	void write(const TCHAR* format, ...);
};


} //namespace kaynine


#endif //_KN_LOGGER_INCLUDED_
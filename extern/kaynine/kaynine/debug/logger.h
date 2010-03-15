#pragma once

#include <tchar.h>

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Logger {
protected:
	FILE*		file_;
	time_t		tZero_;

public:
	explicit Logger(const TCHAR* path, bool append = false);
	~Logger();

	void write(const TCHAR* format, ...);
	void writeF(const char* file, const int line, const char* func, const TCHAR* format, ...);
	void writeFLF(const char* file, const int line, const char* func, const TCHAR* format, ...);
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

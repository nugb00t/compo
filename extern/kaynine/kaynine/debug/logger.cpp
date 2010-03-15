// crt
#include <assert.h>
#include <stdarg.h>
#include <time.h>
#include <stdio.h>

#include "logger.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

kaynine::Logger::Logger(const TCHAR* path, bool append UNUSED(= false))
: tZero_(::time(NULL)) {
	file_ = ::_tfopen(path, append ? _T("at") : _T("wt"));
	if (!file_)
		assert(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

kaynine::Logger::~Logger() {
	if (file_)
		::fclose(file_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kaynine::Logger::write(const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	::_vftprintf(file_, format, args);

	va_end(args);
	::fflush(file_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kaynine::Logger::writeF(const char* /*file*/, const int /*line*/, const char* func, const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	::fprintf(file_, "%10d | %s(): ", ::time(NULL) - tZero_, func);
	::_vftprintf(file_, format, args);

	va_end(args);
	::fflush(file_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kaynine::Logger::writeFLF(const char* file, const int line, const char* func, const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	::fprintf(file_, "%10d | %s[%d] %s(): ", ::time(NULL) - tZero_, file, line, func);
	::_vftprintf(file_, format, args);

	va_end(args);
	::fflush(file_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

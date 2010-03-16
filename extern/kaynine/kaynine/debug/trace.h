#pragma once

// std
#include <stdarg.h>		// vargs
#include <time.h>
// win
#include <windows.h>	// OutputDebugString()
#include <winbase.h>	// OutputDebugString()

#include "../threading/sync_wrappers.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Trace {
	static const unsigned TRACE_LINE_LENGTH = 1024;
	
public:
	enum Level {
		LEVEL_INFO,
		LEVEL_WARNING,
		LEVEL_ERROR,
		LEVEL_COUNT
	};
	
	static const WORD COLORS[LEVEL_COUNT];

public:
	Trace(const Level level = LEVEL_INFO);
	~Trace();
	
private:
	Trace& operator =(const Trace&);

public:
	void setLevel(const Level level) { level_ = level; }
	
	void output(const char* file, const int line, const char* func, const Level level, const TCHAR* format, ...);
	void print(const char* file, const int line, const char* func, const Level level, const TCHAR* format, ...);
	
private:
	const time_t zero_;
	const HANDLE handle_;
	Level level_;
	CriticalSection guard_;
};

TCHAR* errorString(const DWORD code);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

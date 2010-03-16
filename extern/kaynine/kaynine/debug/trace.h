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
	static const unsigned TRACE_LINE_LENGTH = 4096;
	
public:
	enum Level {
		LEVEL_NOTICE,
		LEVEL_GOOD,
		LEVEL_WARNING,
		LEVEL_ERROR,
		LEVEL_COUNT
	};
	
	static const WORD COLORS[LEVEL_COUNT];

public:
	Trace(const Level level = LEVEL_NOTICE);
	~Trace();
	
private:
	Trace& operator =(const Trace&);

public:
	void setLevel(const Level level) { level_ = level; }
	
	void output(const char* file, const int line, const char* func, const Level level, const TCHAR* format, ...);
	void print(const char* file, const int line, const char* func, const Level level, const TCHAR* format, ...);
	
	static const TCHAR* errorString(const DWORD code);

private:
	const time_t zero_;
	const HANDLE handle_;
	Level level_;
	CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}

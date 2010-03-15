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
		LEVEL_CRITICAL,
		LEVEL_COUNT
	};
	
	static const WORD COLORS[LEVEL_COUNT];

	
public:
	Trace(const Level level = LEVEL_INFO);
	
private:
	Trace& operator =(const Trace&);

public:
	void setLevel(const Level level) { level_ = level; }
	
	void output(const char* file, const int line, const char* func, const Level level, const char* format, ...);
	void print(const char* file, const int line, const char* func, const Level level, const char* format, ...);
	
private:
	const time_t zero_;
	const HANDLE handle_;
	Level level_;
	CriticalSection guard_;
};

#ifdef KN_USE_TRACE
#define KN_TRACE(l, x)	kaynine::TraceAF(__FILE__, __LINE__, __FUNCTION__, l, x)
#else
#define KN_TRACE(l, x)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void TraceF(const char* file, const int line, const char* func, const TCHAR* format, ...);
//void Trace(const char* file, const int line, const char* func, const char* format, ...);

//void Trace(const TCHAR* format, ...);
//void TraceA(const char* format, ...);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

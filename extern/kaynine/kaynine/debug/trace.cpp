//#include <kaynine/string_tools/tstring.h>
//#include <kaynine/string_tools/string_conv.h>

#include "trace.h"
#include "../threading/sync_wrappers.h"

#include <stdio.h>
#include <tchar.h>
#include <dxerr.h>

using namespace kaynine;

namespace {

	const WORD colors[Trace::LEVEL_COUNT] = {
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,	// LEVEL_NOTICE
		FOREGROUND_GREEN | FOREGROUND_BLUE,						// LEVEL_EVENT
		FOREGROUND_GREEN,										// LEVEL_GOOD
		FOREGROUND_RED | FOREGROUND_GREEN,						// LEVEL_WARNING
		FOREGROUND_RED,											// LEVEL_ERROR
	};

	CriticalSection guard;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Trace::Trace(const Level level /*= LEVEL_INFO*/) 
: zero_(::time(0)), handle_(::GetStdHandle(STD_OUTPUT_HANDLE)), level_(level) {
	assert(handle_);
	
#if 0	// _WIN32_WINNT >= 0x0600
	CONSOLE_FONT_INFOEX fontInfo = {
		sizeof(fontInfo),
		5,
		{ 8, 8 },
		FF_DONTCARE,
		400,
		L"Terminal"
	};
	
	DEBUG_ONLY(const BOOL ok =)
	::SetCurrentConsoleFontEx(handle_, FALSE, &fontInfo);
	assert(ok);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Trace::~Trace() {
	::SetConsoleTextAttribute(handle_, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void Trace::output(const char* file, const int line, const char* func, const Level level, const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	if (level < level_)
		return;
		
	AutoLock<> lock(guard_);

	static char formatted[TRACE_LINE_LENGTH];
	static char full[TRACE_LINE_LENGTH];

	printf(reinterpret_cast<char*>(formatted), format, args);
	if (file && func)
		printf(full, _T(">%10d @ %s[%d] %s()$ %s"), ::time(0) - zero_, file, line, func, formatted);
	else if (file)
		printf(full, _T(">%10d @ %s[%d] %s()$ %s"), ::time(0) - zero_, file, line, formatted);
	else if (func)
		printf(full, _T(">%10d @ %s[%d] %s()$ %s"), ::time(0) - zero_, func, formatted);
	else
		printf(full, _T(">%10d @ %s[%d] %s()$ %s"), ::time(0) - zero_, formatted);

	::OutputDebugStringA(reinterpret_cast<char*>(full));

	va_end(args);
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Trace::print(const char* file, 
				  const int line, 
				  const char* func, 
				  const Level level,
				  const Source source,
				  const unsigned error,
				  const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	if (level < level_)
		return;

	AutoLock<> lock(guard);
	
	::SetConsoleTextAttribute(handle_, colors[level]);
	
	_ftprintf(stderr, _T("[%10d] "), ::time(0) - zero_);

#ifdef UNICODE
	if (file)
		_ftprintf(stderr, _T("[%20S:%3d] "), file, line);

	if (func)
		_ftprintf(stderr, _T("%40S() | "), func);
#else
	if (file)
		_ftprintf(stderr, "[%20s:%3d] ", file, line);

	if (func)
		_ftprintf(stderr, "%40s(): ", func);
#endif

	::SetConsoleTextAttribute(handle_, colors[level] | FOREGROUND_INTENSITY);

	_vftprintf(stderr, format, args);
	
	if (level >= LEVEL_WARNING && error) {
		::SetConsoleTextAttribute(handle_, FOREGROUND_RED | FOREGROUND_INTENSITY);
		_ftprintf(stderr, _T(" #%d: %s"), error, errorString(source, error));
		::DebugBreak();
	} else
		_ftprintf(stderr, _T("\n"));

	// for the possible assertion reports
	::SetConsoleTextAttribute(handle_, FOREGROUND_RED | FOREGROUND_INTENSITY);

	va_end(args);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR* Trace::errorString(const Source source, const DWORD code) {
	static const unsigned BUFFER_LENGTH = 1024;
	static TCHAR buffer[BUFFER_LENGTH];

	switch (source) {
		case SOURCE_NONE:
			return NULL;

		case SOURCE_GEN:
			return _tcserror(code);
			break;

		case SOURCE_WIN:
			::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, BUFFER_LENGTH, NULL);
			break;

		case SOURCE_D3D:
			_sntprintf(buffer, BUFFER_LENGTH, _T("%s (%s)"), ::DXGetErrorString(code), ::DXGetErrorDescription(code));
			break;

		default:
			assert(false);
	}
					
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

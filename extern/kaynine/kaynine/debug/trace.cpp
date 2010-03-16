//#include <kaynine/string_tools/tstring.h>
//#include <kaynine/string_tools/string_conv.h>

#include <kaynine/debug/trace.h>

#include <stdio.h>
#include <tchar.h>

using namespace kaynine;

const WORD Trace::COLORS[LEVEL_COUNT] = {
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,	// LEVEL_INFO
	FOREGROUND_RED | FOREGROUND_GREEN,						// LEVEL_WARNING
	FOREGROUND_RED,											// LEVEL_ERROR
};

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Trace::print(const char* file, const int line, const char* func, const Level level, const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	if (level < level_)
		return;

	AutoLock<> lock(guard_);
	
	::SetConsoleTextAttribute(handle_, COLORS[level]);
	
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

	::SetConsoleTextAttribute(handle_, COLORS[level] | FOREGROUND_INTENSITY);

	_vftprintf(stderr, format, args);
	
	const DWORD error = ::GetLastError();
	if (level >= LEVEL_WARNING && error) {
		::SetConsoleTextAttribute(handle_, FOREGROUND_RED | FOREGROUND_INTENSITY);
		_ftprintf(stderr, _T(" #%d: %s"), error, errorString(error));
	} else
		_ftprintf(stderr, _T("\n"));

	va_end(args);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const TCHAR* Trace::errorString(const DWORD code) {
	static const unsigned BUFFER_LENGTH = 1024;
	static TCHAR buffer[BUFFER_LENGTH];

	::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, BUFFER_LENGTH, NULL);
					
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

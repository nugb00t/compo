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
	FOREGROUND_RED | FOREGROUND_INTENSITY,					// LEVEL_CRITICAL
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

void Trace::output(const char* file, const int line, const char* func, const Level level, const char* format, ...) {
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

void Trace::print(const char* file, const int line, const char* func, const Level level, const char* format, ...) {
	va_list	args;
	va_start(args, format);

	if (level < level_)
		return;

	AutoLock<> lock(guard_);
	
	::SetConsoleTextAttribute(handle_, COLORS[level]);
	
	fprintf(stderr, "<%10d> ", ::time(0) - zero_);

	if (file)
		fprintf(stderr, "[%20s:%3d] ", file, line);

	if (func)
		fprintf(stderr, "%40s() ", func);
		
	fprintf(stderr, format, args);
	fprintf(stderr, "\n");

	va_end(args);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

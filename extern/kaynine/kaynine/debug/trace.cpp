#include <kaynine/string_tools/tstring.h>
#include <kaynine/string_tools/string_conv.h>

#include <kaynine/debug/trace.h>


static TCHAR formatted[kaynine::MAX_TRACE_BUFFER];
static TCHAR full[kaynine::MAX_TRACE_BUFFER];

void kaynine::TraceF(const char* /*file*/, const int /*line*/, const char* func, const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	::_vstprintf(formatted, format, args);
	::_stprintf(full, _T(">%10d @ %s()$ %s"), ::time(NULL) - TRACE_ZERO_TIME, ANSItoTCHAR(func).c_str(), formatted);
	//_stprintf(full, _T(">%10d @ [%d] %s()$ %s"), ::time(NULL) - TRACE_ZERO_TIME, nLine, ANSItoTCHAR(func).c_str(), formatted);
	//_stprintf(full, _T(">%10d @ %s[%d] %s()$ %s"), ::time(NULL) - TRACE_ZERO_TIME, ANSItoTCHAR(file).c_str(), line, ANSItoTCHAR(func).c_str(), formatted);

	OutputDebugString(full);

	va_end(args);
}

void kaynine::TraceAF(const char* /*file*/, const int /*line*/, const char* func, const char* format, ...) {
	va_list	args;
	va_start(args, format);

	printf(reinterpret_cast<char*>(formatted), format, args);
	printf(reinterpret_cast<char*>(full), _T(">%10d @ %s()$ %s"), ::time(NULL) - TRACE_ZERO_TIME, func, formatted);
	//_stprintf(full, _T(">%10d @ [%d] %s()$ %s"), ::time(NULL) - TRACE_ZERO_TIME, nLine, ANSItoTCHAR(func).c_str(), formatted);
	//_stprintf(full, _T(">%10d @ %s[%d] %s()$ %s"), ::time(NULL) - TRACE_ZERO_TIME, ANSItoTCHAR(file).c_str(), line, ANSItoTCHAR(func).c_str(), formatted);

	::OutputDebugStringA(reinterpret_cast<char*>(full));

	va_end(args);
}

void kaynine::Trace(const TCHAR* format, ...) {
	va_list	args;
	va_start(args, format);

	_vstprintf(formatted, format, args);
	OutputDebugString(formatted);

	va_end(args);
}

void kaynine::TraceA(const char* format, ...) {
	va_list	args;
	va_start(args, format);

	printf(reinterpret_cast<char*>(formatted), format, args);
	::OutputDebugStringA(reinterpret_cast<char*>(formatted));

	va_end(args);
}

/*******************************************************//**
       
	@file

	@version	0.0.1

	@author Andrew 'nugb00t' Gresyk

	@date 18.08.2004

*//********************************************************/
#ifndef _KN_TRACE_INCLUDED_
#define _KN_TRACE_INCLUDED_


// std
#include <stdarg.h>	// vargs
#include <time.h>
// win
#include <windows.h>	// OutputDebugString()
#include <winbase.h>	// OutputDebugString()


namespace kaynine {


	// const
	static const time_t TRACE_ZERO_TIME		= ::time(NULL);
	static const int MAX_TRACE_BUFFER		= 1024;


	#define FLF	__FILE__, __LINE__, __FUNCTION__

	#ifdef KN_USE_TRACE
		#define KN_TRACEF	kaynine::TraceF
		#define KN_TRACEAF	kaynine::TraceAF
		#define KN_TRACE	kaynine::Trace
		#define KN_TRACEA	kaynine::TraceA
#else
		#define KN_TRACEF	__noop
		#define KN_TRACEAF	__noop
		#define KN_TRACE	__noop
		#define KN_TRACEA	__noop
#endif


	/**
		@brief		Trace the string 

		@param		format specificators
		@param		data

		@warning	MAX_TRACE_BUFFER is used for string output
	*/
	void TraceF(const char* file, const int line, const char* func, const TCHAR* format, ...);
	void TraceAF(const char* file, const int line, const char* func, const char* format, ...);


	/**
		@brief	Trace the string without FLF part

		@param	format specificators
		@param	data

		@warning	MAX_TRACE_BUFFER is used for string output
	*/
	void Trace(const TCHAR* format, ...);
	void TraceA(const char* format, ...);


} //namespace kaynine


#endif //_KN_TRACE_INCLUDED_
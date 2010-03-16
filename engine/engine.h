#pragma once

#include "engine_hub.h"

extern engine::Engine g_engine;

#ifdef KN_USE_TRACE
# ifndef TRACE_INFO
#  define TRACE_INFO(...)		g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_INFO,		__VA_ARGS__)
#  define TRACE_WARNING(...)	g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_WARNING,	__VA_ARGS__)
#  define TRACE_ERROR(...)		g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_ERROR,		__VA_ARGS__)
#  define TRACE_CRITICAL(...)	g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_CRITICAL,	__VA_ARGS__)
# endif
#else
# ifndef TRACE_INFO
#  define TRACE_INFO(x)		
#  define TRACE_WARNING(x)	
#  define TRACE_ERROR(x)	
#  define TRACE_CRITICAL(x)	
# endif
#endif

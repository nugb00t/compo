#pragma once

#include "engine_hub.h"

extern engine::Engine g_engine;

#ifdef KN_USE_TRACE
# ifndef TRACE_GOOD
#  define TRACE_GOOD(...)		g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_GOOD,		__VA_ARGS__)
#  define TRACE_NOTICE(...)		g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_NOTICE,		__VA_ARGS__)
#  define TRACE_WARNING(...)	g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_WARNING,	__VA_ARGS__)
#  define TRACE_ERROR(...)		g_engine.trace->print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_ERROR,		__VA_ARGS__)
# endif
#else
# ifndef TRACE_GOOD
#  define TRACE_GOOD(...)		
#  define TRACE_NOTICE(...)		
#  define TRACE_WARNING(...)	
#  define TRACE_ERROR(...)		
# endif
#endif

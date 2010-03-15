#pragma once

#include "engine_hub.h"

extern engine::Engine g_engine;

#ifdef KN_USE_TRACE
# ifndef TRACE_INFO
#  define TRACE_INFO(x)		g_engine.trace->print(__FILE__, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_INFO,		x)
#  define TRACE_WARNING(x)	g_engine.trace->print(__FILE__, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_WARNING,	x)
#  define TRACE_ERROR(x)	g_engine.trace->print(__FILE__, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_ERROR,		x)
#  define TRACE_CRITICAL(x)	g_engine.trace->print(__FILE__, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_CRITICAL,	x)
# endif
#else
# ifndef TRACE_INFO
#  define TRACE_INFO(x)		
#  define TRACE_WARNING(x)	
#  define TRACE_ERROR(x)	
#  define TRACE_CRITICAL(x)	
# endif
#endif

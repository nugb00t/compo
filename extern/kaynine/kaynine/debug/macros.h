#pragma once

#include "trace.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef RELEASE
#define RELEASE_ONLY(x)		x
#define UNLESS_RELEASE(x)
#else
#define RELEASE_ONLY(x)
#define UNLESS_RELEASE(x)	x
#endif

#ifdef _DEBUG
#define DEBUG_ONLY(x)		x
#define UNLESS_DEBUG(x)
#else
#define DEBUG_ONLY(x)
#define UNLESS_DEBUG(x)		x
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef KN_USE_TRACE
# define TRACE_NOTICE(...)			kaynine::Trace::inst().print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_NOTICE,	kaynine::Trace::SOURCE_NONE, 0,					__VA_ARGS__)
# define TRACE_GOOD(...)			kaynine::Trace::inst().print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_GOOD,	kaynine::Trace::SOURCE_NONE, 0, 				__VA_ARGS__)
# define TRACE_WARNING(...)			kaynine::Trace::inst().print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_WARNING,	kaynine::Trace::SOURCE_NONE, 0, 				__VA_ARGS__)
# define TRACE_ERROR(...)			kaynine::Trace::inst().print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_ERROR,	kaynine::Trace::SOURCE_NONE, 0, 				__VA_ARGS__)
# define TRACE_GENERIC_ERROR(...)	kaynine::Trace::inst().print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_ERROR,	kaynine::Trace::SOURCE_GEN, errno,				__VA_ARGS__)
# define TRACE_WINAPI_ERROR(...)	kaynine::Trace::inst().print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_ERROR,	kaynine::Trace::SOURCE_WIN, ::GetLastError(),	__VA_ARGS__)
# define TRACE_D3D_ERROR(hr, ...)	kaynine::Trace::inst().print(/*__FILE__*/ 0, __LINE__, __FUNCTION__, kaynine::Trace::LEVEL_ERROR,	kaynine::Trace::SOURCE_D3D, hr,					__VA_ARGS__)
#else
# define TRACE_NOTICE(...)		
# define TRACE_GOOD(...)		
# define TRACE_WARNING(...)	
# define TRACE_ERROR(...)
# define TRACE_GENERIC_ERROR(...)	
# define TRACE_WINAPI_ERROR(...)	
# define TRACE_D3D_ERROR(hr, ...)
#endif

#ifdef _DEBUG
# define CHECKED_CALL_F(x)				{ unsigned ReT = unsigned(x); if (!ReT)					{ TRACE_ERROR(			_T(#x) _T(" failed")); return false; } }
# define CHECKED_GENERIC_CALL_F(x, r)	{ unsigned ReT = unsigned(x); if (ReT != (r))			{ TRACE_GENERIC_ERROR(	_T(#x) _T(" failed")); return false; } }
# define CHECKED_WINAPI_CALL_F(x)		{ DWORD    ReT = DWORD   (x); if (ReT != ERROR_SUCCESS)	{ TRACE_WINAPI_ERROR(	_T(#x) _T(" failed")); return false; } }
# define CHECKED_D3D_CALL_F(x)			{ HRESULT  ReT = HRESULT (x); if (FAILED(ReT))			{ TRACE_D3D_ERROR(ReT,	_T(#x) _T(" failed")); return false; } }

# define CHECKED_CALL_A(x)				{ unsigned ReT = unsigned(x); if (!ReT)					{ TRACE_ERROR(			_T(#x) _T(" failed")); ::DebugBreak(); } }
# define CHECKED_GENERIC_CALL_A(x, r)	{ unsigned ReT = unsigned(x); if (ReT != (r))			{ TRACE_GENERIC_ERROR(	_T(#x) _T(" failed")); ::DebugBreak(); } }
# define CHECKED_WINAPI_CALL_A(x)		{ DWORD    ReT = DWORD   (x); if (ReT != ERROR_SUCCESS)	{ TRACE_WINAPI_ERROR(	_T(#x) _T(" failed")); ::DebugBreak(); } }
# define CHECKED_D3D_CALL_A(x)			{ HRESULT  ReT = HRESULT (x); if (FAILED(ReT))			{ TRACE_D3D_ERROR(ReT,	_T(#x) _T(" failed")); ::DebugBreak(); } }

# define CHECKED_CALL(x)				{ unsigned ReT = unsigned(x); if (!ReT)					{ TRACE_ERROR(			_T(#x) _T(" failed")); return false; } }
# define CHECKED_GENERIC_CALL(x, r)		{ unsigned ReT = unsigned(x); if (ReT != (r))			{ TRACE_GENERIC_ERROR(	_T(#x) _T(" failed")); return false; } }
# define CHECKED_WINAPI_CALL(x)			{ DWORD    ReT = DWORD   (x); if (ReT != ERROR_SUCCESS)	{ TRACE_WINAPI_ERROR(	_T(#x) _T(" failed")); return false; } }
# define CHECKED_D3D_CALL(x)			{ HRESULT  ReT = HRESULT (x); if (FAILED(ReT))			{ TRACE_D3D_ERROR(ReT,	_T(#x) _T(" failed")); return false; } }
#else
# define CHECKED_CALL_F(x)				(x)
# define CHECKED_GENERIC_CALL_F(x, r)	(x)
# define CHECKED_WINAPI_CALL_F(x)		(x)
# define CHECKED_D3D_CALL_F(x)			(x)

# define CHECKED_CALL_A(x)				(x)
# define CHECKED_GENERIC_CALL_A(x, r)	(x)
# define CHECKED_WINAPI_CALL_A(x)		(x)
# define CHECKED_D3D_CALL_A(x)			(x)

# define CHECKED_CALL(x)				(x)
# define CHECKED_GENERIC_CALL(x, r)		(x)
# define CHECKED_WINAPI_CALL(x)			(x)
# define CHECKED_D3D_CALL(x)			(x)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

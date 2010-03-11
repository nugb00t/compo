/*******************************************************//**
	@file

	@brief	Targe-dependent macros

    @author Andrew Gresyk

    @date	18.11.2009
*//********************************************************/
#ifndef _KN_MACROS_INCLUDED_
#define _KN_MACROS_INCLUDED_

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef RELEASE
#define RELEASE_ONLY(x) x
#else
#define RELEASE_ONLY(x)
#endif

#ifdef _DEBUG
#define DEBUG_ONLY(x) x
#else
#define DEBUG_ONLY(x)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define CHECKED_CALL(x)				assert((x))
#define CHECKED_GENERIC_CALL(x, r)	assert((x) == (r))
#define CHECKED_WINAPI_CALL(x)		assert((x))				// TEMP
#else
#define CHECKED_CALL(x)				(x)
#define CHECKED_GENERIC_CALL(x, r)	(x)
#define CHECKED_WINAPI_CALL(x)		(x)						// TEMP
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_KN_TCHAR_INCLUDED_

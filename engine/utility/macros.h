#ifndef MACROS_INCLUDED
#define MACROS_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UNUSED(x)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef RELEASE
#define RELEASE_ONLY(x) (x)
#else
#define RELEASE_ONLY(x)
#endif

#ifdef DEBUG
#define DEBUG_ONLY(x) (x)
#else
#define DEBUG_ONLY(x)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define CHECKED_CALL(x)				assert((x))
#define CHECKED_GENERIC_CALL(x, r)	assert((x) == (r))
#else
#define CHECKED_CALL(x)				(x)
#define CHECKED_GENERIC_CALL(x, r)	(x)
#endif

#ifdef _DEBUG
#define CHECKED_D3D_CALL(x)	{ HRESULT hr = x; if(FAILED(hr)) DXTrace(__FILE__, __LINE__, hr, _T(#x), TRUE); }
#define CHECKED_WIN_CALL(x)	assert((x))
#else
#define CHECKED_D3D_CALL(x)	(x)
#define CHECKED_WIN_CALL(x)	(x)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
#ifndef DEBUG_CHECKS_INCLUDED
#define DEBUG_CHECKS_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UNUSED(x)

#ifdef _DEBUG
#define DEBUG_ONLY(x)				(x)
#define CHECKED_CALL(x)				assert((x))
#define CHECKED_GENERIC_CALL(x, r)	assert((x) == (r))
#else
#define DEBUG_ONLY(x)
#define CHECKED_CALL(x)				(x)
#define CHECKED_GENERIC_CALL(x, r)	(x)
#endif

#define CHECKED_D3D_CALL(x)			CHECKED_GENERIC_CALL(x, D3D_OK)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

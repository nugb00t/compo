#ifndef ENGINE_PCH_INCLUDED
#define ENGINE_PCH_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <conio.h>		// _getch()
#include <stdio.h>
#include <tchar.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <map>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning (disable: 4244)		// conversion from 'int' to 'unsigned short', possible loss of data
#include <boost/intrusive_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/thread.hpp>
#pragma warning (default: 4244)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef PLATFORM_WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0510		// winxp
#endif

#define NOMINMAX	// disable min() and max() macros (for cml)

#include <Windows.h>

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef VIDEO_DIRECTX
	#include <d3d9.h>
	#include <d3dx9.h>
	#include <dxerr.h>
#endif

#ifdef VIDEO_OPENGL
	// glew - before opengl
	#define GLEW_STATIC
	#include <GL/glew.c>
	#include <GL/wglew.h>
	// opengl
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glaux.h>
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <kaynine/utility/singleton.h>
#include <kaynine/fs_tools/tools.h>
#include <kaynine/threading/frame_buffer.h>
#include <kaynine/threading/frame_buffer_access.h>
#include <kaynine/threading/sync_wrappers.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "engine_macros.h"
#include "engine_math.h"
#include "engine_types.h"
#include "utility/intrusive_ptr_base.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

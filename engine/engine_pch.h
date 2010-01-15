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
#include <boost/scoped_ptr.hpp>
#pragma warning (default: 4244)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef PLATFORM_WIN51
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0510		// winxp
	#endif

	#define NOMINMAX	// disable min() and max() macros (for cml)

	#include <Windows.h>
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef VIDEO_DIRECT3D9
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

#include <kaynine/debug/macros.h>
#include <kaynine/utility/holder.h>
#include <kaynine/utility/registry.h>
#include <kaynine/containers/cyclic_buffer.h>
#include <kaynine/filesystem/tools.h>
#include <kaynine/memory/intrusive_ptr_base.h>
#include <kaynine/threading/frame_buffer.h>
#include <kaynine/threading/thread.h>
#include <kaynine/threading/threaded.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "utility/macros.h"
#include "utility/math.h"

#include "utility/interfaces.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

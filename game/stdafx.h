#ifndef STDAFX_H
#define STDAFX_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning (disable: 4512)		// assignment operator could not be generated

#define VIDEO_DIRECT3D9
#ifdef VIDEO_DIRECT3D9
#define VIDEO_DIRECT3D9_ONLY(x) (x)
#else
#define VIDEO_DIRECT3D9_ONLY(x) (void)0
#endif

//#define VIDEO_OPENGL

#define PLATFORM_WIN51
#ifdef PLATFORM_WIN51
#define PLATFORM_WIN51_ONLY(x) (x)
#else
#define PLATFORM_WIN51_ONLY(x) (void)0
#endif

#include "engine_pch.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

/*******************************************************//**
       
	@file

	@version	0.0.1

	@author Andrew 'nugb00t' Gresyk

	@date 16.10.2004

*//********************************************************/
#ifndef KN_TOOLS_INCLUDED
#define KN_TOOLS_INCLUDED

#include <windows.h>

namespace kaynine
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool setRelativeDirectory(TCHAR* relativePath);
bool setCurrentDirectory();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace kaynine

#endif
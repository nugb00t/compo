/*******************************************************//**
       
	@file

	@version	0.0.1

	@author Andrew 'nugb00t' Gresyk

	@date 16.10.2004

*//********************************************************/
#ifndef _KN_TOOLS_INCLUDED_
#define _KN_TOOLS_INCLUDED_


// kaynine
#include "tchar.h"


namespace kaynine
{


	/**
		@brief	Set the directory of the exec file as current directory 

		@return	The directory set
	*/
	bool setRelativeDirectory(TCHAR* relativePath);

	bool setCurrentDirectory();


} //namespace kaynine


#endif //_KN_TOOLS_INCLUDED_
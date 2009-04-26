/*******************************************************//**
       
	@file

	@brief	Defines

	@date 26.02.2004

	@author Andrew S. Gresyk

*//********************************************************/
#ifndef _KN_TCHAR_INCLUDED_
#define _KN_TCHAR_INCLUDED_


// std
#include <iostream>
#include <sstream>
#include <string>
// win
#include <tchar.h>


// TCHAR macros
#ifndef _UNICODE
# define TCIN	cin
# define TCOUT	cout
# define TCERR	cerr
# define TCLOG	clog
#else
# define TCIN	wcin
# define TCOUT	wcout
# define TCERR	wcerr
# define TCLOG	wclog
#endif


typedef std::basic_streambuf<TCHAR>		tstreambuf;
typedef std::basic_fstream<TCHAR>		tfstream;
typedef std::basic_ifstream<TCHAR>		tifstream;
typedef std::basic_ofstream<TCHAR>		tofstream;
typedef std::basic_string<TCHAR>		tstring;


// DEBUG macros
#ifdef _DEBUG
# define DEBUG_ONLY(f)      (f)
#else
# define DEBUG_ONLY(f)		((void)0)
#endif


#endif //_KN_TCHAR_INCLUDED_



/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
	/*====================================================================================*/
	/*------------------------------------------------------------------------------------*/
/*............................................................................................*/

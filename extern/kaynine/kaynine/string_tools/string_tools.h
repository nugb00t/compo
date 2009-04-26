/*******************************************************//**
       
	@file

	@brief	String functions

	@date 26.02.2004

	@author Andrew S. Gresyk

*//********************************************************/
#ifndef _KN_STRING_TOOLS_INCLUDED_
#define _KN_STRING_TOOLS_INCLUDED_


// std
#include <vector>
// win
#include <windows.h>

// kaynine
#include "tchar.h"


namespace kaynine {


/**
	@brief	Formats error string
*/
tstring getErrDesc(DWORD dwError);


/**
	@brief	Generates random text string of given length

	@param	length of string to be generated
*/
tstring randomString(int nLength);


/**
	@brief	Splits chDel delimited string into string vector

	@param	string consisting of chDel delimited phrases
	@param	delimiter
*/
std::vector<tstring> split(const tstring& sLine, TCHAR chDel);


/**
	@brief	Tries to retrieve parenned substring

	@param	input string
	@param	left paren
	@param	right paren
*/
bool unParen(tstring& sLine, const TCHAR chParenL, const TCHAR chParenR);


} //namespace kaynine


#endif //_KN_STRING_TOOLS_INCLUDED_
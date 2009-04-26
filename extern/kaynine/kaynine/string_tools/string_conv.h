/*******************************************************//**
	@file

	@brief	String conversion functions (covered in test/StrConvTest.*)

	@date	30.01.2005

	@author Andrew S. Gresyk
*//********************************************************/
#ifndef _KN_STRING_CONV_INCLUDED_
#define _KN_STRING_CONV_INCLUDED_


namespace kaynine {


/**
	@brief	Create ANSI-string from T-string

	@param	string
*/
std::wstring ANSItoUTF16(const char* lpszLine);
std::wstring ANSItoUTF16(const std::string& sLine);


/**
	@brief	Create ANSI-string from T-string

	@param	string
*/
std::string UTF16toANSI(const wchar_t* lpszLine);
std::string UTF16toANSI(const std::wstring& sLine);


// TCHAR synonyms
tstring ANSItoTCHAR(const char* lpszLine);
tstring ANSItoTCHAR(const std::string& sLine);

std::string TCHARtoANSI(const TCHAR* lpszLine);
std::string TCHARtoANSI(const tstring& sLine);

tstring UTF16toTCHAR(const wchar_t* lpszLine);
tstring UTF16toTCHAR(const std::wstring& sLine);

std::wstring TCHARtoUTF16(const TCHAR* lpszLine);
std::wstring TCHARtoUTF16(const tstring& sLine);


} //namespace kaynine



#endif //_KN_STRING_CONV_INCLUDED_
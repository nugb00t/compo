// win
#include <windows.h>

#include "string_conv.h"


std::wstring kaynine::ANSItoUTF16(const char* lpszLine) {
	if (!lpszLine)
		return NULL;

	int nLen	= (int)strlen(lpszLine);

	// prepare output string
	wchar_t* lpszConv = new wchar_t[nLen + 1];

	int nConv = MultiByteToWideChar(CP_ACP, 0, lpszLine, nLen, lpszConv, nLen);	// ASCII cp

	// pass the result as std::string
	std::wstring sConv(lpszConv, nConv);
	delete[] lpszConv;

	// TODO: use nConv for erroe control

	return sConv;
}

std::wstring kaynine::ANSItoUTF16(const std::string& sLine) {
	if (sLine.empty())
		return NULL;

	int nLen	= (int)sLine.length();

	// prepare output string
	wchar_t* lpszConv = new wchar_t[nLen + 1];

	int nConv = MultiByteToWideChar(CP_ACP, 0, sLine.c_str(), nLen, lpszConv, nLen);	// ASCII cp

	// pass the result as std::string
	std::wstring sConv(lpszConv, nConv);
	delete[] lpszConv;

	// TODO: use nConv for erroe control

	return sConv;
}


std::string kaynine::UTF16toANSI(const wchar_t* lpszLine) {
	if (!lpszLine)
		return NULL;

	int nLen	= (int)wcslen(lpszLine);

	// prepare output string
	char* lpszConv = new char[nLen + 1];

	int nConv = WideCharToMultiByte(CP_ACP, 0, lpszLine, nLen, lpszConv, nLen, NULL, NULL);	// ASCII cp

	// pass the result as std::string
	std::string sConv(lpszConv, nConv);
	delete[] lpszConv;

	// TODO: use nConv for erroe control

	return sConv;
}

std::string kaynine::UTF16toANSI(const std::wstring& sLine) {
	if (sLine.empty())
		return NULL;

	int nLen	= (int)sLine.length();

	// prepare output string
	char* lpszConv = new char[nLen + 1];

	int nConv = WideCharToMultiByte(CP_ACP, 0, sLine.c_str(), nLen, lpszConv, nLen, NULL, NULL);	// ASCII cp

	// pass the result as std::string
	std::string sConv(lpszConv, nConv);
	delete[] lpszConv;

	// TODO: use nConv for erroe control

	return sConv;
}


#ifndef UNICODE

	tstring kaynine::ANSItoTCHAR(const char* lpszLine)		 {	return lpszLine;				}
	tstring kaynine::ANSItoTCHAR(const std::string& sLine)		 {	return sLine;					}

	std::string kaynine::TCHARtoANSI(const TCHAR* lpszLine)			 {	return lpszLine;				}
	std::string kaynine::TCHARtoANSI(const tstring& sLine)			 {	return sLine;					}

	tstring kaynine::UTF16toTCHAR(const wchar_t* lpszLine)	 {	return UTF16toANSI(lpszLine);	}
	tstring kaynine::UTF16toTCHAR(const std::wstring& sLine)	 {	return UTF16toANSI(sLine);	}

	std::wstring kaynine::TCHARtoUTF16(const TCHAR* lpszLine)		 {	return ANSItoUTF16(lpszLine);	}
	std::wstring kaynine::TCHARtoUTF16(const tstring& sLine)			 {	return ANSItoUTF16(sLine);	}

#else

	tstring kaynine::ANSItoTCHAR(const char* lpszLine)		 {	return ANSItoUTF16(lpszLine);	}
	tstring kaynine::ANSItoTCHAR(const std::string& sLine)		 {	return ANSItoUTF16(sLine);	}

	std::string kaynine::TCHARtoANSI(const TCHAR* lpszLine)			 {	return UTF16toANSI(lpszLine);	}
	std::string kaynine::TCHARtoANSI(const tstring& sLine)			 {	return UTF16toANSI(sLine);	}

	tstring kaynine::UTF16toTCHAR(const wchar_t* lpszLine)	 {	return lpszLine;				}
	tstring kaynine::UTF16toTCHAR(const std::wstring& sLine)	 {	return sLine;					}

	std::wstring kaynine::TCHARtoUTF16(const TCHAR* lpszLine)		 {	return lpszLine;				}
	std::wstring kaynine::TCHARtoUTF16(const tstring& sLine)			 {	return sLine;					}

#endif

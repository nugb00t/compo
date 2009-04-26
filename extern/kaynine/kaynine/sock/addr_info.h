/*******************************************************//**
       
	@file

	@version		BETA

	@author		Andrew 'nugb00t' Gresyk

	@date		16.10.2004

*//********************************************************/
#ifndef _KN_ADDR_INFO_INCLUDED_
#define _KN_ADDR_INFO_INCLUDED_


// kaynine
#include "exception.h"


#define KN_WSA_EXCEPTION(reason)		Exception(FLF, reason, WSAGetLastError())


namespace kaynine {


/***********************************************************************************//**
	
	@brief		A thin @c getaddrinfo() wrapper class.

				A small concrete class that incapsulates @c getaddrinfo() functionality and resulting linked list navigation.

	@remarks	It is recommended to resolve addresses using more common @c getaddinfo() instead of @c gethostbyname() or others.

*//************************************************************************************/
class CAddrInfo: public ThrowerBase {
protected:
	addrinfo*		_aAddrInfos;
	addrinfo*		_pAddrInfoCurr;


public:
	CAddrInfo(const char* lpszAddress, const char* lpszServ) {
		struct addrinfo	hints;

		// setup the hints address info structure
		memset(&hints, 0, sizeof(hints));
		hints.ai_family	= AF_INET;
		hints.ai_socktype	= SOCK_STREAM;
		hints.ai_protocol	= IPPROTO_TCP;

		// retrieve address info
		if (getaddrinfo(lpszAddress, lpszServ, &hints, &_aAddrInfos) != 0 || !_aAddrInfos)
			throw KN_WSA_EXCEPTION(_T(""));

		_pAddrInfoCurr = _aAddrInfos;
	}

	~CAddrInfo() {
		freeaddrinfo(_aAddrInfos);
	}

	inline SOCKADDR* Addr() {
		return _pAddrInfoCurr->ai_addr;
	}

	inline bool AtEnd() {
		return _pAddrInfoCurr->ai_addr != NULL;
	}

	inline void Next() {
		_pAddrInfoCurr = _pAddrInfoCurr->ai_next;
	}

	inline void Reset() {
		_pAddrInfoCurr = _aAddrInfos;
	}
};


} // namespace kaynine


#endif //_KN_ADDR_INFO_INCLUDED_

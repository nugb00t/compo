/*******************************************************//**
       
	@file

	@version		BETA

	@author		Andrew 'nugb00t' Gresyk

	@date		16.10.2004

*//********************************************************/
#ifndef _KN_SOCKETWSA_INCLUDED_
#define _KN_SOCKETWSA_INCLUDED_


// kaynine
#include "socket.h"


namespace kaynine {


/*******************************************************************************************//**
       
	@brief		Socket class with WSA initialization.

				Inherits @c kaynine::CSocket behavior and adds @c WSAStartup() and @c WSACleanup().

	@remarks	Intended to be used when you are responsible for WinSock subsystem initialization and teardown. 

*//*******************************************************************************************/
class CWinClientSocket : public CClientSocket {
protected:
	class CWSA {
		WSADATA		m_wsaData;


	public:
		struct Error {
			static const TCHAR*	WSASTARTUP_FAILED;
		};


	public:
		CWSA();
		~CWSA();
	};


protected:
	static CWSA			m_wsa;


public:
	CWinClientSocket();
	CWinClientSocket(SOCKET sock);
};


class CWinClientSocket : public CClientSocket {
protected:
	class CWSA {
		WSADATA		m_wsaData;


	public:
		struct Error {
			static const TCHAR*	WSASTARTUP_FAILED;
		};


	public:
		CWSA();
		~CWSA();
	};


protected:
	static CWSA			m_wsa;


public:
	CWinSocket();
	CWinSocket(SOCKET sock);
};


} // namespace kaynine


#endif //_KN_SOCKETWSA_INCLUDED_

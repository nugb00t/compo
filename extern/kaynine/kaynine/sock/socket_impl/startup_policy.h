/*******************************************************//**
       
	@file

	@version		BETA

	@author		Andrew 'nugb00t' Gresyk

	@date		16.10.2004

*//********************************************************/
#ifndef _KN_SOCKET_STARTUP_POLICY_INCLUDED_
#define _KN_SOCKET_STARTUP_POLICY_INCLUDED_


// kaynine
#include "../exception.h"


#define KN_WSA_EXCEPTION(reason)		Exception(FLF, reason, WSAGetLastError())


namespace kaynine {


/*******************************************************************************************//**
       
	@brief		Socket class with WSA initialization.

				Inherits @c kaynine::CSocket behavior and adds @c WSAStartup() and @c WSACleanup().

	@remarks	Intended to be used when you are responsible for WinSock subsystem initialization and teardown. 

*//*******************************************************************************************/
class CDoWSAStartup {
protected:
	class CWSA : public ThrowerBase {
		WSADATA		m_wsaData;


	public:
		// construction / destruction
		CWSA();
		~CWSA();
	};


protected:
	static CWSA			m_wsa;
};


class CNoWSAStartup {
};


} // namespace kaynine


#endif //_KN_SOCKET_STARTUP_POLICY_INCLUDED_

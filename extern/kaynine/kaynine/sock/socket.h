/*******************************************************//**
       
	@file

	@version		ALPHA

	@author		Andrew 'nugb00t' Gresyk

	@date		16.10.2004

*//********************************************************/
#ifndef _KN_SOCKET_INCLUDED_
#define _KN_SOCKET_INCLUDED_


// winsock
#include <winsock2.h>
#include <ws2tcpip.h>					// addrinfo
// kaynine
#include "addr_info.h"
#include "exception.h"
#include "string_tools.h"
// strategies
//#include "socket_impl/address_policy.h"
//#include "socket_impl/block_policy.h"
#include "socket_impl/startup_policy.h"


#define KN_WSA_EXCEPTION(reason)		Exception(FLF, reason, WSAGetLastError())


namespace kaynine {


/*******************************************************************************************//**
       
	@brief		A thin @c SOCKET wrapper class.

				Inherits @c kaynine::CSocket behavior and adds @c WSAStartup() and @c WSACleanup().

	@remarks	Intended to be used when you are responsible for WinSock subsystem initialization and teardown. 

*//*******************************************************************************************/
template </*typename TBlockPolicy,*/ typename TStartupPolicy/*, typename TAddressPolicy*/>
class CSocket: 
	//public TBlockPolicy,
	public TStartupPolicy,
	//public TAddressPolicy,
	public ThrowerBase {


protected:
	// consts
	static const int CLEARBUFFER_SIZE	= 256;
	static const int SOCKS4BUFFER_SIZE	= 16;

	//enum STATE
	//{
	//	DISCONNECTED,
	//};


protected:
	SOCKET		_socket;


public:
	CSocket() {
		if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
			throw KN_WSA_EXCEPTION(_T(""));
	}

	CSocket(SOCKET sock)
		: _socket(sock) {
	}

	~CSocket() {
		Close();
	}


	// conversation
	inline int Receive(char* pBuffer, int nLength) {
		int nReceived;
		//char tmpBuffer[1024];
		//tmpBuffer[0] = 0;

		if ((nReceived = recv(_socket, pBuffer, nLength, 0)) == SOCKET_ERROR ) 
			throw KN_WSA_EXCEPTION(_T(""));

		return nReceived;
	}

	inline int Send(const char* pBuffer, int nLength) {
		int nSent;

		if ((nSent = send(_socket, pBuffer, nLength, 0)) == SOCKET_ERROR)
			throw KN_WSA_EXCEPTION(_T(""));

		return nSent;
	}

	inline void Clear() {
		char pBuffer[CLEARBUFFER_SIZE];
		int nReceived;

		do {
			if ((nReceived = recv(_socket, pBuffer, CLEARBUFFER_SIZE, 0)) == SOCKET_ERROR ) 
				throw KN_WSA_EXCEPTION(_T(""));
		} while (nReceived);
	}

	// options
	inline bool SetIOMode(bool bNonblocking) {
		int nMode = bNonblocking;
		ioctlsocket(_socket, FIONBIO, (u_long FAR*) &nMode);
		return nMode != 0;
	}

	inline int SetTimeout(int nMilliseconds) {
		int nOldTimeout;
		int nOldTimeoutSize = sizeof(nOldTimeout);

		if (	getsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&nOldTimeout, &nOldTimeoutSize) == SOCKET_ERROR)
			throw KN_WSA_EXCEPTION(_T(""));

		if (	setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&nMilliseconds, sizeof(nOldTimeout)) == SOCKET_ERROR ||
			setsockopt(_socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&nMilliseconds, sizeof(nOldTimeout)) == SOCKET_ERROR)
			throw KN_WSA_EXCEPTION(_T(""));

		return nOldTimeout;
	}

	// closure
	inline void Close() {
		shutdown(_socket, SD_BOTH);
		//Clear();
		closesocket(_socket);
	}


	// tools
	inline operator SOCKET () {
		return _socket;
	}
};


template </*typename TBlockPolicy = CBlocking,*/ typename TStartupPolicy = CDoWSAStartup/*, typename TAddressPolicy = CSingleAddress*/>
class CClientSocket: public CSocket</*BlockPolicy,*/ TStartupPolicy/*, AddressPolicy*/> {
public:
	CClientSocket()
		: CSocket<TStartupPolicy>() {
	}

	CClientSocket(SOCKET sock)
		: CSocket<TStartupPolicy>(sock) {
	}

	/**	@brief	Connects to specified address

		@remarks	Uses CAddrInfo class to resolve address 
	
		@param	IP address / hostname
		@param	service / port
	*/
	void Connect(const char* lpszAddress, const char* lpszServ) {
		// use AddrInfo() to retrieve IP address
		CAddrInfo addInfo(lpszAddress, lpszServ);
	        
		// connect using sockaddr from getaddrinfo()
		if (connect(_socket, (SOCKADDR*)addInfo.Addr(), sizeof(sockaddr_in)) == SOCKET_ERROR) 
			throw KN_WSA_EXCEPTION(_T(""));
	}


	/**	@brief	Connects to specified address

		@remarks	Uses CAddrInfo class to resolve address 
	
		@param	IP address / hostname
		@param	service / port
	*/
	void ConnectMulti(const char* lpszAddress, const char* lpszServ) {
		int	nRes;
		int	nErr;
		// use AddrInfo() to retrieve IP address
		for (CAddrInfo addInfo(lpszAddress, lpszServ); !addInfo.AtEnd(); addInfo.Next()) {
			// try connecting using one of AddrInfo IPs. break if successful
			if ((nRes = connect(_socket, (SOCKADDR*)addInfo.Addr(), sizeof(sockaddr_in))) != SOCKET_ERROR)
				break;

			// retry only on address fault. otherwise - break to exception
			nErr = WSAGetLastError();
			if (	nRes != WSAEADDRNOTAVAIL && 
				nRes != WSAECONNREFUSED && 
				nRes != WSAEFAULT && 
				nRes != WSAENETUNREACH && 
				nRes != WSAETIMEDOUT)
				break;
		}

		// connect using sockaddr from getaddrinfo()
		if (nRes == SOCKET_ERROR) 
			throw KN_WSA_EXCEPTION(_T(""));
	}
};


template </*typename TBlockPolicy = CBlocking,*/ typename TStartupPolicy = CDoWSAStartup/*, typename TAddressPolicy = CSingleAddress*/>
class CServerSocket: public CSocket</*BlockPolicy,*/ TStartupPolicy/*, AddressPolicy*/> {
public:
	CServerSocket()
		: CSocket<TStartupPolicy>() {
	}

	CServerSocket(SOCKET sock)
		: CSocket<TStartupPolicy>(sock) {
	}

	/**	@brief	Log the string 

		@param	format specificators
		@param	data
	*/
	SOCKET Accept(sockaddr* pAddress, int* nAddrLength) {
		SOCKET	sock;
		if ((sock = accept(_socket, pAddress, nAddrLength)) == INVALID_SOCKET)
			throw KN_WSA_EXCEPTION(_T(""));

		return sock;
	}

	SOCKET Accept() {
		return Accept(NULL, NULL);
	}

	void BindAndListen(const char* lpszAddress, const char* lpszServ, int nConnections) {
		// use AddrInfo() to retrieve IP address
		CAddrInfo addInfo(lpszAddress, lpszServ);

		// try binding using one of AddrInfo IPs
		if (bind(_socket, (SOCKADDR*)addInfo.Addr(), sizeof(sockaddr_in)) == SOCKET_ERROR)
			throw KN_WSA_EXCEPTION(_T(""));

		if (listen(_socket, nConnections) == SOCKET_ERROR) 
			throw KN_WSA_EXCEPTION(_T(""));
	}

	void BindAndListenMulti(const char* lpszAddress, const char* lpszServ, int nConnections) {
		int	nRes;
		int	nErr;
		// use AddrInfo() to retrieve IP address
		for (CAddrInfo addInfo(lpszAddress, lpszServ); !addInfo.AtEnd(); addInfo.Next()) {
			// try binding using one of AddrInfo IPs. break if successful
			if ((nRes = bind(_socket, (SOCKADDR*)addInfo.Addr(), sizeof(sockaddr_in))) != SOCKET_ERROR)
				break;

			// retry only on address fault. otherwise - break to exception
			nErr = WSAGetLastError();
			if (	nRes != WSAEADDRNOTAVAIL && 
				nRes != WSAEFAULT)
				break;
		}

		// track all bind() faults
		if (nRes == SOCKET_ERROR)
			throw KN_WSA_EXCEPTION(_T(""));

		if (listen(_socket, nConnections) == SOCKET_ERROR) 
			throw KN_WSA_EXCEPTION(_T(""));
	}
};


} // namespace kaynine



#endif //_KN_SOCKET_INCLUDED_

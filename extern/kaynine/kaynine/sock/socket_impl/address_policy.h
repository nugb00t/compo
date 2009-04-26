/*******************************************************//**
       
	@file

	@version		BETA

	@author		Andrew 'nugb00t' Gresyk

	@date		16.10.2004

*//********************************************************/
#ifndef _KN_SOCKET_ADDRESS_POLICY_INCLUDED_
#define _KN_SOCKET_ADDRESS_POLICY_INCLUDED_


namespace kaynine {
/*******************************************************************************************//**
       
	@brief		Socket class with WSA initialization.

				Inherits @c kaynine::CSocket behavior and adds @c WSAStartup() and @c WSACleanup().

	@remarks	Intended to be used when you are responsible for WinSock subsystem initialization and teardown. 

*//*******************************************************************************************/
class CSingleAddress {
};


} // namespace kaynine


#endif //_KN_SOCKET_ADDRESS_POLICY_INCLUDED_

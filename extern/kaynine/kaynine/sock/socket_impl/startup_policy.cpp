#include "../include/kaynine/socket_impl/startup_policy.h"


// static member init
kaynine::CDoWSAStartup::CWSA kaynine::CDoWSAStartup::m_wsa;


kaynine::CDoWSAStartup::CWSA::CWSA() {
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != NO_ERROR)
		throw KN_WSA_EXCEPTION(_T(""));
}

kaynine::CDoWSAStartup::CWSA::~CWSA() {
	WSACleanup();
}

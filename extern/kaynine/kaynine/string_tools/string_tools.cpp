#include <kaynine/string_tools.h>


tstring kaynine::getErrDesc(DWORD dwError) {
	TCHAR szMsg[4096];
	
	FormatMessage(/*FORMAT_MESSAGE_ALLOCATE_BUFFER |*/ FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				  NULL,
				  dwError,
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				  szMsg,
				  4096,
				  NULL);
    
	return szMsg;
}

tstring kaynine::randomString(int nLength) {
	tstring	sResult;
	tstring	sCurrent;

	for (int i = 0; i < nLength; i++)
		sResult.append(1, _T('a' + rand() % 26));

	return sResult;
}

std::vector<tstring> kaynine::split(const tstring& sLine, TCHAR chDel) {
	tstring::size_type		nStartPos = 0;
	tstring::size_type		nStopPos;

	std::vector<tstring>	vecLineParts;
	tstring				sCurrent;


	for (nStartPos = 0; nStartPos < sLine.length() + 1; nStartPos = nStopPos + 1) {
		nStopPos = min(sLine.length(), sLine.find(chDel, nStartPos));

		sCurrent.clear();
		sCurrent.insert(0, sLine, nStartPos, nStopPos - nStartPos);

		if (sCurrent.size())
			vecLineParts.push_back(sCurrent);
	}

	return vecLineParts;
}

bool kaynine::unParen(tstring& sLine, const TCHAR chParenL, const TCHAR chParenR) {
	tstring::size_type		nPosL = sLine.find(chParenL);
	tstring::size_type		nPosR = sLine.find(chParenR);


	if (nPosL != sLine.npos && nPosR != sLine.npos) {
		sLine = sLine.substr(nPosL + 1, nPosR - nPosL - 1);
		return true;
	}
	else
		return false;
}

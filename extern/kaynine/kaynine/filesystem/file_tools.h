#ifndef _KN_FILE_TOOLS_INCLUDED_
#define _KN_FILE_TOOLS_INCLUDED_


// kaynine
#include "tchar.h"


namespace kaynine {


template <class TContainer>
void scan(TContainer& files, const tstring& path, const unsigned still) {
	tstring searchPath = path + tstring(_T("\\*.*"));

	WIN32_FIND_DATA findData;
	HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE)
		return;

	while (::FindNextFile(hFind, &findData)) {
		if (findData.cFileName[0] == _T('.'))
			continue;

		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			scan(files, path + tstring(_T("\\")) + tstring(findData.cFileName), still);
		else
			files.insert(((path.length() == still) ? tstring() : tstring(path, still + 1) + tstring(_T("\\"))) + tstring(findData.cFileName));
	}

	::FindClose(hFind);
}


} // namespace kaynine


#endif //_KN_FILE_TOOLS_INCLUDED_
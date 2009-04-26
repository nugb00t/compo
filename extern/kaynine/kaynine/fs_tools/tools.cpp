#include "../string_tools/tstring.h"
#include "tools.h"

// win
#include <windows.h>					// SetCurrentDirectory()
#include <psapi.h>						// GetModuleFileName()
#pragma comment(lib, "psapi.lib")
#include <shlwapi.h>					// PathRemoveFileSpec()
#pragma comment(lib, "shlwapi.lib")


bool kaynine::setRelativeDirectory(TCHAR* relativePath)
{
	TCHAR		exePath[MAX_PATH + 1];

	::GetModuleFileName(NULL, exePath, MAX_PATH);
	::PathRemoveFileSpec(exePath);

	tstring newPath(exePath);

	if (relativePath)
		newPath += tstring(_T("\\")) + relativePath;

	return ::SetCurrentDirectory(newPath.c_str()) != 0;
}

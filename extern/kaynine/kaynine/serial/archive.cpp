#include "archive.h"


using namespace kaynine;


//==============================================================================================================================================
// Ctor 
//==============================================================================================================================================
Archive::Archive(const TCHAR* path, Mode mode, unsigned version)
: mode_(mode), version_(version) {
	assert(mode == READ || mode == WRITE);

	file_ = ::_tfopen(path, mode_ == READ ? _T("rb") : _T("wb"));
	assert(file_);

#ifdef _DEBUG
	bool ok =
#endif // _DEBUG
		serializePOD(version_);
	assert(ok);

#ifdef _DEBUG
	ok =
#endif // _DEBUG
		serializeHeadDelim();
	assert(ok);

	assert(!::ferror(file_));
}


//==============================================================================================================================================
// Dtor 
//==============================================================================================================================================
Archive::~Archive() {
#ifdef _DEBUG
	int nullRet =
#endif // _DEBUG
		::fflush(file_);
	assert(!nullRet);

#ifdef _DEBUG
	nullRet =
#endif // _DEBUG
		::fclose(file_);
	assert(!nullRet);
}


//----------------------------------------------------------------------------------------------------------------------------------------------
// Raw data serialization
//----------------------------------------------------------------------------------------------------------------------------------------------
bool Archive::serializeRaw(void* buffer, unsigned length) {
	assert(file_ && !::ferror(file_));

	size_t count;
	if (mode_ == READ)
		count = ::fread(buffer, 1, length, file_);
	else
		count = ::fwrite(buffer, 1, length, file_);

	return count == length;
}

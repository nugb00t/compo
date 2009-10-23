/*******************************************************//**

	 @file

	 @version	0.0.1

	 @author Andrew 'nugb00t' Gresyk

	 @date 18.08.2004

*//********************************************************/
#ifndef _KN_SCOPED_FILE_INCLUDED_
#define _KN_SCOPED_FILE_INCLUDED_


// kaynine
#include "tchar.h"


namespace kaynine {


class ScopedFile {
public:
	inline ScopedFile();
	inline ScopedFile(const TCHAR* path, const int oflag);
	inline ~ScopedFile();

	inline bool open(const TCHAR* path, const int oflag);
	inline bool close();

	inline bool isOpen() const;
	inline long length() const;

	inline int read(void* buffer, const unsigned count) const;


private:
	int file_;
};


ScopedFile::ScopedFile()
: file_(0) {
}


ScopedFile::ScopedFile(const TCHAR* path, const int oflag)
: file_(0) {
	open(path, oflag);
}


ScopedFile::~ScopedFile() {
	close();
}


bool ScopedFile::close() {
	if (!file_)
		return false;

	return ::_close(file_) == 0;
}


bool ScopedFile::isOpen() const {
	return file_ != 0;
}


long ScopedFile::length() const {
	return ::_filelength(file_);
}


bool ScopedFile::open(const TCHAR* path, const int oflag) {
	file_ = ::_topen(path, oflag);
	return file_ != -1;
}


int ScopedFile::read(void* buffer, const unsigned count) const {
	return ::_read(file_, buffer, count);
}


} // namespace kaynine


#endif //_KN_SCOPED_FILE_INCLUDED_
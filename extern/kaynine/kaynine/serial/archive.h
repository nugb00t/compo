/*******************************************************//**
       
	@file

	@brief	Archive, basic serializer

	@date	2007.08.27

	@author Andrew S. Gresyk

*//********************************************************/
#ifndef _KN_ARCHIVE_INCLUDED_
#define _KN_ARCHIVE_INCLUDED_


// C
#include <assert.h>

// std
#include <vector>

// kaynine
#include "../string_tools/tstring.h"
#include "../string_tools/string_conv.h"


namespace kaynine {


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface for serializable containers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Serializable {
public:
	virtual bool serializeWith(class Archive& archive) = 0;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Archive class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Archive {
public:
	enum Mode {
		READ,
		WRITE
	};

	static const char Delim = ' ';
	static const char HeadDelim = ':';


	Archive(const TCHAR* path, Mode mode, unsigned version = 0);
	~Archive();


private:
	// no copy semantics
	Archive(const Archive&);
	Archive& operator=(const Archive&);


public:
	// inlines
	inline Mode getMode() { return mode_; }
	inline unsigned getVersion() { return version_; }
	inline bool isGood() { return file_ != NULL && !::ferror(file_); }

	// Serializable support
	inline bool serialize(Serializable& serializable) { return serializable.serializeWith(*this); }

	// helpers
	bool serializeDelim() { char delim = Delim; return serializePOD(delim) && delim == Delim;; }
	bool serializeHeadDelim() { char delim = HeadDelim; return serializePOD(delim) && delim == HeadDelim; }

	template <class T>
	bool serializeAsInt(T& t);

	template <class T>
	bool serializePOD(T& t) { return serializeRaw((void*)&t, sizeof(t)); }

	template <>
	bool serializePOD<bool>(bool& t);

	template <class T>
	bool serializePODSequence(T& sequence);


protected:
	bool serializeRaw(void* buffer, unsigned lengthInBytes);


private:
	const Mode mode_;
	unsigned version_;
	FILE* file_;
};


//==============================================================================================================================================
// Serialize data as 4 byte number 
//==============================================================================================================================================
template <class T>
bool Archive::serializeAsInt(T& t) {
	int temp = static_cast<int>(t);

	bool ok = serializePOD(temp);

	t = static_cast<T>(temp);
	return ok;
}


//==============================================================================================================================================
// POD specialization for bool
//==============================================================================================================================================
template <>
bool Archive::serializePOD<bool>(bool& t) {
	char temp = static_cast<char>(t);

	bool ok = serializePOD(temp);

	t = temp != 0;
	return ok;
}


//==============================================================================================================================================
// POD sequence 
//==============================================================================================================================================
template <class T>
bool Archive::serializePODSequence(T& sequence) {
	size_t size = sequence.size();
	if (!serializeDelim() ||
		!serializePOD(size) ||
		!serializeHeadDelim())
		return false;

	if (mode_ == READ) {
		for (size_t i = 0; i < size; ++i) {
			T::value_type elem;
			if (serializePOD(elem))
				sequence.push_back(elem);
			else
				return false;
		}
	} else {
		for (T::const_iterator it = sequence.begin(); it != sequence.end(); ++it)
			if (!serializePOD(*it))
				return false;
	}

	return true;
}


} //namespace kaynine


#endif //_KN_ARCHIVE_INCLUDED_
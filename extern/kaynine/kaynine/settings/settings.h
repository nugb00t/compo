/*******************************************************//**
	@file

	@brief	Shared memry area template

	@author Andrew 'nugb00t' Gresyk

	@date 26.02.2004
*//********************************************************/
#ifndef _KN_SETTINGS_INCLUDED_
#define _KN_SETTINGS_INCLUDED_

#include "tchar.h"
#include <fstream>


namespace kaynine {


namespace {

// this func should be specialized for every type of values_ for Settings class
template <class T>
bool toValue(T& value, const TCHAR* valueChars, const unsigned numChars);

template <>
bool toValue<int>(int& value, const TCHAR* valueChars, const unsigned /*numChars*/) {
	value = ::_tstoi(valueChars);
	return value != 0;
}

template <>
bool toValue<float>(float& value, const TCHAR* valueChars, const unsigned /*numChars*/) {
	value = static_cast<float>(::_tstof(valueChars));
	return value != 0.f;
}

template <>
bool toValue<TCHAR*>(TCHAR*& value, const TCHAR* valueChars, const unsigned numChars) {
	return !::_tcsncpy_s(value, numChars, valueChars, numChars);
}

}


/******************************************************************************************//**
	@brief		Settings class.

	TContainee mockup:

	struct Items {
		typedef float ValueType;

		enum ItemEnum {
			ITEM_NUM
		};
	};

	const TCHAR* Config::Names[Config::Size] = { _T("Uno"), _T("Dos"), _T("Tres") };

	const Config::ValueType Config::Defaults[Config::Size] = { 1.f, 2.f, 3.f };

*//*******************************************************************************************/
template <class TItemSet, int TMaxNameLength = 256, int TMaxValueLength = 16>
class Settings {
	static const unsigned MaxNameLength = TMaxNameLength;
	static const unsigned MaxValueLength = TMaxValueLength;
	static const TCHAR NameValueDelim = _T('=');

public:
	typedef typename TItemSet::ValueType ValueType;
	typedef typename TItemSet::ItemEnum ItemEnum;

	// TContainee parameters
	static const unsigned Size = TItemSet::ITEM_NUM;

	static const TCHAR* Names[Size];
	static const ValueType Defaults[Size];


public:
	Settings();
	Settings(const tstring& path, bool saveOnExit = true);
	~Settings();

	// ?
	Settings operator =(const Settings& settings);

	bool load(const tstring& path);
	bool save(const tstring& path);
	void reset();

	ValueType& operator [](const ItemEnum item);
	const ValueType& operator [](const ItemEnum item) const;

private:
	ValueType values_[Size];
	tstring filePath_;
	const bool saveOnExit_;
};


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
Settings<TItemSet, TMaxNameLength, TMaxValueLength>::Settings()
: saveOnExit_(false) {
	reset();
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
Settings<TItemSet, TMaxNameLength, TMaxValueLength>::Settings(const tstring& path, bool saveOnExit)
: filePath_(path), saveOnExit_(saveOnExit) {
	load(filePath_);
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
Settings<TItemSet, TMaxNameLength, TMaxValueLength>::~Settings() {
	if (saveOnExit_ && !filePath_.empty())
		save(filePath_);
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
Settings<TItemSet, TMaxNameLength, TMaxValueLength> Settings<TItemSet, TMaxNameLength, TMaxValueLength>::operator =(const Settings<TItemSet, TMaxNameLength, TMaxValueLength>& settings) {
	return Settings<TItemSet, TMaxNameLength, TMaxValueLength>(*this);
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
bool Settings<TItemSet, TMaxNameLength, TMaxValueLength>::load(const tstring& path) {
	reset();

	tifstream ifs(path.c_str());
	if (ifs.is_open() && !ifs.bad()) {
		TCHAR name[MaxNameLength];
		TCHAR value[MaxValueLength];

		while (!ifs.eof()) {
			// read value name
			ifs.get(name, MaxNameLength, NameValueDelim);
			ifs.ignore();		// NAME_VALUE_DELIM

			// look it up in Names array
			unsigned i;
			for (i = 0; i < Size; ++i)
				if (!_tcscmp(Names[i], name))
					break;

			ifs.get(value, MaxValueLength, _T('\n'));
			ifs.ignore();		// _T('\n')

			// not found
			if (i < Size)
				toValue(values_[i], value, MaxValueLength);
		}
		ifs.close();
		return true;
	} else {
		return false;
	}
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
bool Settings<TItemSet, TMaxNameLength, TMaxValueLength>::save(const tstring& path) {
	tofstream ofs(path.c_str());
	if (ofs.is_open() && !ofs.bad()) {
		for (unsigned i = 0; i < Size; ++i) {
			ofs << Names[i] << NameValueDelim << values_[i] << std::endl;
		}
		ofs.close();
		return true;
	} else {
		return false;
	}
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
typename Settings<TItemSet, TMaxNameLength, TMaxValueLength>::ValueType& Settings<TItemSet, TMaxNameLength, TMaxValueLength>::operator [](const ItemEnum item) {
	return values_[item];
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
const typename Settings<TItemSet, TMaxNameLength, TMaxValueLength>::ValueType& Settings<TItemSet, TMaxNameLength, TMaxValueLength>::operator [](const ItemEnum item) const {
	return values_[item];
}


template <class TItemSet, int TMaxNameLength, int TMaxValueLength>
void Settings<TItemSet, TMaxNameLength, TMaxValueLength>::reset() {
	for (unsigned i = 0; i < Size; ++i)
		values_[i] = Defaults[i];
}


} //namespace kaynine


#endif //_KN_SETTINGS_INCLUDED_
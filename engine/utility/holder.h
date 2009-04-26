#ifndef HOLDER_INCLUDED
#define HOLDER_INCLUDED

#include "utility/safe_bool.h"

//=====================================================================================================================

template <class T>
class Holder : public safe_bool<Holder<T> > {
public:
	static T& get();

private:
	static void set(T& t);
	static T*& holder();
	bool boolean_test() const;

	friend T;
};

//=====================================================================================================================

template <class T>
T& Holder<T>::get() { 
	return *t(); 
}

//---------------------------------------------------------------------------------------------------------------------

template <class T>
void Holder<T>::set(T& t) {
	assert(!holder());
	holder() = &t;
}

//---------------------------------------------------------------------------------------------------------------------

template <class T>
T*& Holder<T>::holder() {
	static T* t = 0;
	return t;
}

//---------------------------------------------------------------------------------------------------------------------

template <class T>
bool Holder<T>::boolean_test() const {
	return holder() != 0;
}

//---------------------------------------------------------------------------------------------------------------------

#endif

#pragma once

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Holder : public safe_bool<Holder<T> > {
public:
	static T& inst() { return *subject(); }

	// interface: safe_bool
	bool boolean_test() const { return subject() != NULL; }

protected:
	// invoked in T's ctor
	static void set(T& t)  {
		assert(!subject());
		subject() = &t;
	}

	static T*& subject() {
		static T* t = NULL;
		return t;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

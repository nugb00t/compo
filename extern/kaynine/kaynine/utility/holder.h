#pragma once

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Holder : public SafeBool<Holder<T> > {
public:
	static T& inst() { return *subject(); }

	// interface: SafeBool
	bool boolean_test() const { return subject() != NULL; }

protected:
	// invoked in T's ctor
	static void set(T* t)  {
		assert(!subject() || !t);
		subject() = t;
	}

	static T*& subject() {
		static T* t = NULL;
		return t;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

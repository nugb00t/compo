#pragma once

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Holder : public safe_bool<Holder<T> > {
public:
	static T& inst() { return *t_; }

	// interface: safe_bool
	bool boolean_test() const { return t_ != NULL; }

private:
	// invoked in T's ctor
	static void set(T& t)  {
		assert(!subject());
		subject() = &t;
	}

private:
	static T*& subject() {
		static T* t = NULL;
		return t;
	}

	friend T;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

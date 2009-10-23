#ifndef KN_HOLDER_INCLUDED
#define KN_HOLDER_INCLUDED

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Holder {
public:
	static T& inst() { return *subject(); }

private:
	// invoked in T's ctor
	static void set(T& t)  {
		assert(!subject());
		subject() = &t;
	}

	static bool valid() { return subject() != 0; }

private:
	static T*& subject() {
		static T* t = 0;
		return t;
	}

	friend T;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

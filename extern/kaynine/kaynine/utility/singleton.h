#ifndef KN_SIGLETON_INCLUDED
#define KN_SIGLETON_INCLUDED

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
struct Singleton {
	Singleton() {}			//< Allows to skip ctor declaration in child classes

	static T& inst() {
		static T t;
		return t;
	}

private:
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
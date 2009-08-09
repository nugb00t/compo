#ifndef _KN_SIGLETON_INCLUDED_
#define _KN_SIGLETON_INCLUDED_


namespace kaynine {


template <class T>
struct Singleton {
	Singleton() {}

	static T& inst() {
		static T t;
		return t;
	}

private:
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

};


} // namespace kaynine


#endif
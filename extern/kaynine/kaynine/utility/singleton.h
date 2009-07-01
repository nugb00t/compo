#ifndef _KN_SIGLETON_INCLUDED_
#define _KN_SIGLETON_INCLUDED_


namespace kaynine {


template <class T>
struct Singleton {
	static T& get() {
		static T t;
		return t;
	}
};


} // namespace kaynine


#endif
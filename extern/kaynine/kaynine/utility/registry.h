#ifndef _KN_REGISTRY_INCLUDED_
#define _KN_REGISTRY_INCLUDED_

#include <assert.h>

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Registry {
	typedef const int Id;
	typedef std::map<Id, T*> Container;

public:
	static T* get(Id id) { return container()[id]; }

protected:
	Registry(T* t, Id id);
	~Registry();

private:
	Registry& operator =(const Registry&);		// disallowed
	Registry(const Registry&);

	static Container& container() { static Container cont; return cont; }

private:
	Id id_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
Registry<T>::Registry(T* child, Id id) : id_(id) {
#ifdef _DEBUG
	std::pair<Container::iterator, bool> res = 
#endif
		container().insert(std::make_pair(id, child));
#ifdef _DEBUG
	assert(res.second);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
Registry<T>::~Registry() {
#ifdef _DEBUG
	unsigned erased =
#endif
		container().erase(id_);
#ifdef _DEBUG
	assert(erased);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
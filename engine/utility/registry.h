#ifndef REGISTRY_INCLUDED
#define REGISTRY_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, unsigned SIZE>
class Registry : public kaynine::Singleton<Registry<T, SIZE> > {
protected:
	Registry();

public:
	void add(const unsigned id, T* registrant);
	void remove(const unsigned id);

	T& get(const unsigned id);
	const T& get(const unsigned id) const;

	const bool valid(const unsigned id) const;

private:
	T* registrants_[SIZE];

	friend kaynine::Singleton<Registry<T, SIZE> >;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, unsigned SIZE>
Registry<T, SIZE>::Registry() {
	::memset(registrants_, NULL, sizeof(T*) * SIZE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, unsigned SIZE>
void Registry<T, SIZE>::add(const unsigned id, T* registrant) {
	assert(id < SIZE);
	assert(registrants_[id] == 0);

	registrants_[id] = registrant;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, unsigned SIZE>
void Registry<T, SIZE>::remove(const unsigned id) {
	assert(id < SIZE);

	registrants_[id] = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, unsigned SIZE>
T& Registry<T, SIZE>::get(const unsigned id) {
	assert(id < SIZE);
	assert(registrants_[id]);

	return *registrants_[id];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, unsigned SIZE>
const T& Registry<T, SIZE>::get(const unsigned id) const {
	assert(id < SIZE);
	assert(registrants_[id]);

	return *registrants_[id];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, unsigned SIZE>
const bool Registry<T, SIZE>::valid(const unsigned id) const {
	assert(id < SIZE);

	return registrants_[id] != NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

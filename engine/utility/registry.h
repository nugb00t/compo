#ifndef REGISTRY_INCLUDED
#define REGISTRY_INCLUDED

#include <algorithm>

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Registry {
	typedef std::pair<unsigned, T*> Registrant;
	typedef std::map<unsigned, T*> Registrants;

	struct Updater : public std::unary_function<Registrant, void> {
		Updater(const float dt) : time(dt) {}
		void operator() (Registrant r) { r.second->update(time); }

		const float time;
	};

public:
	static bool add(const unsigned id, T* registrant);
	static bool remove(const unsigned id);

	static bool update(const float dt);

private:
	static Registrants& registrants();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool Registry<T>::add(const unsigned id, T* registrant) {
	std::pair<Registrants::const_iterator, bool> result = registrants().insert(std::make_pair(id, registrant));
	return result.second;
}

template <class T>
bool Registry<T>::remove(const unsigned id) {
	return registrants().erase(id) > 0;
}

template <class T>
bool Registry<T>::update(const float dt) {
	Updater up = std::for_each(registrants().begin(), registrants().end(), Updater(dt));
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
typename Registry<T>::Registrants& Registry<T>::registrants() {
	static Registrants registrants;
	return registrants;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Empty {};

template <class T>
bool registerComponent(const unsigned id, T* registrant) {
	return Registry<typename T::ComponentType>::add(id, registrant);
}

template <>
bool registerComponent<Empty>(const unsigned, Empty*);

template <class T>
bool unregisterComponent(const unsigned id) {
	return Registry<typename T::ComponentType>::remove(id);
}

template <>
bool unregisterComponent<Empty>(const unsigned);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

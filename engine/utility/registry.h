#ifndef REGISTRY_INCLUDED
#define REGISTRY_INCLUDED

//=====================================================================================================================

template <class T>
class Registry {
	typedef std::map<unsigned, T*> Registrants;

public:
	static bool add(const unsigned id, T* registrant);
	static bool remove(const unsigned id);

private:
	static Registrants& registrants();
};

//=====================================================================================================================

template <class T>
bool Registry<T>::add(const unsigned id, T* registrant) {
	std::pair<Registrants::const_iterator, bool> result = registrants().insert(std::make_pair(id, registrant));
	return result.second;
}

//---------------------------------------------------------------------------------------------------------------------

template <class T>
bool Registry<T>::remove(const unsigned id) {
	return registrants().erase(id) > 0;
}

//---------------------------------------------------------------------------------------------------------------------

template <class T>
typename Registry<T>::Registrants& Registry<T>::registrants() {
	static Registrants registrants;
	return registrants;
}

//---------------------------------------------------------------------------------------------------------------------

#endif

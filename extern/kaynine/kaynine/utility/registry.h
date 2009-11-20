#ifndef KN_REGISTRY_INCLUDED
#define KN_REGISTRY_INCLUDED

#include "singleton.h"
#include "../threading/sync_wrappers.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned TCapacity>
class Index : public Singleton<Index<TCapacity> > {
	static const unsigned TAKEN = (unsigned)-1;

public:
	static const unsigned CAPACITY = TCapacity;

	//-----------------------------------------------------------------------------------------------------------------

	template <class TComponent>
	class Registry : public Holder<Registry<TComponent> > {
	public:
		typedef TComponent COMPONENT_TYPE;
		static const unsigned CAPACITY = TCapacity;

		Registry() { 
            set(*this); 
            memset(registrants_, NULL, sizeof(TComponent*) * TCapacity); 
        }

	public:
		inline void add(const unsigned id, TComponent* registrant) 	{ 
            assert(id < TCapacity && registrants_[id] == 0);
            registrants_[id] = registrant;
        }

		inline void remove(const unsigned id) {
            assert(id < TCapacity);
            registrants_[id] = NULL;
        }

		inline TComponent& get(const unsigned id) {
            assert(id < TCapacity && registrants_[id]);
            return *registrants_[id];
        }

		inline const TComponent& get(const unsigned id) const {
            assert(id < TCapacity && registrants_[id]);
            return *registrants_[id];
        }

		inline const bool valid(const unsigned id) const {
            assert(id < TCapacity);
            return registrants_[id] != NULL;
        }

	private:
		TComponent* registrants_[TCapacity];
	};

	//-----------------------------------------------------------------------------------------------------------------

	class RegistrantBase {
	public:
		RegistrantBase() : id_(Index::inst().enlist())	{}
		~RegistrantBase() { Index::inst().dismiss(id_); }

		inline const unsigned id() const { return id_; }

	private:
		const unsigned id_;
	};

	//-----------------------------------------------------------------------------------------------------------------

	template <class TComponent1>
	class Registrant1 : public RegistrantBase {
	public:
        Registrant1()	{ Registry<TComponent1::Type>::inst().add(id(), &component1_); }

		~Registrant1()	{ Registry<TComponent1::Type>::inst().remove(id()); }

	private:
		TComponent1 component1_;
	};

	//-----------------------------------------------------------------------------------------------------------------

	template <class TComponent1, class TComponent2>
	class Registrant2 : public RegistrantBase {
	public:
		Registrant2()	{ Registry<TComponent1::Type>::inst().add(id(), &component1_);
						  Registry<TComponent2::Type>::inst().add(id(), &component2_); }

		~Registrant2()	{ Registry<TComponent1::Type>::inst().remove(id());
						  Registry<TComponent2::Type>::inst().remove(id()); }

	private:
		TComponent1 component1_;
		TComponent2 component2_;
	};

	//-----------------------------------------------------------------------------------------------------------------

	template <class TComponent1, class TComponent2, class TComponent3>
	class Registrant3 : public RegistrantBase {
	public:
		Registrant3()	{ Registry<TComponent1::Type>::inst().add(id(), &component1_);
						  Registry<TComponent2::Type>::inst().add(id(), &component2_);
						  Registry<TComponent3::Type>::inst().add(id(), &component3_); }

		~Registrant3()	{ Registry<TComponent1::Type>::inst().remove(id());
						  Registry<TComponent2::Type>::inst().remove(id());
						  Registry<TComponent3::Type>::inst().remove(id()); }

	private:
		TComponent1 component1_;
		TComponent2 component2_;
		TComponent3 component3_;
	};

	//-----------------------------------------------------------------------------------------------------------------

protected:
	Index()
		: firstFree_(0), size_(0), guard_(CriticalSection::UNLOCKED) {
			for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
				ids_[i] = i + 1;
	}

public:
	inline const unsigned enlist() {
		assert(size_ <= ServerState::MAX_ENTITIES);

		AutoLock<> lock(guard_);

		const unsigned ret = firstFree_;
		firstFree_ = ids_[ret];
		ids_[ret] = TAKEN;

		++size_;

		return ret;
	}

	inline void dismiss(const unsigned id) {
		assert(id <= ServerState::MAX_ENTITIES);
		assert(size_ >= 0);

		AutoLock<> lock(guard_);

		ids_[id] = firstFree_;
		firstFree_ = id;

		--size_;
	}

	inline const unsigned size() const { return size_; }

private:
	unsigned ids_[TCapacity];
	unsigned firstFree_;
	unsigned size_;

	CriticalSection guard_;

	friend struct Singleton<Index<TCapacity> >;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

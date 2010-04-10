#pragma once

#include <assert.h>

#include "../debug/macros.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// usage:
// buffer.get(-2).field
template <class TValue, unsigned TCapacity>
class StaticArray {
public:
	typedef TValue VALUE_TYPE;
    static const unsigned CAPACITY = TCapacity;

public:

	//-----------------------------------------------------------------------------------------------------------------

	class Range {
	public:
		inline Range(StaticArray& staticArray);

		inline const bool finished() { return index_ >= (int)staticArray_.size_; }
		inline void next();

		inline TValue& get() { return staticArray_[index_]; }
		inline const TValue& get() const { return staticArray_[index_]; }

		inline const unsigned index() const { return index_; }

	private:
		StaticArray& staticArray_;
		int index_;
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	StaticArray(const TValue& null = 0) : null_(null), vacant_(0), size_(0) {}

	inline const unsigned add(TValue value);
	inline void remove(const unsigned i);

	inline TValue& operator [](const unsigned i) { assert(valid(i)); return values_[i]; }
	inline const TValue& operator [](const unsigned i) const { assert(valid(i)); return values_[i]; }

	inline const bool valid(const unsigned i) const { return i < size_ && values_[i]; }

private:
    TValue values_[CAPACITY];
	const TValue& null_;

	unsigned vacant_;
	unsigned size_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TCapacity>
StaticArray<TValue, TCapacity>::Range::Range(StaticArray& staticArray) : staticArray_(staticArray), index_(0) {
	while (!finished() && !staticArray_[index_])
		++index_;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TCapacity>
void StaticArray<TValue, TCapacity>::Range::next() {
	++index_;
	while (!finished() && !staticArray_[index_])
		++index_;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TCapacity>
const unsigned StaticArray<TValue, TCapacity>::add(TValue value) {
	assert(value);	// StaticArray operates with non-zero TValues only

	const unsigned inserted = vacant_;
	assert(inserted < CAPACITY);
	values_[inserted] = value;

	if (vacant_ < size_)
		while(vacant_ < size_ && values_[vacant_])
			++vacant_;
	else
		vacant_ = ++size_;

	return inserted;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TCapacity>
void StaticArray<TValue, TCapacity>::remove(const unsigned i) {
	assert(i < size_ && i != vacant_);
	values_[i] = null_;
	vacant_ = i;

	if (i == size_ - 1)
		--size_;
}

//---------------------------------------------------------------------------------------------------------------------

}

#pragma once

#include <assert.h>

#include "../debug/macros.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// usage:
// buffer.get(-2).field
template <class TValue, unsigned TSize>
class StaticArray {
public:
	typedef TValue VALUE_TYPE;
    static const unsigned SIZE = TSize;

public:

	//-----------------------------------------------------------------------------------------------------------------

	class Range {
	public:
		inline Range(StaticArray& array);

		inline const bool finished() { return current_ >= (int)array_.size_; }
		inline void next();

		inline		 TValue& get()		 { return array_[current_]; }
		inline const TValue& get() const { return array_[current_]; }

		inline const unsigned index() const { return current_; }

	private:
		StaticArray& array_;
		int current_;
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	StaticArray(const TValue& null = 0) : null_(null), vacant_(0), size_(0) {}

	inline const unsigned add(const TValue value);
	inline void remove(const unsigned i);

	inline		 TValue& operator [](const unsigned i)		 { assert(valid(i)); return items_[i]; }
	inline const TValue& operator [](const unsigned i) const { assert(valid(i)); return items_[i]; }

	inline const bool valid(const unsigned i) const { return i < size_ && items_[i]; }

private:
    TValue items_[SIZE];
	const TValue& null_;

	unsigned vacant_;
	unsigned size_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
StaticArray<TValue, TSize>::Range::Range(StaticArray& staticArray) : array_(staticArray), current_(0) {
	while (!finished() && !array_[current_])
		++current_;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TSize>
void StaticArray<TValue, TSize>::Range::next() {
	++current_;
	while (!finished() && !array_[current_])
		++current_;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TSize>
const unsigned StaticArray<TValue, TSize>::add(const TValue value) {
	assert(value);	// StaticArray operates with non-zero TValues only

	const unsigned inserted = vacant_;
	assert(inserted < SIZE);
	items_[inserted] = value;

	if (vacant_ < size_)
		while(vacant_ < size_ && items_[vacant_])
			++vacant_;
	else
		vacant_ = ++size_;

	return inserted;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TSize>
void StaticArray<TValue, TSize>::remove(const unsigned i) {
	assert(i < size_ && i != vacant_);
	items_[i] = null_;
	vacant_ = i;

	if (i == size_ - 1)
		--size_;
}

//---------------------------------------------------------------------------------------------------------------------

}

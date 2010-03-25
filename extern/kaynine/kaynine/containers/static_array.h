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
	StaticArray(const TValue& null = 0) : null_(null), vacant_(0), size_(0) {}

	const unsigned add(TValue& value) {
		assert(value != null_);	// StaticArray operates with non-zero TValues only

		if (vacant_ < size_) {
			values_[vacant_] = value;

			const unsigned inserted = vacant_;
			while(vacant_ < size_ && values_[vacant_] != null_)
				++vacant_;

			return inserted;
		} else {
			assert(size_ < CAPACITY - 1);

			++vacant_;
			values_[++size_] = value;
		}
	}

	void remove(const unsigned i) {
		assert(i < size_ && i != vacant_);
		values_[i] = null_;
		vacant_ = i;
		
		if (i == size_ - 1)
			--size_;
	}

	TValue& operator [](const unsigned i) { assert(i < size_); return values_[i]; }
	const TValue& operator [](const unsigned i) const { assert(i < size_); return values_[i]; }

private:
    TValue values_[CAPACITY];
	const TValue& null_;

	unsigned vacant_;
	unsigned size_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

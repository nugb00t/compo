#pragma once

#include <assert.h>

#include "../debug/macros.h"
#include "../utility/safe_bool.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// usage:
// buffer.get(-2).field
template <class TValue, unsigned TSize = 4>
class CyclicBuffer : public kaynine::SafeBool<CyclicBuffer<TValue, TSize> > {
public:
	typedef TValue VALUE_TYPE;
    static const unsigned SIZE = TSize;

public:
	enum Mode {
		CLEAR_FRAME
	};

public:
    CyclicBuffer() : lastUpdated_(-1) {}

	// interface: kaynine::SafeBool
	bool boolean_test() const { return lastUpdated_ != -1; }

	// interface: own
	inline void advance() {
		lastUpdated_ = (lastUpdated_ + 1) % SIZE;
	}

	void advance(Mode DEBUG_ONLY(mode)) {
		assert(mode == CLEAR_FRAME);

		advance();
		memset(&ts_[lastUpdated_], 0, sizeof(ts_[lastUpdated_]));
	}

	void add(const TValue& value) {
		advance();
		ts_[lastUpdated_] = value;
	}

    // Negative 'index' values will yield previously added values
	const TValue& get(const int index = 0) const {
		assert(-(int)SIZE < index && index <= 0 && lastUpdated_ != -1);

		const unsigned requested = (lastUpdated_ + index) % SIZE;
		return ts_[requested];
	}

	TValue& get(const int index = 0) {
		assert(-(int)SIZE < index && index <= 0 && lastUpdated_ != -1);

		const unsigned requested = (lastUpdated_ + index) % SIZE;
		return ts_[requested];
	}

private:
    TValue ts_[SIZE];
    int lastUpdated_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#ifndef KN_CYCLIC_BUFFER_INCLUDED
#define KN_CYCLIC_BUFFER_INCLUDED

#include <assert.h>

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// usage:
// buffer.get(-2).field
template <class TValue, unsigned TSize>
class CyclicBuffer {
public:
	typedef TValue VALUE_TYPE;
    static const unsigned SIZE = TSize;

public:
	enum Mode {
		CLEAR_FRAME
	};

public:
    CyclicBuffer() : lastUpdated_(-1) {}

	inline void advance() {
		lastUpdated_ = (lastUpdated_ + 1) % SIZE;
	}

	void advance(Mode mode) {
		assert(mode == CLEAR_FRAME);

		advance();
		memset(&ts_[lastUpdated_], 0, sizeof(ts_[lastUpdated_]));
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

#endif
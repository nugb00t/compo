#ifndef CYCLIC_BUFFER_INCLUDED
#define CYCLIC_BUFFER_INCLUDED

#include <assert.h>

//////////////////////////////////////////////////////////////////////////////////////////////////

// usage:
// buffer.get(-2).field
template <class TValue, unsigned TSize>
class CyclicBuffer {
public:
    static const unsigned SIZE = TSize;

public:
    CyclicBuffer() : lastUpdated_(-1) {}

    void add(const TValue& t) {
        lastUpdated_ = (lastUpdated_ + 1) % SIZE;
        ts_[lastUpdated_] = t;
    }

    const TValue& get(const int index) const {
        assert(-(int)SIZE < index && index <= 0 && lastUpdated_ != -1);
		const unsigned requested = (lastUpdated_ + index) % SIZE;
        return ts_[requested];
    }

private:
    TValue ts_[SIZE];
    int lastUpdated_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
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
        const unsigned justAdded = ++lastUpdated_ % SIZE;
        ts_[justAdded] = t;
    }

    const TValue& get(const int index) const {
        assert(-SIZE < index <= 0 && lastUpdated_ != -1);
        return ts_[(lastUpdated_ + index) % SIZE];
    }

private:
    TValue ts_[SIZE];
    int lastUpdated_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
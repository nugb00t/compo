#ifndef PROFILER_BASE_INCLUDED
#define PROFILER_BASE_INCLUDED

#include <assert.h>

#include "core/time.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

//
//	const TheProfiler::Period& period = TheProfiler::inst().getPeriod(LOGIC_THREAD);
//
template <unsigned TTrackerCount, unsigned THistoryDepth>
class ProfilerBase : public kaynine::Singleton<ProfilerBase<TTrackerCount, THistoryDepth> > {
public:
	static const unsigned SECTION_COUNT = TTrackerCount;
	static const unsigned HISTORY_DEPTH = THistoryDepth;

public:
    class StopWatch {
    public:
        explicit StopWatch(const unsigned id)
            : id_(id), start_(Time::inst().msec()) {}

        ~StopWatch() {
            Profiler::inst().track(id_, start_, Time::inst().msec());
        }

    private:
        unsigned id_;
        unsigned long start_;
    };

    struct Period {
        Period() {};
        Period(const unsigned long start_, const unsigned long end_) : begin(start_), end(end_) {}
		const unsigned long length() const { return end - begin; }
		const unsigned long middle() const { return (end + begin) / 2; }

        unsigned long begin;
        unsigned long end;
    };

public:
	ProfilerBase() {
		// avoid uninitialized section counters by placing dummy periods in the beginning
		for (unsigned id = 0; id < SECTION_COUNT; ++id)
			track(id, 0, 0);
	}

    const Period& get(const unsigned id, const int age = 0) const {
        assert(id < TTrackerCount);
		kaynine::AutoLock<> lock(guard_);
        return trackers_[id].get(age);
    }

protected:
	void track(const unsigned id, const unsigned long begin, const unsigned long end) {
		assert(id < TTrackerCount);

		kaynine::AutoLock<> lock(guard_);
		trackers_[id].add(Period(begin, end));
	}

private:
    kaynine::CyclicBuffer<Period, THistoryDepth> trackers_[TTrackerCount];
	mutable kaynine::CriticalSection guard_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
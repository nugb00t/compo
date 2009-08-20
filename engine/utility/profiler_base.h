#ifndef PROFILER_BASE_INCLUDED
#define PROFILER_BASE_INCLUDED

#include <assert.h>

#include "kaynine/threading/sync_wrappers.h"

#include "cyclic_buffer.h"
#include "timer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

//
//	const TheProfiler::Period& period = TheProfiler::inst().getPeriod(LOGIC_THREAD);
//
template <unsigned TTrackerCount, unsigned THistoryDepth>
class ProfilerBase : public kaynine::Singleton<ProfilerBase<TTrackerCount, THistoryDepth> > {
public:
    static const unsigned SECTION_COUNT = TTrackerCount;

public:
    class StopWatch {
    public:
        explicit StopWatch(const unsigned id)
            : id_(id), start_((float)Timer::inst().now()) {}

        ~StopWatch() {
            Profiler::inst().track(id_, start_, (float)Timer::inst().now());
        }

    private:
        unsigned id_;
        float start_;
    };

    struct Period {
        Period() {};
        Period(const float start_, const float end_) : start(start_), end(end_) {}

        float start;
        float end;
    };

public:
    void track(const unsigned id, const float start, const float end) {
        assert(id < TTrackerCount);

		kaynine::AutoLock<> lock(guard_);
        trackers_[id].add(Period(start, end));
    }

    const Period& get(const unsigned id, const int age = 0) const {
        assert(id < TTrackerCount);
		kaynine::AutoLock lock(guard_);
        return trackers_[id].get(age);
    }

private:
    CyclicBuffer<Period, THistoryDepth> trackers_[TTrackerCount];
	kaynine::CriticalSection guard_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

#endif
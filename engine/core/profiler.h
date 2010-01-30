#ifndef PROFILER_INCLUDED
#define PROFILER_INCLUDED

#include "profiler.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Profiler {
public:
	enum Section {
		SYSTEM,
		SERVER,
		SERVER_ARBITER,
		SERVER_LOGIC,
		LOCAL_CLIENT,
		VIDEO,

		SECTION_COUNT
	};

	static const unsigned SECTION_COLORS[SECTION_COUNT];
	static const unsigned HISTORY_DEPTH = 16;

public:
	//-----------------------------------------------------------------------------------------------------------------

	class StopWatch {
	public:
		explicit StopWatch(const Section section);
		~StopWatch();

	private:
		const Section section_;
		unsigned start_;
	};

	//-----------------------------------------------------------------------------------------------------------------

	struct Period {
		unsigned begin;
		unsigned end;

		Period() : begin(0), end(0) {}
		Period(const unsigned start_, const unsigned end_) : begin(start_), end(end_) {}

		const unsigned length() const { return end - begin; }
		const unsigned middle() const { return (end + begin) / 2; }
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	Profiler();
	const Period& get(const Section section, const int age = 0) const;

protected:
	void track(const Section section, const unsigned begin, const unsigned end);

private:
	kaynine::CyclicBuffer<Period, HISTORY_DEPTH> trackers_[SECTION_COUNT];
	mutable kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
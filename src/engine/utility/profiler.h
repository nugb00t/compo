#pragma once

#include "profiler.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Profiler : public kaynine::Singleton<Profiler> {
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

	static const uint SECTION_COLORS[SECTION_COUNT];
	static const uint HISTORY_DEPTH = 16;

public:
	//-----------------------------------------------------------------------------------------------------------------

	class StopWatch {
	public:
		explicit StopWatch(const Section section);
		~StopWatch();

	private:
		const Section section_;
		uint start_;
	};

	//-----------------------------------------------------------------------------------------------------------------

	struct Period {
		uint begin;
		uint end;

		Period() : begin(0), end(0) {}
		Period(const uint start_, const uint end_) : begin(start_), end(end_) {}

		const uint length() const { return end - begin; }
		const uint middle() const { return (end + begin) / 2; }
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	Profiler();
	const Period& get(const Section section, const int age = 0) const;

protected:
	void track(const Section section, const uint begin, const uint end);

private:
	kaynine::CyclicBuffer<Period, HISTORY_DEPTH> trackers_[SECTION_COUNT];
	mutable kaynine::CriticalSection guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

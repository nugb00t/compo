#ifndef PROFILER_INCLUDED
#define PROFILER_INCLUDED

#include "utility/callable.h"
#include "utility/profiler_base.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ProfilerSections {
	enum SectionID {
		//LOGIC_THREAD,
		VIDEO_THREAD,
		SECTION_COUNT_
	};

	static const unsigned HISTORY_DEPTH = 16;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Profiler : public ProfilerSections, public ProfilerBase<ProfilerSections::SECTION_COUNT_, ProfilerSections::HISTORY_DEPTH> {};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
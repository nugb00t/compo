#ifndef PROFILER_INCLUDED
#define PROFILER_INCLUDED

#include "utility/profiler_base.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ProfilerSections {
	enum SectionID {
        SYSTEM,
		SERVER,
        SERVER_ARBITER,
        SERVER_LOGIC,
        LOCAL_CLIENT,
		VIDEO,
		SECTION_COUNT_
	};

	static const unsigned HISTORY_DEPTH = 16;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Profiler : public ProfilerSections, public ProfilerBase<ProfilerSections::SECTION_COUNT_, ProfilerSections::HISTORY_DEPTH> {};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
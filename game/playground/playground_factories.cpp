#include "stdafx.h"

#include "playground_factories.h"

#include "entities/orb/orb_logic.h"
#include "entities/orb/orb_video.h"

#include "screens/thread_profiler/thread_profiler_video.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LogicComponent* GameEntityFactory::createLogicComponent(const unsigned type) {
	switch (type) {
		case ENTITY_ORB:
			return new OrbLogic;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoComponent* GameEntityFactory::createVideoComponent(const unsigned type) {
	switch (type) {
		case ENTITY_ORB:
			return new OrbVideo;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//LogicComponent* GameScreenFactory::createLogicComponent(const unsigned type) {
//	switch (type) {
//		case SCREEN_THREAD_PROFILER:
//			return NULL;
//			break;
//		default:
//			assert(false);
//			return NULL;
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ScreenVideoComponent* GameScreenFactory::createVideoComponent(const unsigned type) {
	switch (type) {
		case SCREEN_THREAD_PROFILER:
			return new ThreadProfilerVideo;
			break;
		default:
			assert(false);
			return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

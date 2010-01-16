#include "stdafx.h"

#include "playground_entity_factory.h"

#include "playground_entities.h"

#include "orb/orb_logic.h"
#include "orb/orb_video.h"

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

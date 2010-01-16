#ifndef PLAYGROUND_ENTITY_FACTORY_INCLUDED
#define PLAYGROUND_ENTITY_FACTORY_INCLUDED

#include "entity_factory.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameEntityFactory : public engine::EntityFactory {
public:
    // interface: EntityFactory
	virtual engine::LogicComponent* createLogicComponent(const unsigned type);
	virtual engine::VideoComponent* createVideoComponent(const unsigned type);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

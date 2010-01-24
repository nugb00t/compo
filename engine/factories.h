#ifndef FACTORIES_INCLUDED
#define FACTORIES_INCLUDED

#include "logic/logic_component.h"
#include "video/video_component.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntityFactory {
public:
	virtual LogicComponent* createLogicComponent(const unsigned type) = 0;
	virtual VideoComponent* createVideoComponent(const unsigned type) = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreenFactory {
public:
	//virtual LogicComponent* createLogicComponent(const unsigned type) = 0;
	virtual ScreenVideoComponent* createVideoComponent(const unsigned type) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

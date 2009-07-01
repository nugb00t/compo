#ifndef LOGIC_COMPONENT_INCLUDED
#define LOGIC_COMPONENT_INCLUDED

#include "utility/intrusive_ptr_base.h"
#include "utility/updatable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LogicComponent : public Updatable {
public:
	typedef engine::LogicComponent Type;
};

typedef boost::intrusive_ptr<LogicComponent> LogicComponentPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

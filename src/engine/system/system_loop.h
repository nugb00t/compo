#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SystemLoop : public kaynine::ThreadObject {
public:
	// interface: kaynine::ThreadObject
	virtual void terminate();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

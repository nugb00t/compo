#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SystemLoop : public kaynine::ThreadObject {
public:
	virtual kaynine::Event& quit();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

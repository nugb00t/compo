#ifndef LOCAL_CLIENT_INCLUDED
#define LOCAL_CLIENT_INCLUDED

#include "system/input_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClient {
public:
	static const unsigned FRAMERATE = 60;

public:
	LocalClient();

	void update();

protected:
    virtual void handleControls(const InputInterface::Controls& controls) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<LocalClient> Client;

}

#endif
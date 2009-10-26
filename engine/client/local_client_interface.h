#ifndef LOCAL_CLIENT_INTERFACE_INCLUDED
#define LOCAL_CLIENT_INTERFACE_INCLUDED

#include "input/input_data.h"
#include "client_data.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClientInterface {
public:
	static const unsigned FRAMERATE = 60;

public:
	LocalClientInterface();

	void update();

protected:
    virtual void handleControls(const InputData& controls) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<LocalClientInterface> LocalClient;

}

#endif
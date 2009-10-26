#ifndef LOCAL_CLIENT_INTERFACE_INCLUDED
#define LOCAL_CLIENT_INTERFACE_INCLUDED

#include "system/input_interface.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LocalClientInterface {
public:
	static const unsigned FRAMERATE = 60;

    struct Delta {
        Vector3 loc;
    };

public:
	LocalClientInterface();

	void update();

protected:
    virtual void handleControls(const InputInterface::Controls& controls) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<LocalClientInterface> LocalClient;

}

#endif

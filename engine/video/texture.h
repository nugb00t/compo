#ifndef TEXTURE_INCLUDED
#define TEXTURE_INCLUDED

#include "utility/intrusive_ptr_base.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Texture : public IntrusivePtrBase {
public:
	virtual bool load(const TCHAR* const path) = 0;
	virtual void activate(const unsigned stage) = 0;
};

typedef boost::intrusive_ptr<Texture> TexturePtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

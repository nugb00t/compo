#ifndef EFFECT_INCLUDED
#define EFFECT_INCLUDED

#include "utility/intrusive_ptr_base.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Effect : public IntrusivePtrBase {
public:
	virtual bool load(const TCHAR* const path) = 0;
	virtual const char* errors() const = 0;
	virtual void activate(const Matrix44& transform) = 0;
	virtual void deactivate() = 0;
};

typedef boost::intrusive_ptr<Effect> EffectPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

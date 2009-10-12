#ifndef EFFECT_INCLUDED
#define EFFECT_INCLUDED

#include "utility/intrusive_ptr_base.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Uniform {
    enum Type {
        None = 0,


        Float,
        Vector,
        Matrix,
        Texture,

        Uniform_COUNT
    };

    static const Uniform EMPTY;

    Type type;
    const char* name;
    void* value;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Effect : public IntrusivePtrBase {
public:
 	virtual const char* errors() const = 0;

    virtual void setUniforms(const Uniform* const uniforms) = 0;
    virtual void setTransform(const Matrix44& transform) = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;
};

typedef boost::intrusive_ptr<Effect> EffectPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

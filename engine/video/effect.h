#ifndef EFFECT_INCLUDED
#define EFFECT_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Effect : public kaynine::IntrusivePtrBase {
public:
    struct Uniform {
        static const Uniform TERMINATOR;

        const char* name;
        void* value;
    };

    struct TextureUniform {
        static const TextureUniform TERMINATOR;

        const char* name;
        const TCHAR* path;
    };

    static const unsigned MAX_TEXTURES = 8;

public:
 	virtual const char* errors() const = 0;

    virtual void setUniforms(const Uniform* const uniforms) = 0;
    virtual void setTexUniforms(const TextureUniform* const texUniforms) = 0;

    virtual void setTransform(const Matrix44& transform) = 0;

	virtual unsigned begin() = 0;
    virtual void next() = 0;
	virtual void end() = 0;
};

typedef boost::intrusive_ptr<Effect> EffectPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

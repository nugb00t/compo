#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Effect {
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

    static const uint MAX_TEXTURES = 8;

public:
	virtual ~Effect() {}

	virtual void setUniforms(const Uniform* const uniforms) = 0;
	virtual void setTexUniforms(const TextureUniform* const texUniforms) = 0;
	virtual void setTransform(const Matrix44& transform) = 0;

	virtual uint begin(class Video& video) = 0;
	virtual void next() = 0;
	virtual void end() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

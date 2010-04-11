#pragma once

#include "../effect.h"

#include "video_d3d9.h"
#include "texture_d3d9.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EffectD3D9 : public Effect {
public:
	EffectD3D9(ID3DXEffect& effect, const Video::VertexDeclType vertexDecl);

	// interface: Effect
    virtual void setUniforms(const Uniform* const uniforms) { assert(uniforms); uniforms_ = uniforms; }
    virtual void setTexUniforms(const TextureUniform* const texUniforms);
    virtual void setTransform(const Matrix44& transform);

	virtual uint begin(Video& video);
    virtual void next();
	virtual void end();

private:
	ID3DXEffect& effect_;
	const Video::VertexDeclType vertexDecl_;

	boost::scoped_ptr<TextureD3D9> textures_[Effect::MAX_TEXTURES];	// TODO: check if scoped_ptr is needed indeed
    const Uniform* uniforms_;
    const TextureUniform* texUniforms_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

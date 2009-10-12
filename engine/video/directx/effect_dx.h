#ifndef EFFECT_DX_INCLUDED
#define EFFECT_DX_INCLUDED

#include "video/directx/texture_dx.h"
#include "video/directx/vertex_decl_dx.h"

#include "video/effect.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EffectDX : public Effect {
public:
	EffectDX(const TCHAR* const path, const VertexDeclPtr vertexDecl);
	~EffectDX();

	// interface: Effect
	virtual const char* errors() const { return reinterpret_cast<const char*>(errors_->GetBufferPointer()); }

    virtual void setUniforms(const Uniform* const uniforms) { assert(uniforms); uniforms_ = uniforms; }
    virtual void setTexUniforms(const TextureUniform* const texUniforms);

    virtual void setTransform(const Matrix44& transform);

	virtual unsigned begin();
    virtual void next();
	virtual void end();

private:
	static const TCHAR* const FX_PATHS[];

	// Direct3D
	ID3DXEffect* effect_;
	ID3DXBuffer* errors_;

	VertexDeclPtr vertexDecl_;

    TextureDXPtr textures_[Effect::MAX_TEXTURES];
    const Uniform* uniforms_;
    const TextureUniform* texUniforms_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

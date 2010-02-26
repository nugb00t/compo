#pragma once

#include "video/direct3d9/texture_d3d9.h"
#include "video/direct3d9/vertex_decls_d3d9.h"

#include "video/effect.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EffectD3D9 : public Effect {
public:
	EffectD3D9(const VertexDecls::Type vertexDecl);
	~EffectD3D9();

	// interface: Effect
	virtual const char* errors() const { return reinterpret_cast<const char*>(errors_->GetBufferPointer()); }

    virtual void setUniforms(const Uniform* const uniforms) { assert(uniforms); uniforms_ = uniforms; }
    virtual void setTexUniforms(const TextureUniform* const texUniforms);

    virtual void setTransform(const Matrix44& transform);

	virtual uint begin();
    virtual void next();
	virtual void end();

private:
	static const TCHAR* const FX_PATHS[];

	// Direct3D
	ID3DXEffect* effect_;
	ID3DXBuffer* errors_;

	const VertexDecls::Type vertexDecl_;

	boost::scoped_ptr<TextureD3D9> textures_[Effect::MAX_TEXTURES];
    const Uniform* uniforms_;
    const TextureUniform* texUniforms_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

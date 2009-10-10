#ifndef EFFECT_DX_INCLUDED
#define EFFECT_DX_INCLUDED

#include "video/vertex_decl.h"

#include "video/effect.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EffectDX : public Effect {
public:
	EffectDX(const TCHAR* const path, const VertexDeclPtr vertexDecl, const TexturePtr texture);
	~EffectDX();

	// interface: Effect
	virtual const char* errors() const { return reinterpret_cast<const char*>(errors_->GetBufferPointer()); }

	virtual void activate(const Matrix44& transform);
	virtual void deactivate();

private:
	static const TCHAR* const FX_PATHS[];

	// Direct3D
	ID3DXEffect* effect_;
	ID3DXBuffer* errors_;

	engine::VertexDeclPtr vertexDecl_;
	engine::TexturePtr texture_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

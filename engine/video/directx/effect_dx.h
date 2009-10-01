#ifndef EFFECT_DX_INCLUDED
#define EFFECT_DX_INCLUDED

#include "video/effect.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EffectDX : public Effect {
public:
	EffectDX(const TCHAR* const path);
	~EffectDX();

	// interface: Effect
	virtual const char* errors() const { return reinterpret_cast<const char*>(errors_->GetBufferPointer()); }

	virtual void activate(const Matrix44& transform);
	virtual void deactivate();

private:
	ID3DXEffect* effect_;
	ID3DXBuffer* errors_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

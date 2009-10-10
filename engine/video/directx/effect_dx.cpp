#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "video_system_dx.h"
#include "texture_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EffectDX::EffectDX(const TCHAR* const path)
: effect_(NULL), errors_(NULL) {
	assert(path);

	HRESULT hr = D3DXCreateEffectFromFile(&VideoDX::inst().device(), path, 0, 0, D3DXSHADER_DEBUG, 0, &effect_, &errors_);
	if (hr != D3D_OK)  {
		assert(errors_);

		const char* charBuffer = reinterpret_cast<const char*>(errors_->GetBufferPointer());
		MessageBoxA(0, charBuffer, 0, 0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EffectDX::~EffectDX() {
	if (effect_)
		effect_->Release();

	if (errors_)
		errors_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectDX::activate(const Matrix44& transform) {
	assert(effect_);

	D3DXHANDLE wvpHandle = effect_->GetParameterByName(0, "gWVP");
	CHECKED_D3D_CALL(effect_->SetMatrix(wvpHandle, transform.d3dMatrix()));

	D3DXHANDLE techHandle = effect_->GetTechniqueByName("TransformTech");
	CHECKED_D3D_CALL(effect_->SetTechnique(techHandle));

	UINT numPasses = 0;
	CHECKED_D3D_CALL(effect_->Begin(&numPasses, D3DXFX_DONOTSAVESTATE));

	CHECKED_D3D_CALL(effect_->BeginPass(0));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectDX::deactivate() {
	assert(effect_);

	CHECKED_D3D_CALL(effect_->EndPass());
	CHECKED_D3D_CALL(effect_->End());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

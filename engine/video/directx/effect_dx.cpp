#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "video_system_dx.h"
#include "texture_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EffectDX::EffectDX(const TCHAR* const path, const VertexDeclPtr vertexDecl, const TexturePtr texture)
: effect_(NULL), errors_(NULL), vertexDecl_(vertexDecl), texture_(texture), uniforms_(&Uniform::EMPTY) {
	assert(path);
	assert(vertexDecl_);
	assert(texture_);

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

void EffectDX::setUniforms(const Uniform* const uniforms) {
    if (!uniforms)
        uniforms_ = &Uniform::EMPTY;
    else
        uniforms_ = uniforms;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectDX::setTransform(const Matrix44& transform) {
    D3DXHANDLE wvpHandle = effect_->GetParameterByName(0, "transform");
    CHECKED_D3D_CALL(effect_->SetMatrix(wvpHandle, transform.d3dMatrix()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectDX::activate() {
	assert(effect_);
    assert(uniforms_);

	texture_->activate(0);
	vertexDecl_->activate();

	D3DXHANDLE techHandle = effect_->GetTechniqueByName("TransformTech");
	CHECKED_D3D_CALL(effect_->SetTechnique(techHandle));

    for (const Uniform* uniforms = uniforms_; uniforms->value; ++uniforms) {
        D3DXHANDLE handle = effect_->GetParameterByName(NULL, uniforms->name);
        effect_->SetValue(handle, uniforms->value, D3DX_DEFAULT);
    }

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

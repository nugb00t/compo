#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "video_system_dx.h"
#include "texture_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EffectDX::EffectDX(const TCHAR* const path, const VertexDeclPtr vertexDecl)
: effect_(NULL), errors_(NULL), vertexDecl_(vertexDecl), uniforms_(&Uniform::TERMINATOR) {
	assert(path);
	assert(vertexDecl_);

	HRESULT hr = D3DXCreateEffectFromFile(&VideoDX::inst().device(), path, 0, 0, D3DXSHADER_DEBUG, 0, &effect_, &errors_);
	if (hr != D3D_OK)  {
		assert(errors_);

		const char* charBuffer = reinterpret_cast<const char*>(errors_->GetBufferPointer());
		MessageBoxA(0, charBuffer, NULL, 0);
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

void EffectDX::setTexUniforms(const TextureUniform* const texUniforms) { 
    assert(texUniforms);

    texUniforms_ = texUniforms;

    unsigned i = 0;
    for (; i < MAX_TEXTURES; ++i) {
        if (!texUniforms_[i].name || !texUniforms_[i].path) {
            assert(!texUniforms_[i].name && !texUniforms_[i].path);
            break;
        } else if (!textures_[i] || textures_[i]->path() && _tcscmp(texUniforms_[i].path, textures_[i]->path()))
            textures_[i] = new TextureDX(texUniforms_[i].path);
    }

    for (; i < MAX_TEXTURES; ++i)
        textures_[i] = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectDX::setTransform(const Matrix44& transform) {
    D3DXHANDLE handle = effect_->GetParameterByName(0, "transform");
    assert(handle);
    CHECKED_D3D_CALL(effect_->SetMatrix(handle, transform.d3dMatrix()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned EffectDX::begin() {
	assert(effect_);
    assert(uniforms_);

	vertexDecl_->activate();

	D3DXHANDLE techHandle = effect_->GetTechniqueByName("TransformTech");
	CHECKED_D3D_CALL(effect_->SetTechnique(techHandle));

    // textures
    for (unsigned i = 0; i < MAX_TEXTURES && textures_[i]; ++i) {
        textures_[i]->activate(0);

        D3DXHANDLE handle = effect_->GetParameterByName(NULL, texUniforms_[i].name);
        assert(handle);
        CHECKED_D3D_CALL(effect_->SetTexture(handle, textures_[i]->d3dObject()));
    }

    // uniforms
    for (unsigned i = 0; uniforms_[i].name; ++i) {
        D3DXHANDLE handle = effect_->GetParameterByName(NULL, uniforms_[i].name);
        assert(handle);
        effect_->SetValue(handle, uniforms_[i].value, D3DX_DEFAULT);
    }

	unsigned passes = 0;
	CHECKED_D3D_CALL(effect_->Begin(&passes, D3DXFX_DONOTSAVESTATE));
	CHECKED_D3D_CALL(effect_->BeginPass(0));

    return passes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectDX::next() {
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectDX::end() {
	assert(effect_);

	CHECKED_D3D_CALL(effect_->EndPass());
	CHECKED_D3D_CALL(effect_->End());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
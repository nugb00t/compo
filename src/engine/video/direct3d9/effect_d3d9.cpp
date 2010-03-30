#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "engine.h"	// TODO: pass video device
#include "effect_d3d9.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EffectD3D9::EffectD3D9(const Video::VertexDeclType vertexDecl)
: effect_(NULL), errors_(NULL), vertexDecl_(vertexDecl), uniforms_(&Uniform::TERMINATOR) {
	for (uint i = 0; i < MAX_TEXTURES; ++i)
		textures_[i].reset();

	HRESULT hr = D3DXCreateEffectFromFile(&Engine::inst().videoD3D9->device(), VideoD3D9::EFFECT_PATHS[vertexDecl], 0, 0, D3DXSHADER_DEBUG, 0, &effect_, &errors_);
	if (hr != D3D_OK)  {
		assert(errors_);

		const char* charBuffer = reinterpret_cast<const char*>(errors_->GetBufferPointer());
		MessageBoxA(0, charBuffer, NULL, 0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EffectD3D9::~EffectD3D9() {
	if (effect_)
		effect_->Release();

	if (errors_)
		errors_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectD3D9::setTexUniforms(const TextureUniform* const texUniforms) { 
    assert(texUniforms);

    texUniforms_ = texUniforms;

    uint i = 0;
    for (; i < MAX_TEXTURES; ++i) {
        if (!texUniforms_[i].name || !texUniforms_[i].path) {
            assert(!texUniforms_[i].name && !texUniforms_[i].path);
            break;
		} else if (!textures_[i] || textures_[i]->path() && _tcscmp(texUniforms_[i].path, textures_[i]->path())) {
            textures_[i].reset(new TextureD3D9(texUniforms_[i].path));
			CHECKED_CALL_A(textures_[i]->initialize());
		}
    }

    for (; i < MAX_TEXTURES; ++i)
        textures_[i].reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectD3D9::setTransform(const Matrix44& transform) {
    D3DXHANDLE handle = effect_->GetParameterByName(0, "TRANSFORM");
    assert(handle);
    CHECKED_D3D_CALL_A(effect_->SetMatrix(handle, transform.d3dMatrix()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint EffectD3D9::begin() {
	assert(effect_);
    assert(uniforms_);

	Engine::inst().video->activateVertexDecl(vertexDecl_);

	D3DXHANDLE techHandle = effect_->GetTechniqueByName("TransformTech");
	CHECKED_D3D_CALL(effect_->SetTechnique(techHandle));

    // textures
    for (uint i = 0; i < MAX_TEXTURES && textures_[i]; ++i) {
        textures_[i]->activate(0);

        D3DXHANDLE handle = effect_->GetParameterByName(NULL, texUniforms_[i].name);
        assert(handle);
        CHECKED_D3D_CALL(effect_->SetTexture(handle, textures_[i]->d3dObject()));
    }

    // uniforms
    for (uint i = 0; uniforms_[i].name; ++i) {
        D3DXHANDLE handle = effect_->GetParameterByName(NULL, uniforms_[i].name);
        assert(handle);
        effect_->SetValue(handle, uniforms_[i].value, D3DX_DEFAULT);
    }

	uint passes = 0;
	CHECKED_D3D_CALL(effect_->Begin(&passes, D3DXFX_DONOTSAVESTATE));
	CHECKED_D3D_CALL(effect_->BeginPass(0));

    return passes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectD3D9::next() {
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EffectD3D9::end() {
	assert(effect_);

	CHECKED_D3D_CALL_A(effect_->EndPass());
	CHECKED_D3D_CALL_A(effect_->End());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

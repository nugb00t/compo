#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "render_target_d3d9.h"
#include "tools_d3d9.h"

using namespace engine;

//---------------------------------------------------------------------------------------------------------------------

const RenderTargetD3D9::RenderVertex RenderTargetD3D9::VERTICES[] = {
	RenderVertex(Vector3(-(1601.f / 1600.f), -(1201.f / 1200.f), 0.f), Vector2(0.f, 1.f)),
	RenderVertex(Vector3(-(1601.f / 1600.f),  (1199.f / 1200.f), 0.f), Vector2(0.f, 0.f)),
	RenderVertex(Vector3( (1599.f / 1600.f),  (1199.f / 1200.f), 0.f), Vector2(1.f, 0.f)),
	RenderVertex(Vector3( (1599.f / 1600.f), -(1201.f / 1200.f), 0.f), Vector2(1.f, 1.f)),
};

const u16 RenderTargetD3D9::INDICES[] = {
	0, 1, 2,
	2, 3, 0
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderTargetD3D9::RenderTargetD3D9(IDirect3DDevice9* device, IDirect3DVertexDeclaration9* decl, ID3DXEffect* effect)
:	device_(device),
	decl_(decl),
	effect_(effect),
	target_(NULL),
	texture_(NULL),
	surface_(NULL),
	mesh_(device_, sizeof(RenderVertex), VERTICES, 4, INDICES, 6)
{
	CHECKED_D3D_CALL_A(D3DXCreateRenderToSurface(device_, 800, 600, D3DFMT_X8R8G8B8, TRUE, D3DFMT_D16, &target_));
	CHECKED_D3D_CALL_A(D3DXCreateTexture(device_, 800, 600, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture_));        
	CHECKED_D3D_CALL_A(texture_->GetSurfaceLevel(0, &surface_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RenderTargetD3D9::~RenderTargetD3D9() {
	safeRelease(surface_);
	safeRelease(texture_);
	safeRelease(target_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderTargetD3D9::begin() {
	CHECKED_D3D_CALL_A(target_->BeginScene(surface_, NULL));

	CHECKED_D3D_CALL_A(device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0));

	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE));
	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderTargetD3D9::end() {
	CHECKED_D3D_CALL_A(target_->EndScene(D3DX_FILTER_NONE));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderTargetD3D9::draw() {
	CHECKED_D3D_CALL_A(device_->SetVertexDeclaration(decl_));

	// technique
	D3DXHANDLE techHandle = effect_->GetTechniqueByName("TransformTech");
	assert(techHandle);
	CHECKED_D3D_CALL_A(effect_->SetTechnique(techHandle));

	// textures
	D3DXHANDLE texHandle = effect_->GetParameterByName(NULL, "TEX_DIFFUSE");
	assert(texHandle);
	CHECKED_D3D_CALL_A(effect_->SetTexture(texHandle, texture_));
	UINT numPasses = 0;
	CHECKED_D3D_CALL_A(effect_->Begin(&numPasses, 0));
	CHECKED_D3D_CALL_A(effect_->BeginPass(0));

	mesh_.streamBuffers();

	CHECKED_D3D_CALL_A(effect_->EndPass());
	CHECKED_D3D_CALL_A(effect_->End());	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "video_d3d9.h"

#include "engine.h"
#include "game.h"

// directx
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxerr.lib")
#ifndef _DEBUG
#pragma comment(lib, "d3dx9.lib")
#else
#pragma comment(lib, "d3dx9d.lib")
#endif

using namespace engine;

namespace {
	const D3DCOLOR CLEAR_COLOR = D3DCOLOR_XRGB(127, 127, 127);

	inline void safeRelease(IUnknown* unknown) {
		if (unknown) {
			unknown->Release();
			unknown = NULL;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------

const D3DVERTEXELEMENT9 VideoD3D9::VERTEX_DECL_ELEMS[VERTEX_DECL_COUNT][MAX_VERTEX_DECL_ELEMS] = {
	// stream, offset, type, method, usage, usage index

	{	// POS_DIFFUSE
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		D3DDECL_END()
	},

	{	// POS_DIFFUSE_TEX
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		{ 0, 16, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
		D3DDECL_END()
	},

	//{	// POS_NORMAL_TEX
	//	{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
	//	{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0},
	//	{ 0, 24, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
	//	D3DDECL_END()
	//},
};

//---------------------------------------------------------------------------------------------------------------------

const TCHAR* VideoD3D9::EFFECT_PATHS[VERTEX_DECL_COUNT] = {
	_T("main/fx/pos_diffuse.h"),
	_T("main/fx/pos_diffuse_tex.h"),
};

//---------------------------------------------------------------------------------------------------------------------

const Video::VertexType VideoD3D9::EFFECT_VERTEX_DECLS[EFFECT_COUNT] = {
	POS_DIFFUSE,
	POS_DIFFUSE_TEX,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoD3D9::VideoD3D9() :
	d3d_(NULL), 
	device_(NULL),
	renderTarget_(NULL),
	renderTexture_(NULL),
	renderSurface_(NULL),
	assets_(ASSET_POOL_SIZE)
{ 
	memset(&vertexDecls_[0], 0, sizeof(vertexDecls_)); 
	memset(&effects_[0], 0, sizeof(effects_)); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoD3D9::initialize() {
	d3d_ = ::Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d_) {
		TRACE_D3D_ERROR(D3D_OK, _T("::Direct3DCreate9(%d)"), D3D_SDK_VERSION);
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	::ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	const HWND handle = Engine::inst().window->handle();
	assert(handle);
	CHECKED_D3D_CALL(d3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_HARDWARE_VERTEXPROCESSING RELEASE_ONLY(| D3DCREATE_PUREDEVICE), &d3dpp, &device_));

	CHECKED_D3D_CALL(device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
	CHECKED_D3D_CALL(device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
	CHECKED_D3D_CALL(device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));

	// render target
	CHECKED_D3D_CALL(D3DXCreateRenderToSurface(device_, 800, 600, D3DFMT_X8R8G8B8, TRUE, D3DFMT_D16, &renderTarget_));
	CHECKED_D3D_CALL(D3DXCreateTexture(device_, 800, 600, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &renderTexture_));        
	CHECKED_D3D_CALL(renderTexture_->GetSurfaceLevel(0, &renderSurface_));

	static const PosDiffuseTex quadVertices[] = {
		PosDiffuseTex(Vector3(-.5f, -.5f, 0.f), 0xffffffff, Vector2(0.f, 1.f)),
		PosDiffuseTex(Vector3(-.5f,  .5f, 0.f), 0xffffffff, Vector2(0.f, 0.f)),
		PosDiffuseTex(Vector3( .5f,  .5f, 0.f), 0xffffffff, Vector2(1.f, 0.f)),
		PosDiffuseTex(Vector3( .5f, -.5f, 0.f), 0xffffffff, Vector2(1.f, 1.f)),
	};
	static const u16 quadIndices[] = {
		0, 1, 2,
		2, 3, 0
	};
	renderMesh_.reset(new StaticMeshD3D9(device_, sizeof(PosDiffuseTex), quadVertices, 4, quadIndices, 6));

	// vertex decls
	for (uint i = 0; i < VERTEX_DECL_COUNT; ++i)
		CHECKED_D3D_CALL(device_->CreateVertexDeclaration(VERTEX_DECL_ELEMS[i], &vertexDecls_[i]));

	// effects
	for (uint i = 0; i < EFFECT_COUNT; ++i) {
		ID3DXBuffer* errors = NULL;

		const HRESULT hr = D3DXCreateEffectFromFile(device_, VideoD3D9::EFFECT_PATHS[i], 0, 0, D3DXSHADER_DEBUG, 0, &effects_[i], &errors);
		if (hr != D3D_OK)  {
			assert(errors);

			const char* charBuffer = reinterpret_cast<const char*>(errors->GetBufferPointer());
			errors->Release();

			MessageBoxA(0, charBuffer, NULL, 0);
			return false;
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::terminate() {
	for (uint i = 0; i < EFFECT_COUNT; ++i)
		safeRelease(effects_[i]);

	for (uint i = 0; i < VERTEX_DECL_COUNT; ++i)
		safeRelease(vertexDecls_[i]);

	renderMesh_.reset();
	safeRelease(renderSurface_);
	safeRelease(renderTexture_);
	safeRelease(renderTarget_);

	safeRelease(device_);
	safeRelease(d3d_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::begin() {
	assets_.update(device_);

	CHECKED_D3D_CALL_A(renderTarget_->BeginScene(renderSurface_, NULL));

	CHECKED_D3D_CALL_A(device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0));

	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE));
	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::end() {
	CHECKED_D3D_CALL_A(renderTarget_->EndScene(D3DX_FILTER_NONE));

	CHECKED_D3D_CALL_A(device_->BeginScene());

	CHECKED_D3D_CALL_A(device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0));

	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE));
	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE));
	CHECKED_D3D_CALL_A(device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO));

	ID3DXEffect* effect = effects_[DIFFUSE_TEXTURED];
	D3DXHANDLE handle = effect->GetParameterByName(NULL, "TEX_DIFFUSE");
	assert(handle);
	CHECKED_D3D_CALL_A(effect->SetTexture(handle, renderTexture_));
	UINT numPasses = 0;
	CHECKED_D3D_CALL_A(effect->Begin(&numPasses, 0));
	CHECKED_D3D_CALL_A(effect->BeginPass(0));

	renderMesh_->streamBuffers();
	//CHECKED_D3D_CALL_A(device_->SetStreamSource(0, mRadarVB, 0, sizeof(VertexPT)));
	//CHECKED_D3D_CALL_A(device_->SetVertexDeclaration (VertexPT::Decl));
	//CHECKED_D3D_CALL_A(device_->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2));

	CHECKED_D3D_CALL_A(effect->EndPass());
	CHECKED_D3D_CALL_A(effect->End());	

	CHECKED_D3D_CALL_A(device_->EndScene());
	CHECKED_D3D_CALL_A(device_->Present(NULL, NULL, NULL, NULL));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::draw(Mesh& mesh, const VertexType vertexType, const EffectType effectType,
					 const TextureUniform* const texUniforms, const uint textureCount,
					 //const void* const uniforms, const uint uniformCount,
					 const Matrix44& transform) 
{
	ID3DXEffect* const effect = effects_[effectType];

	// set transform
	D3DXHANDLE handle = effect->GetParameterByName(0, "TRANSFORM");
	assert(handle);
	CHECKED_D3D_CALL_A(effect->SetMatrix(handle, transform.d3dMatrix()));

	// vertex type
	CHECKED_D3D_CALL_A(device_->SetVertexDeclaration(vertexDecls_[vertexType]));

	// technique
	D3DXHANDLE techHandle = effect->GetTechniqueByName("TransformTech");
	assert(techHandle);
	CHECKED_D3D_CALL_A(effect->SetTechnique(techHandle));

	// textures
	for (uint i = 0; i < textureCount; ++i) {
		IDirect3DTexture9* const texture = assets_.getTexture(texUniforms[i].texture);
		if (!texture)
			continue;

		//CHECKED_D3D_CALL_A(device->SetTexture(stage, texture));

		D3DXHANDLE handle = effect->GetParameterByName(NULL, texUniforms[i].name);
		assert(handle);
		CHECKED_D3D_CALL_A(effect->SetTexture(handle, texture));
	}

	// uniforms
	//for (uint i = 0; uniforms_[i].name; ++i) {
	//	D3DXHANDLE handle = effect->GetParameterByName(NULL, uniforms_[i].name);
	//	assert(handle);
	//	effect->SetValue(handle, uniforms_[i].value, D3DX_DEFAULT);
	//}

	uint passes = 0;
	CHECKED_D3D_CALL_A(effect->Begin(&passes, D3DXFX_DONOTSAVESTATE));
	CHECKED_D3D_CALL_A(effect->BeginPass(0));

    mesh.streamBuffers();

	CHECKED_D3D_CALL_A(effect->EndPass());
	CHECKED_D3D_CALL_A(effect->End());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StaticMesh* VideoD3D9::createStaticMesh(const uint vertexSize, const void* const vertices, const uint vertexCount, const u16* const indices, const uint indexCount) {
	return new StaticMeshD3D9(device_, vertexSize, vertices, vertexCount, indices, indexCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicMesh* VideoD3D9::createDynamicMesh(const uint vertexSize, const uint vertexCapacity, const uint indexCapacity) {
	return new DynamicMeshD3D9(device_, vertexSize, vertexCapacity, indexCapacity);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "video_d3d9.h"

#include "engine.h"
#include "game.h"

// factory-created objects
#include "effect_d3d9.h"
#include "texture_d3d9.h"

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

const Video::VertexDeclType VideoD3D9::EFFECT_VERTEX_DECLS[EFFECT_COUNT] = {
	POS_DIFFUSE,
	POS_DIFFUSE_TEX,
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoD3D9::VideoD3D9() : d3d_(NULL), device_(NULL) { 
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

	for (uint i = 0; i < VERTEX_DECL_COUNT; ++i)
		CHECKED_D3D_CALL(Engine::inst().videoD3D9->device().CreateVertexDeclaration(VERTEX_DECL_ELEMS[i], &vertexDecls_[i]));

	for (uint i = 0; i < EFFECT_COUNT; ++i) {
		ID3DXBuffer* errors = NULL;

		const HRESULT hr = D3DXCreateEffectFromFile(&Engine::inst().videoD3D9->device(), VideoD3D9::EFFECT_PATHS[i], 0, 0, D3DXSHADER_DEBUG, 0, &effects_[i], &errors);
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
		if (effects_[i]) {
			effects_[i]->Release();
			effects_[i] = NULL;
		}

	for (uint i = 0; i < VERTEX_DECL_COUNT; ++i)
		if (vertexDecls_[i]) {
			vertexDecls_[i]->Release();
			vertexDecls_[i] = NULL;
		}

	if (device_) {
		device_->Release();
		device_ = NULL;
	}

	if (d3d_) {
		d3d_->Release();
		d3d_ = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::clear() {
	device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoD3D9::begin() {
	return SUCCEEDED(device_->BeginScene());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::end() {
	device_->EndScene();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::present() {
	device_->Present(NULL, NULL, NULL, NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Texture* VideoD3D9::createTexture(const TCHAR* const path) {
	Texture* tex = new TextureD3D9(path);
	if (tex->initialize())
		return tex;
	else {
		delete tex;
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Effect* VideoD3D9::createEffect(const EffectType type) {
	assert(0 <= type && type < EFFECT_COUNT);

	return new EffectD3D9(*effects_[type], EFFECT_VERTEX_DECLS[type]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::activateVertexDecl(const Video::VertexDeclType type) {
	assert(0 <= type && type < VERTEX_DECL_COUNT);

	CHECKED_D3D_CALL_A(device_->SetVertexDeclaration(vertexDecls_[type]));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
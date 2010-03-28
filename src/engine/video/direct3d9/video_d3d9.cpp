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
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const bool VideoD3D9::Device::initialize() {
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
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // D3DPRESENT_INTERVAL_ONE; // 

	const HWND handle = Engine::inst().window->handle();
	assert(handle);
	CHECKED_D3D_CALL(d3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, handle, D3DCREATE_HARDWARE_VERTEXPROCESSING RELEASE_ONLY(| D3DCREATE_PUREDEVICE), &d3dpp, &device_));

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoD3D9::Device::~Device() {
	if (d3d_)
		d3d_->Release();

	if (device_)
		device_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoD3D9::initialize() {
	return device_.initialize() && vertexDecls_.initialize();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::clear() {
	device_.get()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoD3D9::begin() {
	return SUCCEEDED(device_.get()->BeginScene());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::end() {
	device_.get()->EndScene();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::present() {
	device_.get()->Present(NULL, NULL, NULL, NULL);
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

#endif
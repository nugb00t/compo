#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "video_d3d9.h"

#include "window/window_interface.h"

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

VideoD3D9::VideoD3D9()
: d3d_(NULL), device_(NULL) {
	VideoDX::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoD3D9::~VideoD3D9() {
	shutdown();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoD3D9::shutdown() {
	if (d3d_) {
		d3d_->Release();
		d3d_ = 0;
	}

	if (device_) {
		device_->Release();
		device_ = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoD3D9::startup() {
	d3d_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d_)
		return false;

	D3DPRESENT_PARAMETERS d3dpp;
	::ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	return SUCCEEDED(d3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::inst().handle(), D3DCREATE_HARDWARE_VERTEXPROCESSING RELEASE_ONLY(& D3DCREATE_PUREDEVICE), &d3dpp, &device_));
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

#endif
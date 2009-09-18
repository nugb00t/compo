#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "video_system_dx.h"

#include "utility/registry.h"
#include "window/window_system.h"

// directx
#pragma comment(lib, "d3d9.lib")
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

VideoSystemDX::VideoSystemDX()
: d3d_(NULL), device_(NULL) {
	VideoDX::set(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VideoSystemDX::~VideoSystemDX() {
	shutdown();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoSystemDX::init() {
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_ZENABLE, TRUE));
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
	CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_LIGHTING, FALSE));
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(255, 0, 0, 22)));
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD));
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_COLOR1));

	// texture filtering
	CHECKED_D3D_CALL(device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
	CHECKED_D3D_CALL(device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
	CHECKED_D3D_CALL(device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));

	// alpha blending
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE));
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	//CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::shutdown() {
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

bool VideoSystemDX::startup() {
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

	if (FAILED(d3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::inst().handle(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_)))
		return false;

	return init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::clear() {
	device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoSystemDX::begin() {
	return SUCCEEDED(device_->BeginScene());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::end() {
	device_->EndScene();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::present() {
	device_->Present(NULL, NULL, NULL, NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "video_system_dx.h"

#include "utility/registry.h"
#include "window/window_system.h"
#include "video/video_component.h"

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
	CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_LIGHTING, TRUE));
	CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(255, 0, 0, 22)));
	CHECKED_D3D_CALL(device_->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD));

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::operator()() {
	if (Window::get().create(800, 600, 32, 0, false) && startup()) {
		while (true) {
			// TODO: valid dt here?
			if (!Window::get().update(0))
				break;

			update(0);
		}
	}

	shutdown();
	Window::get().destroy();
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

	if (FAILED(d3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::get().handle(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device_)))
		return false;

	camera_ = createCamera();
	assert(camera_);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoSystemDX::update(const float dt) {
	device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0);

	if (SUCCEEDED(device_->BeginScene())) {
		camera_->update(dt);

		// TODO: correct dt
		Registry<VideoComponent>::update(/* correct dt */ 0);

		device_->EndScene();
	}

	device_->Present(NULL, NULL, NULL, NULL);
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
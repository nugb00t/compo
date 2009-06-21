#include "stdafx.h"

#ifdef VIDEO_DIRECTX

#include "utility/registry.h"
#include "window/window_system.h"
#include "video/video_component.h"
#include "video/mesh.h"

#include "video_system_dx.h"

// directx
#pragma comment(lib, "d3d9.lib")
#ifndef _DEBUG
#pragma comment(lib, "d3dx9.lib")
#else
#pragma comment(lib, "d3dx9d.lib")
#endif

using namespace engine;

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

void VideoSystemDX::draw(const Mesh& /*mesh*/) {
	// TODO: implement
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::drawTest() {
	// TODO: implement
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool VideoSystemDX::init() {
	// TODO: implement
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::operator()() {
	if (Window::get().create(800, 600, 32, 0, false) &&
		startup() &&
		init())
	{
		while (true) {
			// TODO: valid dt here?
			if (!Window::get().update(0))
				break;

			update();
		}
	}

	shutdown();
	Window::get().destroy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::reshape(const unsigned /*width*/, const unsigned /*height*/) {
	// TODO: implement
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::setOrthogonalView() {
	// TODO: implement
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

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VideoSystemDX::update() {
	device_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(device_->BeginScene())) {
		// TODO: correct dt
		Registry<VideoComponent>::update(/* correct dt */ 0);

		// tmp
		Video::get().drawTest();
		// tmp

		device_->EndScene();
	}

	device_->Present(NULL, NULL, NULL, NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
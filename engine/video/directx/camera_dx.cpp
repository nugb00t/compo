#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "camera_dx.h"

#include "video_system_dx.h"

using namespace engine;

namespace {
	const float FOV = D3DX_PI / 3;
	const float ASPECT = 4.0f / 3.0f;
	const float Z_NEAR = 1.0f;
	const float Z_FAR = 500.0f;

	const D3DXVECTOR3 CAMERA_POS	= D3DXVECTOR3(0.0f, 25.0f, 50.0f);
	const D3DXVECTOR3 CAMERA_LOOKAT	= D3DXVECTOR3(0.0f,  0.0f,  0.0f);
	const D3DXVECTOR3 CAMERA_UP		= D3DXVECTOR3(0.0f,  1.0f,  0.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CameraDX::CameraDX()
:	pos_(CAMERA_POS),
	lookAt_(CAMERA_LOOKAT),
	up_(CAMERA_UP),
	fov_(FOV),
	aspect_(ASPECT)
		 {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CameraDX::update(const float /*dt*/) {
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view, &pos_, &lookAt_, &up_);

	CHECKED_D3D_CALL(VideoDX::get().device().SetTransform(D3DTS_VIEW, &view));

	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection, fov_, aspect_, Z_NEAR, Z_FAR);

	CHECKED_D3D_CALL(VideoDX::get().device().SetTransform(D3DTS_PROJECTION, &projection));

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
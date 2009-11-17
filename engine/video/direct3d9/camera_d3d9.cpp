#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "camera_d3d9.h"

#include "video_d3d9.h"

using namespace engine;

namespace {
	const float FOV = D3DX_PI / 3;
	const float ASPECT = 4.0f / 3.0f;
	const float Z_NEAR = 1.0f;
	const float Z_FAR = 500.0f;

	const D3DXVECTOR3 CAMERA_POS	= D3DXVECTOR3(0.0f,  0.0f, 10.0f);
	const D3DXVECTOR3 CAMERA_LOOKAT	= D3DXVECTOR3(0.0f,  0.0f,  0.0f);
	const D3DXVECTOR3 CAMERA_UP		= D3DXVECTOR3(0.0f, -1.0f,  0.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CameraD3D9::CameraD3D9()
:	pos_(CAMERA_POS),
	lookAt_(CAMERA_LOOKAT),
	up_(CAMERA_UP),
	fov_(FOV),
	aspect_(ASPECT)
		 {
			 view_projection_.identity();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CameraD3D9::update(const unsigned UNUSED(msec)) {
	D3DXMatrixLookAtLH(view_projection_.d3dMatrix(), &pos_, &lookAt_, &up_);

	Matrix44 projection;
	D3DXMatrixPerspectiveFovLH(projection.d3dMatrix(), fov_, aspect_, Z_NEAR, Z_FAR);
	//D3DXMatrixOrthoLH();

	view_projection_ *= projection;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const Matrix44& CameraD3D9::view_projection() const {
	return view_projection_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
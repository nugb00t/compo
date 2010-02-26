#pragma once

#include "video/camera.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ProjectionCameraD3D9 : public ProjCamera {
public:
	ProjectionCameraD3D9();

	// interface: Updatable
	virtual void update();

	// interface: ProjCamera
	virtual const Matrix44& view_projection() const { return view_projection_; }

private:
	// view
	D3DXVECTOR3 pos_;
	D3DXVECTOR3 lookAt_;
	D3DXVECTOR3 up_;

	// projection
	float fov_;
	float aspect_;

	Matrix44 view_projection_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrthoCameraD3D9 : public OrthoCamera {
public:
	OrthoCameraD3D9();

	// interface: Updatable
	virtual void update();

	// interface: OrthoCamera
	virtual const Matrix44& view_projection() const { return view_projection_; }

private:
	// view
	D3DXVECTOR3 pos_;
	D3DXVECTOR3 lookAt_;
	D3DXVECTOR3 up_;

	// projection
	float width_;
	float height_;

	Matrix44 view_projection_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

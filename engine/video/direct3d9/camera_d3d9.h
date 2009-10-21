#ifndef CAMERA_D3D9_INCLUDED
#define CAMERA_D3D9_INCLUDED

#include "video/camera.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CameraD3D9 : public Camera {
public:
	CameraD3D9();

	// interface: Updatable
	virtual void update(const unsigned msec);

	// interface: Camera
	virtual const Matrix44& view_projection() const;

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

} // namespace engine

#endif
#ifndef CAMERA_DX_INCLUDED
#define CAMERA_DX_INCLUDED

#include "video/camera.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CameraDX : public Camera {
public:
	CameraDX();

	// interface: Updatable
	virtual void update(const float dt);

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
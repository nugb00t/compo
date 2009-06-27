#ifndef CAMERA_DX_INCLUDED
#define CAMERA_DX_INCLUDED

#include "video/camera.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CameraDX : public Camera {
public:
	CameraDX();

	// interface: Updatable
	virtual bool update(const float dt);

private:
	D3DXVECTOR3 pos_;
	D3DXVECTOR3 lookAt_;
	D3DXVECTOR3 up_;

	float fov_;
	float aspect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
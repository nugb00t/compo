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
	D3DXMATRIX view_;

	D3DXVECTOR3 pos_;
	D3DXVECTOR3 lookAt_;
	D3DXVECTOR3 up_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
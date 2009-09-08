#ifndef MESH_INCLUDED
#define MESH_INCLUDED

#include "utility/intrusive_ptr_base.h"
#include "drawable.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Mesh : public IntrusivePtrBase, public Drawable {
public:
	virtual void setTransformRect(const float left, const float top, const float right, const float bottom, const float depth);
};

typedef boost::intrusive_ptr<Mesh> MeshPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
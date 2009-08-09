#ifndef DRAWABLE_INCLUDED
#define DRAWABLE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Drawable {
public:
	virtual bool draw(const Vector3& position, const Vector3& rotation, const Vector3& scale) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

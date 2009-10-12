#ifndef ENGINE_TYPES_INCLUDED
#define ENGINE_TYPES_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Callable {
public:
	virtual void operator()() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//class Transformable {
//public:
//	virtual Matrix44& transform()	{	return transform_;	}
//	virtual const Matrix44& transform() const	{	return transform_;	}
//
//protected:
//	Matrix44 transform_;
//};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Drawn {
public:
	virtual void draw(const Matrix44& transform) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity {
public:
    struct Params {
        Matrix44 transform;
    };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Updatable {
public:
	virtual void update(const float dt) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

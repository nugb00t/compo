#ifndef ENGINE_MATH_INCLUDED
#define ENGINE_MATH_INCLUDED

#include <cml/cml.h>

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef cml::constantsf constants;

typedef cml::vector2f Vector2;
typedef cml::vector3f Vector3;
typedef cml::vector4f Vector4;
typedef cml::quaternionf_n Quaternion;
typedef cml::matrix44f_r Matrix44;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline Matrix44 transformFromVectors(const Vector3 position, const Vector3 rotation, const Vector3 scale) {
	Matrix44 transform;
	transform.identity();

	cml::matrix_rotation_euler(transform, rotation[0], rotation[1], rotation[2], cml::euler_order_xyz);
	cml::matrix_set_translation(transform, position[0], position[1], position[2]);

	Matrix44 s;
	cml::matrix_scale(s, scale[0], scale[1], scale[2]);

	return s * transform; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline Matrix44 transformFromRect(const float left, const float top, const float right, const float bottom, const float depth) {
	return transformFromVectors(
		Vector3((left + right) / 2.f, (top + bottom) / 2.f, depth),
		Vector3(0.f, 0.f, 0.f),
		Vector3(abs(right - left), abs(top - bottom), 0.f));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif

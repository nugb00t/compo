#include "stdafx.h"

#include "mesh.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Mesh::setTransformRect(const float left, const float top, const float right, const float bottom, const float depth) {
	return setTransform(
		Vector3((left + right) / 2.f, (top + bottom) / 2.f, depth),
		Vector3(0.f, 0.f, 0.f),
		Vector3(abs(right - left), abs(top - bottom), 0.f));
}
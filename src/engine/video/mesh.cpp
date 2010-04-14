#include "stdafx.h"

#include "mesh.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DynamicMesh::BufferAccess::setBuffers(const void* vertices, const u16 vertexCount, const u16* indices, const uint indexCount) {
    assert(mesh_.vertices_ && mesh_.indices_ && vertices && vertexCount && indices && indexCount);
    assert(vertexCount <= mesh_.vertexCapacity_ && indexCount <= mesh_.indexCapacity_);

    memcpy(mesh_.vertices_, vertices, vertexCount * mesh_.vertexSize_);
    memcpy(mesh_.indices_, indices, indexCount * sizeof(u16));

    mesh_.vertexCount_ = vertexCount;
    mesh_.indexCount_ = indexCount;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

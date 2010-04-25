#pragma once

#ifdef VIDEO_DIRECT3D9

#include "../mesh.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StaticMeshD3D9 : public StaticMesh {
public:
	StaticMeshD3D9(IDirect3DDevice9* device, const uint vertexSize, const void* const vertices, const uint vertexCount, const u16* const indices, const uint indexCount);
	virtual ~StaticMeshD3D9();

	virtual void streamBuffers(const uint vertexCount = 0, const uint primCount = 0);

protected:
	IDirect3DDevice9* device_;

	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicMeshD3D9 : public DynamicMesh {
public:
    DynamicMeshD3D9(IDirect3DDevice9* device, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity);
    ~DynamicMeshD3D9();

	// interface: DynamicMesh
	virtual void streamBuffers(const uint vertexCount = 0, const uint primCount = 0);

protected:
	virtual void* vertices();
	virtual u16* indices();

	virtual void unlock();

protected:
	IDirect3DDevice9* device_;

	IDirect3DVertexBuffer9* vertexBuffer_;
	IDirect3DIndexBuffer9* indexBuffer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif

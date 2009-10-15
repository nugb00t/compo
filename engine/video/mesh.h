#ifndef MESH_INCLUDED
#define MESH_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Mesh : public IntrusivePtrBase, public Drawn {
public:
	virtual void setBuffers(const void* const vertices, const unsigned verticesSize, const unsigned vertexSize, 
							const short* const indices, const unsigned indicesSize) = 0;
};

typedef boost::intrusive_ptr<Mesh> MeshPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
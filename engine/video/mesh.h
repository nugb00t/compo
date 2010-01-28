#ifndef MESH_INCLUDED
#define MESH_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Mesh : public Drawn {
private:
    Mesh();

public:
	virtual void load(const void* const vertices, const unsigned vertexCount, 
                            const short* const indices, const unsigned indexCount) = 0;
};

typedef boost::intrusive_ptr<Mesh> MeshPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
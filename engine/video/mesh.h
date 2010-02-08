#ifndef MESH_INCLUDED
#define MESH_INCLUDED

#include "video/effect.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MeshImpl {
public:
    virtual ~MeshImpl() {}

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicMesh : public Drawn {
public:

    //-----------------------------------------------------------------------------------------------------------------

    class BufferAccess {
    public:
        BufferAccess(DynamicMesh& mesh) : mesh_(mesh) { mesh_.lock(); }

        ~BufferAccess() { mesh_.unlock(); }

        template <class TVertex> inline u16 appendVertex(const TVertex& vertex);
        inline void appendIndex(const u16 index);
        void setBuffers(const void* vertices, const u16 vertexCount, const u16* indices, const uint indexCount);

    private:
        DynamicMesh& mesh_;
    };

    //-----------------------------------------------------------------------------------------------------------------

protected:
    DynamicMesh(engine::Effect* effect, const uint vertexSize, const uint vertexCapacity, const uint indexCapacity) 
        : effect_(effect), vertexSize_(vertexSize), vertexCapacity_(vertexCapacity), indexCapacity_(indexCapacity), vertexCount_(0), indexCount_(0) {}

public:
    // interface: Drawn
    void draw(const Matrix44& transform);

    // interface: own
    virtual void lock() = 0;
    virtual void unlock() = 0;

    virtual void streamBuffers(const uint vertexCount, const uint primCount) = 0;

    void clear() { vertexCount_ = 0; indexCount_ = 0; }

protected:
    engine::Effect* const effect_;

    const uint vertexSize_;
    const uint vertexCapacity_;
    const uint indexCapacity_;

    // state vars
    void* vertices_;
    u16* indices_;

    u16 vertexCount_;
    uint indexCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TVertex>
inline u16 DynamicMesh::BufferAccess::appendVertex(const TVertex& vertex) {
    assert(mesh_.vertices_);
    assert(sizeof(TVertex) == mesh_.vertexSize_ && mesh_.vertexCount_ < mesh_.vertexCapacity_);

    reinterpret_cast<TVertex*>(mesh_.vertices_)[mesh_.vertexCount_] = vertex;
    return mesh_.vertexCount_++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DynamicMesh::BufferAccess::appendIndex(const u16 index) {
    assert(mesh_.indices_);
    assert(mesh_.indexCount_ < mesh_.indexCapacity_);

    mesh_.indices_[mesh_.indexCount_++] = index;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
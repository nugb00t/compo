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
        BufferAccess(DynamicMesh& mesh)
            : mesh_(mesh) 
        {
            mesh_.lock();
        }

        ~BufferAccess() {
            mesh_.unlock();
        }

        void reset() {
            mesh_.vertexCount_ = 0;
            mesh_.indexCount_ = 0;
        }

        template <class TVertex>
        inline unsigned short appendVertex(const TVertex& vertex) {
            assert(mesh_.vertices_);
            assert(sizeof(TVertex) == mesh_.vertexSize_ && mesh_.vertexCount_ < mesh_.vertexCapacity_);

            reinterpret_cast<TVertex*>(mesh_.vertices_)[mesh_.vertexCount_] = vertex;
            return mesh_.vertexCount_++;
        }

        inline void appendIndex(const unsigned short index) {
            assert(mesh_.indices_);
            assert(mesh_.indexCount_ < mesh_.indexCapacity_);

            mesh_.indices_[mesh_.indexCount_++] = index;
        }

        inline void setBuffers(const void* vertices, const unsigned short vertexCount, const unsigned short* indices, const unsigned indexCount) {
            assert(mesh_.vertices_ && mesh_.indices_ && vertices && vertexCount && indices && indexCount);
            assert(vertexCount <= mesh_.vertexCapacity_ && indexCount <= mesh_.indexCapacity_);

            memcpy(mesh_.vertices_, vertices, vertexCount * mesh_.vertexSize_);
            memcpy(mesh_.indices_, indices, indexCount * sizeof(unsigned short));

            mesh_.vertexCount_ = vertexCount;
            mesh_.indexCount_ = indexCount;
        }

    private:
        DynamicMesh& mesh_;
    };

    //-----------------------------------------------------------------------------------------------------------------

protected:
    DynamicMesh(engine::Effect* effect, const unsigned vertexSize, const unsigned vertexCapacity, const unsigned indexCapacity) 
        : effect_(effect), vertexSize_(vertexSize), vertexCapacity_(vertexCapacity), indexCapacity_(indexCapacity), vertexCount_(0), indexCount_(0) {}

public:
    // interface: Drawn
    void draw(const Matrix44& transform);

    // interface: own
    virtual void lock() = 0;
    virtual void unlock() = 0;

    virtual void streamBuffers(const unsigned vertexCount, const unsigned primCount) = 0;

protected:
    engine::Effect* const effect_;

    const unsigned vertexSize_;
    const unsigned vertexCapacity_;
    const unsigned indexCapacity_;

    // state vars
    void* vertices_;
    unsigned short* indices_;

    unsigned short vertexCount_;
    unsigned indexCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
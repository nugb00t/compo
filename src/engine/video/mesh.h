#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Mesh {
public:
	// interface: own
	virtual void streamBuffers(const uint vertexCount = 0, const uint primCount = 0) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StaticMesh : public Mesh {
public:
	StaticMesh(const uint vertexSize, const uint vertexCount, const uint indexCount) 
		: vertexSize_(vertexSize), vertexCount_(vertexCount), indexCount_(indexCount) {
			assert(vertexSize && vertexCount && indexCount);
	}
	virtual ~StaticMesh() {}

protected:
	const uint vertexSize_;
	const uint vertexCount_;
	const uint indexCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DynamicMesh : public Mesh {
public:

    //-----------------------------------------------------------------------------------------------------------------

    class BufferAccess {
    public:
		BufferAccess(DynamicMesh& mesh) : mesh_(mesh), vertices_(mesh.vertices()), indices_(mesh.indices()) {
			assert(vertices_ && indices_);
		}
        ~BufferAccess() { mesh_.unlock(); }

        template <class TVertex> inline u16 addVertex(const TVertex& vertex);
        inline void addIndex(const u16 index);

    private:
        DynamicMesh& mesh_;

		void* vertices_;
		u16* indices_;
	};

    //-----------------------------------------------------------------------------------------------------------------

public:
    DynamicMesh(const uint vertexSize, const uint vertexCapacity, const uint indexCapacity) 
        : vertexSize_(vertexSize), vertexCapacity_(vertexCapacity), indexCapacity_(indexCapacity), vertexCount_(0), indexCount_(0) {}
	virtual ~DynamicMesh() {}

    // interface: own
	void clear() { vertexCount_ = 0; indexCount_ = 0; }

protected:
	virtual void* vertices() = 0;
	virtual u16* indices() = 0;

	virtual void unlock() = 0;

protected:
	const uint vertexSize_;
	const uint vertexCapacity_;
	const uint indexCapacity_;

	u16 vertexCount_;
    uint indexCount_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TVertex>
inline u16 DynamicMesh::BufferAccess::addVertex(const TVertex& vertex) {
    assert(vertices_ && sizeof(TVertex) == mesh_.vertexSize_ && mesh_.vertexCount_ < mesh_.vertexCapacity_);

    reinterpret_cast<TVertex*>(vertices_)[mesh_.vertexCount_] = vertex;
    return mesh_.vertexCount_++;
}

//---------------------------------------------------------------------------------------------------------------------

inline void DynamicMesh::BufferAccess::addIndex(const u16 index) {
    assert(indices_ && mesh_.indexCount_ < mesh_.indexCapacity_);

    indices_[mesh_.indexCount_++] = index;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

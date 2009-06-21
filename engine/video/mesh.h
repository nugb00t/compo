#ifndef MESH_INCLUDED
#define MESH_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(push, 4)
	struct Vertice {
		Vector3	point;
		Vector3	normal;
		Vector2	uv;

		inline Vertice(const Vector3 point_ = Vector3(0.f, 0.f, 0.f), const Vector3 normal_ = Vector3(0.f, 0.f, 1.f), const Vector2 uv_ = Vector2(0.f, 0.f))
			: point(point_), normal(normal_), uv(uv_) {}
	};
	inline const bool operator ==(const Vertice& left, const Vertice& right) {	return left.point == right.point && left.normal == right.normal && left.uv == right.uv;	}
#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Mesh /*: public kaynine::Serializable*/ {
public:
	typedef std::vector<Vertice> Vertices;
	typedef std::vector<unsigned> Indices;

public:
	Mesh(const unsigned verticeCount = 4, const unsigned indexCount = 4);

	inline void addIndex(const unsigned index)			{ indices_.push_back(index); }
	inline unsigned addVertice(const Vertice& vertice)	{ vertices_.push_back(vertice); return vertices_.size() - 1; }

	inline void clear()									{ vertices_.clear(); indices_.clear(); } 

	inline const unsigned* indices() const				{ assert(indices_.size()); return &(indices_[0]); }
	inline const unsigned indexCount() const			{ return indices_.size(); }

	inline const Vertice* vertices() const				{ assert(vertices_.size()); return &(vertices_[0]); }
	inline const unsigned verticeCount() const			{ return vertices_.size(); }

	unsigned optimize();

	// kaynine::Serializable
	//bool serializeWith(kaynine::Archive& archive);

private:
	Mesh& operator= (const Mesh& /*original*/);

private:
	Vertices		vertices_;
	Indices			indices_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
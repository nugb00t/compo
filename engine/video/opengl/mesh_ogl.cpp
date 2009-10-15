#include "stdafx.h"

#ifdef VIDEO_OPENGL

#include "video_interface.h"

#include "mesh.h"


using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh(const unsigned verticeCount, const unsigned indexCount) {
	vertices_.reserve(verticeCount);
	indices_.reserve(indexCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned Mesh::optimize() {
	unsigned removed = 0;

	for (unsigned iwalkvertex = 0; iwalkvertex < vertices_.size() - 1; ++iwalkvertex)
		for (unsigned itestvertex = iwalkvertex + 1; itestvertex < vertices_.size(); ++itestvertex) 
			if (vertices_[iwalkvertex] == vertices_[itestvertex]) 
			{
				vertices_.erase(vertices_.begin() + itestvertex);

				for (unsigned iindex = 0; iindex < indices_.size(); ++iindex) {
					if (indices_[iindex] == itestvertex)
						indices_[iindex] = iwalkvertex;

					if (indices_[iindex] > itestvertex)
						--indices_[iindex];
				}

				++removed;
			}

	return removed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//bool Mesh::serializeWith(kaynine::Archive& archive) {
//	return archive.serializeAsInt(type_) &&
//		archive.serializePODSequence(vertices_) &&
//		archive.serializePODSequence(indices_);
//
//	return true;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

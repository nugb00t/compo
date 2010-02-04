#include "stdafx.h"

#ifdef VIDEO_OPENGL

#include "video_interface.h"

#include "mesh.h"


using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicMesh::DynamicMesh(const uint verticeCount, const uint indexCount) {
	vertices_.reserve(verticeCount);
	indices_.reserve(indexCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint DynamicMesh::optimize() {
	uint removed = 0;

	for (uint iwalkvertex = 0; iwalkvertex < vertices_.size() - 1; ++iwalkvertex)
		for (uint itestvertex = iwalkvertex + 1; itestvertex < vertices_.size(); ++itestvertex) 
			if (vertices_[iwalkvertex] == vertices_[itestvertex]) 
			{
				vertices_.erase(vertices_.begin() + itestvertex);

				for (uint iindex = 0; iindex < indices_.size(); ++iindex) {
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

//bool DynamicMesh::serializeWith(kaynine::Archive& archive) {
//	return archive.serializeAsInt(type_) &&
//		archive.serializePODSequence(vertices_) &&
//		archive.serializePODSequence(indices_);
//
//	return true;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

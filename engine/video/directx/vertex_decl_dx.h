#ifndef VERTEX_DX_INCLUDED
#define VERTEX_DX_INCLUDED

#include "video/vertex_decl.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VertexDeclDX : public VertexDecl {
	static const unsigned MAX_ELEMENTS = 8;

public:
	static VertexDeclPtr get(const Type type);

private:
	VertexDeclDX(const Type type);

public:
	~VertexDeclDX();

	virtual void activate(); 

private:
	static const D3DVERTEXELEMENT9 ELEMENTS[Type_COUNT][MAX_ELEMENTS];

	static VertexDeclPtr vertexDecls_[Type_COUNT];

	// Direct3D
	IDirect3DVertexDeclaration9* vertexDecl_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

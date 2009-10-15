#ifndef VERTEX_D3D9_INCLUDED
#define VERTEX_D3D9_INCLUDED

#include "video/vertex_decl.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VertexDeclD3D9 : public VertexDecl {
	static const unsigned MAX_ELEMENTS = 8;

public:
	static VertexDeclPtr get(const Type type);

private:
	VertexDeclD3D9(const Type type);

public:
	~VertexDeclD3D9();

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

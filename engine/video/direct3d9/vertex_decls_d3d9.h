#ifndef VERTEX_DECLS_D3D9_INCLUDED
#define VERTEX_DECLS_D3D9_INCLUDED

#include "video/vertex_decls.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VertexDeclsD3D9 : public VertexDecls {
	static const unsigned MAX_ELEMENTS = 8;

	static const D3DVERTEXELEMENT9 ELEMENTS[COUNT][MAX_ELEMENTS];

public:
	VertexDeclsD3D9() { memset(&vertexDecls_[0], 0, sizeof(vertexDecls_)); }

	~VertexDeclsD3D9();

public:
	// interface: VertexDecls
	virtual void initialize();
	virtual void activate(const Type type);

private:
	// Direct3D
	IDirect3DVertexDeclaration9* vertexDecls_[COUNT];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

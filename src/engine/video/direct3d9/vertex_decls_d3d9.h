#pragma once

#include "video/vertex_decls.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VertexDeclsD3D9 : public VertexDecls {
	static const uint MAX_ELEMENTS = 8;

	static const D3DVERTEXELEMENT9 ELEMENTS[COUNT][MAX_ELEMENTS];

public:
	static const TCHAR* PATHS[COUNT];

public:
	VertexDeclsD3D9() { memset(&vertexDecls_[0], 0, sizeof(vertexDecls_)); }

	~VertexDeclsD3D9();

public:
	// interface: VertexDecls
	virtual bool initialize();
	virtual void activate(const Type type);
	virtual void terminate();

private:
	// Direct3D
	IDirect3DVertexDeclaration9* vertexDecls_[COUNT];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

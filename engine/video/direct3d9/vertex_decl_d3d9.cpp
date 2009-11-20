#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "video_d3d9.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const D3DVERTEXELEMENT9 VertexDeclD3D9::ELEMENTS[Type_COUNT][MAX_ELEMENTS] = {
		// stream, offset, type, method, usage, usage index

	{	//POS_DIFFUSE_TEX
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		{ 0, 16, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
		D3DDECL_END()
	},

	//{	//POS_NORMAL_TEX
	//	{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
	//	{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0},
	//	{ 0, 24, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
	//	D3DDECL_END()
	//},
};


VertexDeclPtr VertexDeclD3D9::vertexDecls_[Type_COUNT];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDeclPtr VertexDeclD3D9::get(const Type type) {
	assert(type < Type_COUNT);

	if (!vertexDecls_[type])
		vertexDecls_[type] = VertexDeclPtr(new VertexDeclD3D9(type));

	return vertexDecls_[type];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDeclD3D9::VertexDeclD3D9(const Type type)
: vertexDecl_(NULL) {
	CHECKED_D3D_CALL(VideoD3D9::inst().device().CreateVertexDeclaration(ELEMENTS[type], &vertexDecl_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDeclD3D9::~VertexDeclD3D9() {
	if (vertexDecl_)
		vertexDecl_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VertexDeclD3D9::activate() {
	CHECKED_D3D_CALL(VideoD3D9::inst().device().SetVertexDeclaration(vertexDecl_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECT3D9

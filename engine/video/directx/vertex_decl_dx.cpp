#include "stdafx.h"

#ifdef VIDEO_DIRECTX
#include "video_system_dx.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const D3DVERTEXELEMENT9 VertexDeclDX::ELEMENTS[Type_COUNT][MAX_ELEMENTS] = {
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


VertexDeclPtr VertexDeclDX::vertexDecls_[Type_COUNT];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDeclPtr VertexDeclDX::get(const Type type) {
	assert(type < Type_COUNT);

	if (!vertexDecls_[type])
		vertexDecls_[type] = VertexDeclPtr(new VertexDeclDX(type));

	return vertexDecls_[type];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDeclDX::VertexDeclDX(const Type type)
: vertexDecl_(NULL) {
	CHECKED_D3D_CALL(VideoDX::inst().device().CreateVertexDeclaration(ELEMENTS[type], &vertexDecl_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDeclDX::~VertexDeclDX() {
	if (vertexDecl_)
		vertexDecl_->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VertexDeclDX::activate() {
	CHECKED_D3D_CALL(VideoDX::inst().device().SetVertexDeclaration(vertexDecl_));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIDEO_DIRECTX

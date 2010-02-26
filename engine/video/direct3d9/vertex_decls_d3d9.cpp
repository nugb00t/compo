#include "stdafx.h"

#ifdef VIDEO_DIRECT3D9
#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const D3DVERTEXELEMENT9 VertexDeclsD3D9::ELEMENTS[COUNT][MAX_ELEMENTS] = {
		// stream, offset, type, method, usage, usage index

	{	// POS_DIFFUSE
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		D3DDECL_END()
	},

	{	// POS_DIFFUSE_TEX
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
		{ 0, 12, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
		{ 0, 16, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
		D3DDECL_END()
		},

	//{	// POS_NORMAL_TEX
	//	{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
	//	{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0},
	//	{ 0, 24, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
	//	D3DDECL_END()
	//},
};

const TCHAR* VertexDeclsD3D9::PATHS[COUNT] = {
	_T("fx/pos_diffuse.h"),
	_T("fx/pos_diffuse_tex.h"),
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VertexDeclsD3D9::~VertexDeclsD3D9() {
	for (uint i = 0; i < COUNT; ++i)
		if (vertexDecls_[i])
			vertexDecls_[i]->Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VertexDeclsD3D9::initialize() {
	for (uint i = 0; i < COUNT; ++i)
		CHECKED_D3D_CALL(g_engine.videoImplD3D9->device().CreateVertexDeclaration(ELEMENTS[i], &vertexDecls_[i]));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void VertexDeclsD3D9::activate(const Type type) {
	assert(0 <= type && type < COUNT);

	CHECKED_D3D_CALL(g_engine.videoImplD3D9->device().SetVertexDeclaration(vertexDecls_[type]));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
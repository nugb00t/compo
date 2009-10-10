#ifndef VERTEX_INCLUDED
#define VERTEX_INCLUDED

#include "utility/intrusive_ptr_base.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VertexDecl : public IntrusivePtrBase {
public:
	enum Type {
		POS_DIFFUSE_TEX,
		//POS_NORMAL_TEX,

		Type_COUNT
	};

public:
	virtual void activate() = 0; 
};

typedef boost::intrusive_ptr<VertexDecl> VertexDeclPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

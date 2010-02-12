#ifndef ORB_VIDEO_INCLUDED
#define ORB_VIDEO_INCLUDED

#include "video/video_component.h"
#include "video/effect.h"
#include "video/mesh.h"
#include "video/texture.h"
#include "video/vertex_decls.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::VideoComponent {
    typedef engine::VertexDecls::PosDiffuseTex Vertex;

public:
    OrbVideo() : mesh_(NULL), effect_(NULL) {}

	// interface: VideoComponent
	virtual void draw(const engine::ServerState::Entity& fromClient);

private:
	static const Vertex vertices_[];
	static const u16 indices_[];

    static const engine::Effect::TextureUniform TEX_UNIFORMS[];

    boost::scoped_ptr<engine::DynamicMesh> mesh_;
    boost::scoped_ptr<engine::Effect> effect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

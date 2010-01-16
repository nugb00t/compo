#ifndef ORB_VIDEO_INCLUDED
#define ORB_VIDEO_INCLUDED

#include "video/video_component.h"
#include "video/effect.h"
#include "video/mesh.h"
#include "video/texture.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::VideoComponent {

#pragma pack(push, 4)
	struct Vertex {
		Vector3	xyz;
		unsigned diffuse;
		Vector2	uv;

		Vector2 dummy;
	};
#pragma pack(pop)

public:
    OrbVideo() : mesh_(NULL), effect_(NULL) {}

	// interface: VideoComponent
	virtual void draw(const engine::ServerState::Entity& fromClient);

private:
	static const Vertex vertices_[];
	static const short indices_[];

    static const engine::Effect::Uniform uniforms_[];
    static const engine::Effect::TextureUniform texUniforms_[];

	engine::MeshPtr mesh_;
    engine::EffectPtr effect_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

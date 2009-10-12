#ifndef ORB_VIDEO_INCLUDED
#define ORB_VIDEO_INCLUDED

#include "video/video_component.h"
#include "video/effect.h"
#include "video/mesh.h"
#include "video/texture.h"

namespace game_playground {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OrbVideo : public engine::EntityVideoComponent {

#pragma pack(push, 4)
	struct Vertex {
		Vector3	xyz;
		unsigned diffuse;
		Vector2	uv;
	};
#pragma pack(pop)

public:
    OrbVideo();

	// interface: EntityVideoComponent
	virtual void update(const engine::Entity::Params& fromLogic, const float dt);

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

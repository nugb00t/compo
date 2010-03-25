#include "stdafx.h"

#include "playground_local_client.h"

#include "engine.h"

using namespace game_playground;

namespace {
	const float AXIS_SCALE = .1f;
	const float AXIS_FALLOFF = 10.f;	// msec
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameLocalClient::handleControls(const engine::Controls& controls, engine::ServerRequests::Client& request) {
	assert(!request.valid);

	const uint now = engine::Engine::inst().time->msec();

	const engine::Controls::AxisEvent& x = controls.axis[engine::Controls::MOUSE_X].get();
	const uint ageX = now - x.time;
	const engine::Controls::AxisEvent& y = controls.axis[engine::Controls::MOUSE_Y].get();
	const uint ageY = now - y.time;

	request.positionalVelocity = Vector3(
		ageX < AXIS_FALLOFF ? (float)x.value * AXIS_SCALE * (AXIS_FALLOFF - ageX) / AXIS_FALLOFF : 0.f, 
		ageY < AXIS_FALLOFF ? (float)y.value * AXIS_SCALE * (AXIS_FALLOFF - ageY) / AXIS_FALLOFF : 0.f, 
		0.f);

	request.valid = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameLocalClient::showWorld(const engine::ServerState& fromArbiter, engine::ServerState& toVideo) {
	memcpy(&toVideo, &fromArbiter, sizeof(toVideo));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

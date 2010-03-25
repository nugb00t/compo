#include "stdafx.h"

#include "playground_local_client.h"

#include "engine.h"

using namespace engine;
using namespace game_playground;

namespace {
	const float AXIS_SCALE = .1f;
	const float AXIS_FALLOFF = 10.f;	// msec
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameLocalClient::handleControls(const InputData& controls, ServerRequests::Client& request) {
	assert(!request.valid);

	const uint now = g_engine.time->msec();

	const InputData::AxisEvent& x = controls.axis[InputData::MOUSE_X].get();
	const uint ageX = now - x.time;
	const InputData::AxisEvent& y = controls.axis[InputData::MOUSE_Y].get();
	const uint ageY = now - y.time;

	request.positionalVelocity = Vector3(
		ageX < AXIS_FALLOFF ? (float)x.value * AXIS_SCALE * (AXIS_FALLOFF - ageX) / AXIS_FALLOFF : 0.f, 
		ageY < AXIS_FALLOFF ? (float)y.value * AXIS_SCALE * (AXIS_FALLOFF - ageY) / AXIS_FALLOFF : 0.f, 
		0.f);

	request.valid = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameLocalClient::showWorld(const ServerState& fromArbiter, ServerState& toVideo) {
	memcpy(&toVideo, &fromArbiter, sizeof(toVideo));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

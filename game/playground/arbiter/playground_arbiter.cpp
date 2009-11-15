#include "stdafx.h"

#include "playground_arbiter.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameArbiter::marshall(const ServerState& last, const ServerRequests& requests, ServerState& next) {
	// TODO: move clients

	for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
		if (last.entities[i].active) {
			next.entities[i].rotation = last.entities[i].rotation * requests.entities[i].rotationalVelocity;
			next.entities[i].position = last.entities[i].position + requests.entities[i].positionalVelocity;

			next.entities[i].active = true;
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

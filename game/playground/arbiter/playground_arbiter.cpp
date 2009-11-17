#include "stdafx.h"

#include "playground_arbiter.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameArbiter::marshall(const ServerState& last, const ServerRequests& requests, ServerState& next) {
	for (unsigned i = 0; i < ServerState::MAX_CLIENTS; ++i)
		if (last.clients[i].active) {
			next.clients[i].active = true;

			next.clients[i].rotation = last.clients[i].rotation * requests.clients[i].rotationalVelocity;
			next.clients[i].position = last.clients[i].position + requests.clients[i].positionalVelocity;

			next.clients[i].position = Vector3(
				cml::clamp(next.clients[i].position[0], -5.f, 5.f),
				cml::clamp(next.clients[i].position[1], -5.f, 5.f),
				0.f);
		}

	for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
		if (last.entities[i].active) {
			next.entities[i].active = true;

			next.entities[i].rotation = last.entities[i].rotation * requests.entities[i].rotationalVelocity;
			next.entities[i].position = last.entities[i].position + requests.entities[i].positionalVelocity;

			next.entities[i].position = Vector3(
				cml::clamp(next.entities[i].position[0], -5.f, 5.f),
				cml::clamp(next.entities[i].position[1], -5.f, 5.f),
				0.f);
		}

	// temp
	next.entities[0].position = next.clients[0].position;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

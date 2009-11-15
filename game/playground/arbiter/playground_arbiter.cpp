#include "stdafx.h"

#include "playground_arbiter.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameArbiter::marshall(const ServerState& last, const ServerRequests& requests, ServerState& next) {
	for (unsigned i = 0; i < ServerState::MAX_CLIENTS; ++i)
		if (last.clients[i].active) {
			next.clients[i].rotation = last.clients[i].rotation * requests.clients[i].rotationalVelocity;
			next.clients[i].position = last.clients[i].position + requests.clients[i].positionalVelocity;

			cml::clamp(next.clients[i].position, Vector3(-2.f, -2.f, 0.f), Vector3(2.f, 2.f, 0.f));
			next.clients[i].active = true;
		}

	for (unsigned i = 0; i < ServerState::MAX_ENTITIES; ++i)
		if (last.entities[i].active) {
			next.entities[i].rotation = last.entities[i].rotation * requests.entities[i].rotationalVelocity;
			next.entities[i].position = last.entities[i].position + requests.entities[i].positionalVelocity;

			cml::clamp(next.clients[i].position, Vector3(-2.f, -2.f, 0.f), Vector3(2.f, 2.f, 0.f));
			next.entities[i].active = true;
		}

	// temp
	next.entities[0].position = next.clients[0].position / 100.f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

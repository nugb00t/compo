#include "stdafx.h"

#include "playground_arbiter.h"

using namespace engine;
using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameArbiter::marshall(const ServerState& last, const ServerRequests& requests, ServerState& next) {
	for (uint i = 0; i < ServerState::MAX_CLIENTS; ++i) {
		next.clients[i].active = last.clients[i].active;

		if (requests.clients[i].valid) {
			next.clients[i].position = last.clients[i].position + requests.clients[i].positionalVelocity;
			next.clients[i].rotation = last.clients[i].rotation * requests.clients[i].rotationalVelocity;

			next.clients[i].position = Vector3(
				cml::clamp(next.clients[i].position[0], -5.f, 5.f),
				cml::clamp(next.clients[i].position[1], -5.f, 5.f),
				0.f);
		} else {
			next.clients[i].position = last.clients[i].position;
			next.clients[i].rotation = last.clients[i].rotation;
		}
	}

	for (uint i = 0; i < ServerState::MAX_ENTITIES; ++i) {
		next.entities[i].active = last.entities[i].active;

		if (requests.entities[i].valid) {
			next.entities[i].position = last.entities[i].position + requests.entities[i].positionalVelocity;
			next.entities[i].rotation = last.entities[i].rotation * requests.entities[i].rotationalVelocity;

			next.entities[i].position = Vector3(
				cml::clamp(next.entities[i].position[0], -5.f, 5.f),
				cml::clamp(next.entities[i].position[1], -5.f, 5.f),
				0.f);
		} else {
			next.entities[i].position = last.entities[i].position;
			next.entities[i].rotation = last.entities[i].rotation;
		}
	}

	// temp
	next.entities[0].position = next.clients[0].position;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

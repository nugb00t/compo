#include "stdafx.h"

#include "playground_client.h"

using namespace game_playground;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameClient::handleControls(const engine::InputData& controls, engine::ClientRequest& clientRequest) {
	const int x = controls.axis[engine::InputData::MOUSE_X].events[0].value;
	const int y = controls.axis[engine::InputData::MOUSE_Y].events[0].value;

	clientRequest.positionalVelocity = Vector3((float)x, (float)y, 0.f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

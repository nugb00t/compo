#include "stdafx.h"

#include "resources.h"

#include "engine.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::initialize() {
	TiXmlDocument doc("game.xml");
	doc.LoadFile();

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Resources::update() {
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

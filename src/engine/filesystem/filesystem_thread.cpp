#include "stdafx.h"

#include "filesystem_thread.h"

#include "filesystem/resources.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FileSystemThread::update() {
	return Resources::inst().update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
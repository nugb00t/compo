#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Window
{
public:
	virtual HWND handle() const = 0;
	//virtual const uint width() const = 0;
	//virtual const uint height() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
#pragma once

#ifdef PLATFORM_WIN51
#include "../system_loop.h"
#include "../controls.h"

#include "input_w51.h"
#include "window_w51.h"

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SystemLoopW51 : public SystemLoop, public kaynine::Holder<SystemLoopW51> {
public:
	SystemLoopW51() { set(this); }
	
    // interface: kaynine::ThreadObject
    virtual bool initialize();
    virtual bool update();
	virtual void terminate();

	// interface: SystemLoop
	virtual Controls& controls() { return controls_; }
	virtual Window& window() { return *window_; }

private:
    static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

private:
    Controls controls_;
	boost::scoped_ptr<WindowW51> window_;
	boost::scoped_ptr<InputW51> input_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

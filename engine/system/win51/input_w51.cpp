#include "stdafx.h"

#ifdef PLATFORM_WIN51
#include "input_w51.h"

#include "core/timer.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputW51::InputW51() {
	memset(&controls_, 0, sizeof(controls_));

	RAWINPUTDEVICE rid[2] = {
		{ 0x01, 0x02, RIDEV_NOLEGACY, NULL },
		{ 0x01, 0x06, RIDEV_NOLEGACY, NULL }
	};

	CHECKED_WIN_CALL(::RegisterRawInputDevices(rid, 2, sizeof(rid[0])));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputW51::handleRawInput(HRAWINPUT handle) {
	const unsigned long now = Timer::inst().msec();

	unsigned size;

	unsigned ret = ::GetRawInputData(handle, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
	assert(!ret);

	RAWINPUT raw;
	assert(size == sizeof(raw));
	
	ret = ::GetRawInputData(handle, RID_INPUT, &raw, &size, sizeof(RAWINPUTHEADER));
	assert(ret == size);

	if (raw.header.dwType == RIM_TYPEMOUSE) {
		unsigned short flags = raw.data.mouse.usButtonFlags;

		// 5 mouse buttons
		if (flags & RI_MOUSE_LEFT_BUTTON_DOWN)
			controls_.buttons[VK_LBUTTON].pushed = now;
		if (flags & RI_MOUSE_LEFT_BUTTON_UP)
			controls_.buttons[VK_LBUTTON].released = now;

		if (flags & RI_MOUSE_RIGHT_BUTTON_DOWN)
			controls_.buttons[VK_RBUTTON].pushed = now;
		if (flags & RI_MOUSE_RIGHT_BUTTON_UP)
			controls_.buttons[VK_RBUTTON].released = now;

		if (flags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
			controls_.buttons[VK_MBUTTON].pushed = now;
		if (flags & RI_MOUSE_MIDDLE_BUTTON_UP)
			controls_.buttons[VK_MBUTTON].released = now;

		if (flags & RI_MOUSE_BUTTON_4_DOWN)
			controls_.buttons[VK_XBUTTON1].pushed = now;
		if (flags & RI_MOUSE_BUTTON_4_UP)
			controls_.buttons[VK_XBUTTON1].released = now;

		if (flags & RI_MOUSE_BUTTON_5_DOWN)
			controls_.buttons[VK_XBUTTON2].pushed = now;
		if (flags & RI_MOUSE_BUTTON_5_UP)
			controls_.buttons[VK_XBUTTON2].released = now;

		// and a wheel axis
		if (flags & RI_MOUSE_WHEEL)
			controls_.axis[MOUSE_WHEEL].add(now, raw.data.mouse.usButtonData);
	} else if (raw.header.dwType == RIM_TYPEKEYBOARD) {
		RAWKEYBOARD& keyboard = raw.data.keyboard;

		if (keyboard.Message == WM_KEYDOWN)
			controls_.buttons[keyboard.VKey].pushed = now;

		if (keyboard.Message == WM_KEYUP)
			controls_.buttons[keyboard.VKey].released = now;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

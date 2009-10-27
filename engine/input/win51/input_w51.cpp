#include "stdafx.h"

#ifdef PLATFORM_WIN51
#include "input_w51.h"

#include "input/input_data.h"

#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InputW51::InputW51() {
	memset(&controls_, 0, sizeof(controls_));

	RAWINPUTDEVICE rid[2] = {
		{ 0x01, 0x02, 0/*RIDEV_NOLEGACY*/, NULL },		// mouse
		{ 0x01, 0x06, RIDEV_NOLEGACY, NULL }		// keyboard
	};

	CHECKED_WIN_CALL(::RegisterRawInputDevices(rid, 2, sizeof(rid[0])));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef USE_BUFFERED_RAW_INPUT
void InputW51::buffered(const HRAWINPUT handle, const unsigned long now) {
	/*
	unsigned ret = ::GetRawInputBuffer(NULL, &size, sizeof(RAWINPUTHEADER));
	assert(ret == 0);
	assert(size < sizeof(RAWINPUT) * RAW_INPUT_BUFFER_COUNT);
	*/

	static RAWINPUT buffers[RAW_INPUT_BUFFER_COUNT];

	unsigned size = sizeof(buffers); 
	while (true) {
		const unsigned count = ::GetRawInputBuffer(buffers, &size, sizeof(RAWINPUTHEADER));
		if (!count)
			break;

		RAWINPUT* raw = buffers;
		for (UINT i = 0; i < count; ++i, raw = NEXTRAWINPUTBLOCK(raw)) {
			assert(raw->header.dwSize == sizeof(RAWINPUT));
			process(raw, now);
		}

		//::DefRawInputProc(&buffers[0], count, sizeof(RAWINPUTHEADER)); 
	}
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputW51::unbuffered(const HRAWINPUT handle, const unsigned long now) {
	//unsigned size;

	//// inquire on the space requested
	//const unsigned ret = ::GetRawInputData(handle, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
	//assert(!ret);
	//assert(size == sizeof(RAWINPUT));

	RAWINPUT raw;

	// read raw input
	unsigned size = sizeof(raw);
	const unsigned read = ::GetRawInputData(handle, RID_INPUT, &raw, &size, sizeof(RAWINPUTHEADER));
	assert(read == size);

	process(raw, now);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputW51::process(const RAWINPUT& raw, const unsigned long now) {
	if (raw.header.dwType == RIM_TYPEMOUSE) {
		const RAWMOUSE& mouse = raw.data.mouse;

		// 5 mouse buttons
		if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
			controls_.buttons[VK_LBUTTON].pushed = now;
		if (mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)
			controls_.buttons[VK_LBUTTON].released = now;

		if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
			controls_.buttons[VK_RBUTTON].pushed = now;
		if (mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)
			controls_.buttons[VK_RBUTTON].released = now;

		if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
			controls_.buttons[VK_MBUTTON].pushed = now;
		if (mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP)
			controls_.buttons[VK_MBUTTON].released = now;

		if (mouse.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN)
			controls_.buttons[VK_XBUTTON1].pushed = now;
		if (mouse.usButtonFlags & RI_MOUSE_BUTTON_4_UP)
			controls_.buttons[VK_XBUTTON1].released = now;

		if (mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN)
			controls_.buttons[VK_XBUTTON2].pushed = now;
		if (mouse.usButtonFlags & RI_MOUSE_BUTTON_5_UP)
			controls_.buttons[VK_XBUTTON2].released = now;

		static int lastX = 0;
		static int lastY = 0;
		static int lastWheel = 0;

		// axis
		if (mouse.usFlags & MOUSE_MOVE_ABSOLUTE) {
			controls_.axis[InputData::MOUSE_X].add(now, mouse.lLastX - lastX);
			controls_.axis[InputData::MOUSE_Y].add(now, mouse.lLastY - lastY);

			lastX = mouse.lLastX;
			lastY = mouse.lLastY;

			if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {
				controls_.axis[InputData::MOUSE_WHEEL].add(now, mouse.usButtonData - lastWheel);
				lastWheel = mouse.usButtonData;
			}
		} else {
			controls_.axis[InputData::MOUSE_X].add(now, mouse.lLastX);
			controls_.axis[InputData::MOUSE_Y].add(now, mouse.lLastY);

			lastX = 0;
			lastY = 0;

			if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {
				controls_.axis[InputData::MOUSE_WHEEL].add(now, mouse.usButtonData);
				lastWheel = 0;
			}
		}
	} else if (raw.header.dwType == RIM_TYPEKEYBOARD) {
		const RAWKEYBOARD& keyboard = raw.data.keyboard;

		if (keyboard.Message == WM_KEYDOWN)
			controls_.buttons[keyboard.VKey].pushed = now;

		if (keyboard.Message == WM_KEYUP)
			controls_.buttons[keyboard.VKey].released = now;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

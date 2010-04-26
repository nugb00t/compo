#include "stdafx.h"

#ifdef PLATFORM_WIN51
#include "input_w51.h"

#include "core/sync.h"

using namespace engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputW51::initialize() {
	RAWINPUTDEVICE rid[2] = {
		{ 0x01, 0x02, 0/*RIDEV_NOLEGACY*/, NULL },	// mouse
		{ 0x01, 0x06, RIDEV_NOLEGACY, NULL }		// keyboard
	};

	CHECKED_CALL(::RegisterRawInputDevices(rid, 2, sizeof(rid[0])));
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef USE_BUFFERED_RAW_INPUT
void InputW51::buffered(const HRAWINPUT handle, const uint now) {
	/*
	uint ret = ::GetRawInputBuffer(NULL, &size, sizeof(RAWINPUTHEADER));
	assert(ret == 0);
	assert(size < sizeof(RAWINPUT) * RAW_INPUT_BUFFER_COUNT);
	*/

	static RAWINPUT buffers[RAW_INPUT_BUFFER_COUNT];

	uint size = sizeof(buffers); 
	while (true) {
		const uint count = ::GetRawInputBuffer(buffers, &size, sizeof(RAWINPUTHEADER));
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

void InputW51::unbuffered(const HRAWINPUT handle, const uint now) {
	//uint size;

	//// inquire on the space requested
	//const uint ret = ::GetRawInputData(handle, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
	//assert(!ret);
	//assert(size == sizeof(RAWINPUT));

	RAWINPUT raw;

	// read raw input
	uint size = sizeof(raw);
	DEBUG_ONLY(const uint read =)
		::GetRawInputData(handle, RID_INPUT, &raw, &size, sizeof(RAWINPUTHEADER));
	assert(read <= size);

	process(raw, now);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputW51::process(const RAWINPUT& raw, const uint now) {
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
			controls_.axis[Controls::MOUSE_X].add(Controls::AxisEvent(now,  mouse.lLastX - lastX));
			controls_.axis[Controls::MOUSE_Y].add(Controls::AxisEvent(now, -mouse.lLastY - lastY));

			lastX =  mouse.lLastX;
			lastY = -mouse.lLastY;

			if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {
				controls_.axis[Controls::MOUSE_WHEEL].add(Controls::AxisEvent(now, mouse.usButtonData - lastWheel));
				lastWheel = mouse.usButtonData;
			}
		} else {
			controls_.axis[Controls::MOUSE_X].add(Controls::AxisEvent(now,  mouse.lLastX));
			controls_.axis[Controls::MOUSE_Y].add(Controls::AxisEvent(now, -mouse.lLastY));

			lastX = 0;
			lastY = 0;

			if (mouse.usButtonFlags & RI_MOUSE_WHEEL) {
				controls_.axis[Controls::MOUSE_WHEEL].add(Controls::AxisEvent(now, mouse.usButtonData));
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

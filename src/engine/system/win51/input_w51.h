#pragma once

#ifdef PLATFORM_WIN51

//#define USE_BUFFERED_RAW_INPUT

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class InputW51 : public kaynine::Holder<InputW51> {
#ifdef USE_BUFFERED_RAW_INPUT
	static const uint RAW_INPUT_BUFFER_COUNT = 16;
#endif

public:
	InputW51();

	// interface: Input
	virtual bool initialize();

	inline void processRawInput(const HRAWINPUT handle, const uint now) {
#ifdef USE_BUFFERED_RAW_INPUT
		unbuffered(handle, now);
#else
		unbuffered(handle, now);
#endif
	}

private:
#ifdef USE_BUFFERED_RAW_INPUT
	void buffered(const HRAWINPUT handle, const uint now);
#else
	void unbuffered(const HRAWINPUT handle, const uint now);
#endif

	void process(const RAWINPUT& raw, const uint now);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

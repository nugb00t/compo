#pragma once

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Time {
public:
	Time();

	const uint msec() const;
	const float now() const;

private:
	const uint zero_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
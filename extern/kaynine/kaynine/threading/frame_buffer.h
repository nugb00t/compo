/*******************************************************//**
	@file

	@brief	Shared memory buffer

	@author Andrew Gresyk

	@date	28.09.2005
*//********************************************************/
#pragma once

#include "sync_wrappers.h"

#include "../utility/safe_bool.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	Purpose:
	Facility for sending data (in one direction) without delivery control.
	Delivery validation (if needed) should be done using data package identification or similar mechanism.

	Usage:

	// some place visible from both threads:
	FrameBuffer<ServerState> sharedBuffer;

	// sender thread's main loop:
	{
		FrameBuffer<ServerState>::Writable toBeSent(sharedBuffer);
		fillIn(toBeSent.data());
	}

	// receiver thread's main loop:
	{
		FrameBuffer<ServerState>::Readable received(sharedBuffer);
		assert(received);													//< should never fail with triple buffering..
		process(received.data());
	}
*/

template <class TContents>
class FrameBuffer {
public:
	typedef TContents CONTENTS_TYPE;

public:
	//-----------------------------------------------------------------------------------------------------------------

	class Readable : public SafeBool<Readable> {
	public:
		explicit Readable(const FrameBuffer& frameBuffer)
			: frameBuffer_(frameBuffer), initialized_(frameBuffer_.lockReadable()) {}

		~Readable() { release(); }
		inline void release() { if (initialized_) frameBuffer_.unlockReadable(); }

		inline const TContents& data() { assert(frameBuffer_.getReadable()); return *frameBuffer_.getReadable(); }

		inline const unsigned age() const { return frameBuffer_.age(); }

		// interface: SafeBool
		inline bool boolean_test() const { return initialized_; }

	private:
		Readable(const Readable&);				// prohibited
		Readable operator =(const Readable&);	// prohibited

	private:
		const FrameBuffer& frameBuffer_;
		bool initialized_;
	};

    //-----------------------------------------------------------------------------------------------------------------

	class Writable : public SafeBool<Writable>  {
	public:
		explicit Writable(FrameBuffer& frameBuffer) 
			: frameBuffer_(frameBuffer), initialized_(frameBuffer_.lockWritable()) {}

		~Writable() { release(); }
		inline void release() { if (initialized_) frameBuffer_.unlockWritable(); }

		inline TContents& data() { assert(frameBuffer_.getWritable()); return *frameBuffer_.getWritable(); }

		// interface: SafeBool
		inline bool boolean_test() const { return initialized_; }

	private:
		Writable(const Writable&);				// prohibited
		Writable operator =(const Writable&);	// prohibited

	private:
		FrameBuffer& frameBuffer_;
		bool initialized_;
	};

    //-----------------------------------------------------------------------------------------------------------------

private:
	static const int INVALID_FRAME = -1;
	static const int FRAME_COUNT = 3;

public:
	FrameBuffer();

private:
	const bool lockWritable();
	TContents* getWritable();
	void unlockWritable();

	const bool lockReadable() const;
	const TContents* getReadable() const;
	void unlockReadable() const;

	inline const unsigned age() const { return age_; }

private:
	// shared data
	TContents			contents_[FRAME_COUNT];

	int			writing_;
	mutable int fresh_;
	mutable int	reading_;
	mutable unsigned age_;

	mutable CriticalSection		guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
FrameBuffer<TContents>::FrameBuffer()
	: writing_(INVALID_FRAME), fresh_(INVALID_FRAME), reading_(INVALID_FRAME), age_(0) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
const bool FrameBuffer<TContents>::lockWritable() {
	AutoLock<> lock(guard_);

	assert(writing_ == INVALID_FRAME);

	// pick the oldest frame
	for (int i = 0; i < FRAME_COUNT; ++i)
		if (i != reading_ && i != fresh_) {
			writing_ = i;
			break;
		}

	assert(writing_ != INVALID_FRAME);

	return writing_ != INVALID_FRAME;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
TContents* FrameBuffer<TContents>::getWritable() {
	AutoLock<> lock(guard_);

	assert(0 <= writing_ && writing_ < FRAME_COUNT);

	return &contents_[writing_];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
void FrameBuffer<TContents>::unlockWritable() {
	AutoLock<> lock(guard_);

	assert(0 <= writing_ && writing_ < FRAME_COUNT);

	fresh_ = writing_;
	age_ = 0;
	writing_ = INVALID_FRAME;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
const bool FrameBuffer<TContents>::lockReadable() const {
	AutoLock<> lock(guard_);

	assert(reading_ == INVALID_FRAME);

	reading_ = fresh_;
	++age_;

	return reading_ != INVALID_FRAME;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
const TContents* FrameBuffer<TContents>::getReadable() const {
	AutoLock<> lock(guard_);

	assert(0 <= reading_ && reading_ < FRAME_COUNT);

	return &contents_[reading_];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
void FrameBuffer<TContents>::unlockReadable() const {
	AutoLock<> lock(guard_);

	assert(0 <= reading_ && reading_ < FRAME_COUNT);

	reading_ = INVALID_FRAME;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

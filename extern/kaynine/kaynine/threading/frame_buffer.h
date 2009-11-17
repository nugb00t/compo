/*******************************************************//**
	@file

	@brief	Shared memry area template

	@author Andrew S. Gresyk

	@date	28.09.2005
*//********************************************************/
#ifndef KN_FRAME_BUFFER_INCLUDED
#define KN_FRAME_BUFFER_INCLUDED

#include "sync_wrappers.h"

#include "../utility/safe_bool.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
class FrameBuffer {
public:
	typedef TContents CONTENTS_TYPE;

public:
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Readable : public safe_bool<> {
	public:
		typedef TContents CONTENTS_TYPE;

	public:
		explicit Readable(const FrameBuffer& frameBuffer)
			: frameBuffer_(frameBuffer), initialized_(frameBuffer_.lockReadable()) {}

		~Readable() { release(); }
		inline void release() { if (initialized_) frameBuffer_.unlockReadable(); }

		inline const TContents& data() { assert(frameBuffer_.getReadable()); return *frameBuffer_.getReadable(); }
		inline bool boolean_test() const { return initialized_; }

	private:
		Readable(const Readable&);				// prohibited
		Readable operator =(const Readable&);	// prohibited

	private:
		const FrameBuffer& frameBuffer_;
		bool initialized_;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Writable : public safe_bool<>  {
	public:
		typedef TContents CONTENTS_TYPE;

	public:
		explicit Writable(FrameBuffer& frameBuffer) 
			: frameBuffer_(frameBuffer), initialized_(frameBuffer_.lockWritable()) {}

		~Writable() { release(); }
		inline void release() { if (initialized_) frameBuffer_.unlockWritable(); }

		inline TContents& data() { assert(frameBuffer_.getWritable()); return *frameBuffer_.getWritable(); }
		inline bool boolean_test() const { return initialized_; }

	private:
		Writable(const Writable&);				// prohibited
		Writable operator =(const Writable&);	// prohibited

	private:
		FrameBuffer& frameBuffer_;
		bool initialized_;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

private:
	// shared data
	TContents			contents_[FRAME_COUNT];

	int			writing_;
	mutable int fresh_;
	mutable int	reading_;

	mutable CriticalSection		guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
FrameBuffer<TContents>::FrameBuffer()
	: writing_(INVALID_FRAME), fresh_(INVALID_FRAME), reading_(INVALID_FRAME) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
const bool FrameBuffer<TContents>::lockWritable() {
	AutoLock<> lock(guard_);

	assert(writing_ == INVALID_FRAME);

	// pick oldest frame
	for (int i = 0; i < FRAME_COUNT; ++i)
		if (i != reading_ && i != fresh_) {
			writing_ = i;
			break;
		}

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
	writing_ = INVALID_FRAME;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
const bool FrameBuffer<TContents>::lockReadable() const {
	AutoLock<> lock(guard_);

	assert(reading_ == INVALID_FRAME);

	reading_ = fresh_;
	fresh_ = INVALID_FRAME;

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

#endif //_KN_FRAME_BUFFER_INCLUDED_
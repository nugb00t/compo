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

		inline const TContents& data() { return *frameBuffer_.getReadable(); }
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

		inline TContents& data() { return *frameBuffer_.getWritable(); }
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
	enum CONSTANTS {
		FRAME_INVALID = -1,
		NUM_FRAMES = 3,
	};

public:
	FrameBuffer();

private:
	bool lockWritable();
	TContents* getWritable();
	void unlockWritable();

	bool lockReadable() const;
	const TContents* getReadable() const;
	void unlockReadable() const;

private:
	// shared data
	TContents	contents_[NUM_FRAMES];
	int			timeline_[NUM_FRAMES];		//< Timeline array holds frame indexes from newest to oldest order.
	bool		initialized_[NUM_FRAMES];
	mutable int	reading_;
	int			writing_;

	mutable CriticalSection		guard_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
FrameBuffer<TContents>::FrameBuffer()
	: reading_(FRAME_INVALID), writing_(FRAME_INVALID) {
		for (int i = 0; i < NUM_FRAMES; ++i) {
			timeline_[i] = i;
			initialized_[i] = false;
		}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
bool FrameBuffer<TContents>::lockWritable() {
	AutoLock<> lock(guard_);

	// writing in progress
	if (writing_ != FRAME_INVALID)
		return false;

	// pick oldest frame
	for (int iTime = NUM_FRAMES - 1; iTime >= 0; --iTime)
		if (timeline_[iTime] != reading_) {
			writing_ = timeline_[iTime];
			break;
		}

	assert(0 <= writing_ && writing_ < NUM_FRAMES);

	return writing_ != FRAME_INVALID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
TContents* FrameBuffer<TContents>::getWritable() {
	AutoLock<> lock(guard_);

	assert(0 <= writing_ && writing_ < NUM_FRAMES);

	if (writing_ == FRAME_INVALID)
		return NULL;
	else
		return &contents_[writing_];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
void FrameBuffer<TContents>::unlockWritable() {
	AutoLock<> lock(guard_);

	assert(0 <= timeline_[0] && timeline_[0] < NUM_FRAMES);

	if (writing_ != FRAME_INVALID) {
		// find age index
		int iTime;
		for (iTime = 0; iTime < NUM_FRAMES; ++iTime)
			if (timeline_[iTime] == writing_)
				break;

		// shift other frames' ages
		for (int i = iTime - 1; i >= 0; --i)
			timeline_[i + 1] = timeline_[i];

		timeline_[0] = writing_;
		initialized_[writing_] = true;
		writing_ = FRAME_INVALID;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
bool FrameBuffer<TContents>::lockReadable() const {
	AutoLock<> lock(guard_);

	if (reading_ != FRAME_INVALID)
		return false;

	// pick newest
	for (int iTime = 0; iTime < NUM_FRAMES; ++iTime)
		if (timeline_[iTime] != writing_ && initialized_[timeline_[iTime]]) {
			reading_ = timeline_[iTime];
			break;
		}

	return reading_ != FRAME_INVALID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
const TContents* FrameBuffer<TContents>::getReadable() const {
	AutoLock<> lock(guard_);

	if (reading_ == FRAME_INVALID)
		return NULL;
	else
		return &contents_[reading_];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TContents>
void FrameBuffer<TContents>::unlockReadable() const {
	AutoLock<> lock(guard_);

	reading_ = FRAME_INVALID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif //_KN_FRAME_BUFFER_INCLUDED_
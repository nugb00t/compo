/*******************************************************//**
	@file

	@brief	Shared memry area template

	@author Andrew S. Gresyk

	@date	28.09.2005
*//********************************************************/
#ifndef _KN_FRAME_BUFFER_INCLUDED_
#define _KN_FRAME_BUFFER_INCLUDED_


// kaynine
#include "tchar.h"
#include "sync_wrappers.h"


namespace kaynine {


/**
	Framebuffer class
*/
template <class TContents>
class FrameBuffer {
public:
	typedef TContents CONTENTS_TYPE;


private:
	enum CONSTANTS {
		FRAME_INVALID = -1,
		NUM_FRAMES = 3,
	};


private:
	// shared data
	TContents			contents_[NUM_FRAMES];
	int					aiTimeLine_[NUM_FRAMES];		//< Timeline array holds frame indexes from newest to oldest order.
	bool				abInitialized_[NUM_FRAMES];
	mutable int			iReading_;
	int					iWriting_;

	mutable CriticalSection		csIndexes_;


public:
	FrameBuffer();

	bool lockWritable();
	TContents* getWritable();
	void unlockWritable();

	bool lockReadable() const;
	const TContents* getReadable() const;
	void unlockReadable() const;
};


} //namespace kaynine


template <class TContents>
kaynine::FrameBuffer<TContents>::FrameBuffer()
	: iReading_(FRAME_INVALID), iWriting_(FRAME_INVALID) {
		for (int i = 0; i < NUM_FRAMES; ++i) {
			aiTimeLine_[i] = i;
			abInitialized_[i] = false;
		}
}


template <class TContents>
bool kaynine::FrameBuffer<TContents>::lockWritable() {
	AutoLock<CriticalSection> lock(&csIndexes_);

	// writing in progress
	if (iWriting_ != FRAME_INVALID)
		return false;

	// pick oldest frame
	for (int iTime = NUM_FRAMES - 1; iTime >= 0; --iTime)
		if (aiTimeLine_[iTime] != iReading_) {
			iWriting_ = aiTimeLine_[iTime];
			break;
		}

	assert(0 <= iWriting_ && iWriting_ < NUM_FRAMES);

	return iWriting_ != FRAME_INVALID;
}


template <class TContents>
TContents* kaynine::FrameBuffer<TContents>::getWritable() {
	AutoLock<CriticalSection> lock(&csIndexes_);

	assert(0 <= iWriting_ && iWriting_ < NUM_FRAMES);

	if (iWriting_ == FRAME_INVALID)
		return NULL;
	else
		return &contents_[iWriting_];
}


template <class TContents>
void kaynine::FrameBuffer<TContents>::unlockWritable() {
	AutoLock<CriticalSection> lock(&csIndexes_);

	assert(0 <= aiTimeLine_[0] && aiTimeLine_[0] < NUM_FRAMES);

	if (iWriting_ != FRAME_INVALID) {
		// find age index
		int iTime;
		for (iTime = 0; iTime < NUM_FRAMES; ++iTime)
			if (aiTimeLine_[iTime] == iWriting_)
				break;

		// shift other frames' ages
		for (int i = iTime - 1; i >= 0; --i)
			aiTimeLine_[i + 1] = aiTimeLine_[i];

		aiTimeLine_[0] = iWriting_;
		abInitialized_[iWriting_] = true;
		iWriting_ = FRAME_INVALID;
	}
}


template <class TContents>
bool kaynine::FrameBuffer<TContents>::lockReadable() const {
	AutoLock<CriticalSection> lock(&csIndexes_);

	if (iReading_ != FRAME_INVALID)
		return false;

	// pick newest
	for (int iTime = 0; iTime < NUM_FRAMES; ++iTime)
		if (aiTimeLine_[iTime] != iWriting_ && abInitialized_[aiTimeLine_[iTime]]) {
			iReading_ = aiTimeLine_[iTime];
			break;
		}

	return iReading_ != FRAME_INVALID;
}


template <class TContents>
const TContents* kaynine::FrameBuffer<TContents>::getReadable() const {
	AutoLock<CriticalSection> lock(&csIndexes_);

	if (iReading_ == FRAME_INVALID)
		return NULL;
	else
		return &contents_[iReading_];
}


template <class TContents>
void kaynine::FrameBuffer<TContents>::unlockReadable() const {
	AutoLock<CriticalSection> lock(&csIndexes_);

	iReading_ = FRAME_INVALID;
}


#endif //_KN_FRAME_BUFFER_INCLUDED_
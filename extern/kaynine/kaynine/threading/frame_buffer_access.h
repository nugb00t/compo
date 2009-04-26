/*******************************************************//**
	@file

	@brief	Shared memory area access template

	@author Andrew S. Gresyk

	@date	15.10.2006
*//********************************************************/
#ifndef _KN_FRAME_BUFFER_ACCESS_INCLUDED_
#define _KN_FRAME_BUFFER_ACCESS_INCLUDED_


// kaynine
#include "frame_buffer.h"


namespace kaynine {


/*******************************************************//**
	Framebuffer class
*//********************************************************/
template <class TContents>
class FrameBufferAccess : protected FrameBuffer<TContents> {
public:
	typedef typename FrameBuffer<TContents>::CONTENTS_TYPE CONTENTS_TYPE;


protected:
	template <class TContents> friend class WritableAccess;
	template <class TContents> friend class ReadableAccess;
};


/*******************************************************//**
	Writable Access class
*//********************************************************/
template <class TContents>
class WritableAccess {
public:
	typedef TContents		CONTENTS_TYPE;


public:
	explicit WritableAccess(FrameBufferAccess<TContents>& frameBuffer);
	~WritableAccess();
	void release();

	inline TContents& operator*();
	inline TContents* operator->();
	inline operator bool() const;


private:
	WritableAccess(const WritableAccess&);				// prohibited
	WritableAccess operator =(const WritableAccess&);	// prohibited


private:
	FrameBufferAccess<CONTENTS_TYPE>& frameBufferAccess_;
	bool bInitialized_;
};


/*******************************************************//**
	Readable Access class
*//********************************************************/
template <class TContents>
class ReadableAccess {
public:
	typedef TContents		CONTENTS_TYPE;


public:
	explicit ReadableAccess(const FrameBufferAccess<TContents>& frameBuffer);
	~ReadableAccess();
	void release();

	inline const TContents& operator*();
	inline const TContents* operator->();
	inline operator bool() const;


private:
	ReadableAccess(const ReadableAccess&);				// prohibited
	ReadableAccess operator =(const ReadableAccess&);	// prohibited


private:
	const FrameBufferAccess<CONTENTS_TYPE>& frameBufferAccess_;
	bool bInitialized_;
};


} //namespace kaynine


template <class TContents>
kaynine::WritableAccess<TContents>::WritableAccess(FrameBufferAccess<CONTENTS_TYPE>& frameBufferAccess) 
: frameBufferAccess_(frameBufferAccess), bInitialized_(frameBufferAccess_.lockWritable()) {}


template <class TContents>
kaynine::WritableAccess<TContents>::~WritableAccess() {
	release();
}


template <class TContents>
inline void kaynine::WritableAccess<TContents>::release() {
	if (bInitialized_)
		frameBufferAccess_.unlockWritable();
}


template <class TContents>
inline kaynine::WritableAccess<TContents>::operator bool() const {
	return bInitialized_;
}


template <class TContents>
inline TContents& kaynine::WritableAccess<TContents>::operator*() {
	TContents* ret = frameBufferAccess_.getWritable();
	assert(ret);
	return *ret;
}


template <class TContents>
inline TContents* kaynine::WritableAccess<TContents>::operator->() {
	TContents* ret = frameBufferAccess_.getWritable();
	assert(ret);
	return ret;
}


template <class TContents>
kaynine::ReadableAccess<TContents>::ReadableAccess(const FrameBufferAccess<CONTENTS_TYPE>& frameBufferAccess) 
: frameBufferAccess_(frameBufferAccess), bInitialized_(frameBufferAccess_.lockReadable()) {}


template <class TContents>
kaynine::ReadableAccess<TContents>::~ReadableAccess() {
	release();
}


template <class TContents>
inline void kaynine::ReadableAccess<TContents>::release() {
	if (bInitialized_)
		frameBufferAccess_.unlockReadable();
}


template <class TContents>
inline kaynine::ReadableAccess<TContents>::operator bool() const {
	return bInitialized_;
}


template <class TContents>
inline const TContents& kaynine::ReadableAccess<TContents>::operator*() {
	const TContents* ret = frameBufferAccess_.getReadable();
	assert(ret);
	return *ret;
}


template <class TContents>
inline const TContents* kaynine::ReadableAccess<TContents>::operator->() {
	const TContents* ret = frameBufferAccess_.getReadable();
	assert(ret);
	return ret;
}


#endif //_KN_FRAME_BUFFER_ACCESS_INCLUDED_
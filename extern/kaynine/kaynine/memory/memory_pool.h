#ifndef _KN_MEMORYPOOL_INCLUDED_
#define _KN_MEMORYPOOL_INCLUDED_

// crt
#include <assert.h>
// win
#include <tchar.h>

#include "../utility/singleton.h"

#ifdef K9_MEMORYPOOL_STATS
#include "../debug/logger.h"
#endif


#ifndef UNUSED
# define UNUSED(x)
#endif


namespace kaynine {


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MemoryPool class
//
// Uses two double-linked lists (one goes from the first to the last and the other maintains smallest-to-biggest chunks).
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MemoryPool {

#pragma pack(push, 4)
	struct Chunk {
		Chunk* next;
		Chunk* prev;
		Chunk* smaller;
		Chunk* bigger;

		inline void markOccupied() { smaller = bigger = this; }
		inline bool isOccupied() const { return this == smaller || this == bigger; }

		inline void* data() const { return (void*)((unsigned)this + sizeof(Chunk)); }
		inline unsigned dataSize() const { return next ? (next - this - 1) * sizeof(Chunk) : 0; }
	};
#pragma pack(pop)


public:
	MemoryPool(): data_(0), first_(0), last_(0), biggest_(0), smallest_(0) {}
	MemoryPool(const unsigned kbytes): data_(0), first_(0), last_(0), biggest_(0), smallest_(0) { reserve(kbytes); }
	~MemoryPool() { purge(); }

private:
	// disallow copy semantics
	MemoryPool(const MemoryPool&);
	MemoryPool& operator =(const MemoryPool&);

public:
	bool reserve(const unsigned kbytes);
	void purge();

	void* allocate(const unsigned bytes);
	void deallocate(void* data);

	unsigned inline maxSize() { return biggest_ ? biggest_->dataSize() : 0; }
	unsigned inline dataSize(const void* data) {
		assert(data_ && data);

		const Chunk* chunk = reinterpret_cast<const Chunk*>(data) - 1;
		assert(chunk >= first_ && chunk < last_);

		return chunk->dataSize(); 
	}


#ifdef K9_MEMORYPOOL_STATS
public:
	void logStructure(Logger& logger, bool contents = false, bool empty = false) const;
private:
	void logContents(Logger& logger, Chunk* chunk) const;
#endif


protected:
	inline static bool isAligned(const void* const p) { return isAligned((unsigned)p); }
	inline static bool isAligned(const unsigned p) { return p % sizeof(Chunk) == 0; }

private:
	inline Chunk* findFreeChunk(const unsigned bytes) const;

	inline void* alignDown(const unsigned p) const;
	inline void* alignUp(const unsigned p) const;
	inline void* alignUp(void* const p) const { return alignUp((unsigned)p); }

	inline void linkBySize(Chunk* chunk);
	inline void unlinkBySize(Chunk* chunk);


private:
	void* data_;
	// lists
	Chunk* first_;
	Chunk* last_;
	Chunk* biggest_;
	Chunk* smallest_;
};


} //namespace kaynine


#endif //_KN_MEMORYPOOL_INCLUDED_
#pragma once

#ifdef K9_MEMORYPOOL_STATS
#include "../debug/logger.h"
#endif

#include "../debug/macros.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Uses two double-linked lists (one goes from the first to the last and the other maintains smallest-to-biggest chunks).

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
	~MemoryPool() { discard(); }

private:
	// disallow copy semantics
	MemoryPool(const MemoryPool&);
	MemoryPool& operator =(const MemoryPool&);

public:
	bool reserve(const unsigned kbytes);
	void reset();
	void discard();

	void* allocate(const unsigned bytes);
	void deallocate(void* data);

	unsigned inline maxSize() { return biggest_ ? biggest_->dataSize() : 0; }
	unsigned inline dataSize(const void* data);


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
	DEBUG_ONLY(void checkStructure());

private:
	Chunk* findFreeChunk(const unsigned bytes) const;

	inline void* alignDown(const unsigned p) const;
	inline void* alignUp(const unsigned p) const;
	inline void* alignUp(void* const p) const { return alignUp((unsigned)p); }

	void linkBySize(Chunk* chunk);
	void unlinkBySize(Chunk* chunk);

private:
	void* data_;
	// lists
	Chunk* first_;
	Chunk* last_;
	Chunk* biggest_;
	Chunk* smallest_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned inline MemoryPool::dataSize(const void* data) {
	assert(data_ && data);

	const Chunk* chunk = reinterpret_cast<const Chunk*>(data) - 1;
	assert(chunk >= first_ && chunk < last_);

	return chunk->dataSize(); 
}

//---------------------------------------------------------------------------------------------------------------------

inline void* MemoryPool::alignDown(const unsigned p) const {
	assert(p);
	assert(data_);

	return isAligned(p) ? reinterpret_cast<void*>(p) : reinterpret_cast<void*>((p / sizeof(Chunk)) * sizeof(Chunk));
}

//---------------------------------------------------------------------------------------------------------------------

inline void* MemoryPool::alignUp(const unsigned p) const {
	assert(p);
	assert(data_);

	return isAligned(p) ? reinterpret_cast<void*>(p) : reinterpret_cast<void*>((p / sizeof(Chunk) + 1) * sizeof(Chunk));
}

//---------------------------------------------------------------------------------------------------------------------

} //namespace kaynine

#pragma once

#include <new>

#include "memory_pool.h"

#include "../utility/safe_bool.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PooledPtrBase {
public:
	virtual ~PooledPtrBase () {}

	inline void* operator new(size_t size, MemoryPool& pool) { return pool.allocate(size); }

	inline void operator delete(void* p, MemoryPool& pool)	 { pool.deallocate(p); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TInterface>
class PooledPtr {
public:
	inline PooledPtr() : t_(NULL), pool_(NULL) {}

	inline ~PooledPtr() { destroy(); }

	template <class T>
	inline void create(MemoryPool& pool) {
		assert(!t_ && !pool_);

		pool_ = pool;
		t_ = new (pool) T;
	}

	inline void destroy() {
		assert(t_ && pool_);

		t_->~PooledPtrBase();
		pool_->deallocate(t_);

		t_ = pool_ = NULL;
	}

		  TInterface& operator *()		 { return *t_; }
	const TInterface& operator *() const { return *t_; }

	//	  TInterface& operator ->()		  { return *t_; }
	//const TInterface& operator ->() const { return *t_; }

private:
	PooledPtrBase* t_;
	MemoryPool* pool_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

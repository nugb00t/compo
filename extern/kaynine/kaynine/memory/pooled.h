#ifndef _KN_POOLED_INCLUDED_
#define _KN_POOLED_INCLUDED_

#include <new>


#ifndef UNUSED
# define UNUSED(x)
#endif


namespace kaynine {


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base class for the objects created on MemoryPool
//
// Inherit from this class to allow creation on the pool
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TPool>
struct Pooled {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Implemented as inner class to have access to the Pooled::TPool type, since Allocator::T could differ from Pooled
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <class T>
	class Allocator {
		typedef Pooled<TPool> Outer;
	public:
		typedef T        value_type;
		typedef T*       pointer;
		typedef const T* const_pointer;
		typedef T&       reference;
		typedef const T& const_reference;
		typedef std::size_t    size_type;
		typedef std::ptrdiff_t difference_type;

		// rebind allocator to type U
		template <class U>
		struct rebind {
			typedef Allocator<U> other;
		};


	public:
		// return address of values
		pointer address (reference value) const { return &value; }
		const_pointer address (const_reference value) const { return &value; }

		// ctor / dtor
		Allocator() throw() {}

		Allocator(const Allocator&) throw() {}

		template <class U>
		Allocator (const Allocator<U>&) throw() {}

		~Allocator() throw() {}

		// return maximum number of elements that can be allocated
		size_type max_size() const throw() { return Outer::pool().maxSize() / sizeof(T); }

		// allocate but don't initialize num elements of type T
		pointer allocate(size_type num, const void* UNUSED(hint) = 0) {
			pointer p = reinterpret_cast<pointer>(Outer::pool().allocate(num * sizeof(T)));

			if (!p)
				throw std::bad_alloc();

			return p;
		}

		// initialize elements of allocated storage p with value value
		void construct(pointer p, const T& value) {
			::new (p) T(value);
		}

		// destroy elements of initialized storage p
		void destroy(pointer p) { p->~T(); }

		// deallocate storage p of deleted elements
		void deallocate(pointer p, size_type num) {
			assert(num * sizeof(T) <= Outer::pool().dataSize(p));
			Outer::pool().deallocate(p);
		}
	};

	typedef Pooled<TPool> ThisClass;


	static TPool& pool() { return Singleton<TPool>::inst(); }

	void* operator new(size_t size) { return pool().allocate(size); }

	void operator delete(void* p) {
		reinterpret_cast<ThisClass*>(p)->~ThisClass();
		return pool().deallocate(p); 
	}
};


//==============================================================================================================================================
// return that all specializations of this allocator are interchangeable 
//==============================================================================================================================================
template <class P1, class P2, class T1, class T2>
bool operator== (const typename Pooled<P1>::Allocator<T1>&, const typename Pooled<P2>::Allocator<T2>&) throw() { return true; }

template <class P1, class P2, class T1, class T2>
bool operator!= (const typename Pooled<P1>::Allocator<T1>&, const typename Pooled<P2>::Allocator<T2>&) throw() { return false; }


} //namespace kaynine


#endif // _KN_POOLED_INCLUDED_
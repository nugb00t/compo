#ifndef _KN_REFCOUNTED_INCLUDED_
#define _KN_REFCOUNTED_INCLUDED_


namespace kaynine {


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Strategy implementing support for boost::intrusive_ptr via reference count
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RefCounted {
public:
	RefCounted() : refs_(0) {}
	virtual ~RefCounted() { assert(!refs_); }

private:
	unsigned refs_;

	friend void intrusive_ptr_add_ref(RefCounted* p) { assert(p); ++p->refs_; }
	friend void intrusive_ptr_release(RefCounted* p) { assert(p); if (--p->refs_ <= 0) delete p; }
};


} //namespace kaynine


#endif //_KN_REFCOUNTED_INCLUDED_
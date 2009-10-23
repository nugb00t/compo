#ifndef KN_INTRUSIVE_PTR_BASE_INCLUDED
#define KN_INTRUSIVE_PTR_BASE_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace kaynine {
	class IntrusivePtrBase;
}

inline void intrusive_ptr_add_ref(class kaynine::IntrusivePtrBase* ptr);
inline void intrusive_ptr_release(class kaynine::IntrusivePtrBase* ptr);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace kaynine {

class IntrusivePtrBase
{
public:
enum AutoDeleteStrategy {
	NoAutoDelete
};

protected:
	inline IntrusivePtrBase() : refs_(0), autoDelete_(true) {}
	inline IntrusivePtrBase(AutoDeleteStrategy) : refs_(0), autoDelete_(false) {}
	virtual ~IntrusivePtrBase() {}

public:
	inline int refs() const { return refs_; }
	inline bool isAutoDelete() const { return autoDelete_; }

protected:
	inline void setAutoDelete(bool autoDelete) { autoDelete_ = autoDelete; }

private:
	unsigned refs_;
	bool autoDelete_;

	friend inline void ::intrusive_ptr_add_ref(IntrusivePtrBase*);
	friend inline void ::intrusive_ptr_release(IntrusivePtrBase*);
};

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void intrusive_ptr_add_ref(kaynine::IntrusivePtrBase* ptr) {
	++ptr->refs_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void intrusive_ptr_release(kaynine::IntrusivePtrBase* ptr) {
	if (!--ptr->refs_ && ptr->autoDelete_) {
		delete ptr;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

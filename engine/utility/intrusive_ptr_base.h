#ifndef INTRUSIVE_PTR_BASE_INCLUDED
#define INTRUSIVE_PTR_BASE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IntrusivePtrBase;

void intrusive_ptr_add_ref(IntrusivePtrBase*);
void intrusive_ptr_release(IntrusivePtrBase*);

enum AutoDeleteStrategy {
	NoAutoDelete
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IntrusivePtrBase
{
protected:
	IntrusivePtrBase() : refs_(0), autoDelete_(true) {}
	IntrusivePtrBase(AutoDeleteStrategy) : refs_(0), autoDelete_(false) {}
	virtual ~IntrusivePtrBase() {}

public:
	int refs() const { return refs_; }
	bool isAutoDelete() const { return autoDelete_; }

protected:
	void setAutoDelete(bool autoDelete) { autoDelete_ = autoDelete; }

private:
	unsigned refs_;
	bool autoDelete_;

	friend void intrusive_ptr_add_ref(IntrusivePtrBase*);
	friend void intrusive_ptr_release(IntrusivePtrBase*);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif

#pragma once

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Safe Bool idiom by Bjorn Karlsson
//
//	Here's how to use SafeBool: 
//
//	class Testable_with_virtual : public SafeBool<> {
//	protected:
//		bool boolean_test() const {
//			// Perform Boolean logic here
//		}
//	};
//
//	class Testable_without_virtual : 
//		public SafeBool <Testable_without_virtual> {
//	public:
//		bool boolean_test() const {
//			// Perform Boolean logic here
//		}
//	};
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SafeBoolBase {
public:
	void this_type_does_not_support_comparisons() const {}

protected:
	typedef void (SafeBoolBase::*bool_type)() const;

	SafeBoolBase() {}
	SafeBoolBase(const SafeBoolBase&) {}
	SafeBoolBase& operator=(const SafeBoolBase&) {return *this;}
	virtual ~SafeBoolBase() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T = void> 
class SafeBool : public SafeBoolBase {
public:
	operator bool_type() const {
		return (static_cast<const T*>(this))->boolean_test() ?
			&SafeBoolBase::this_type_does_not_support_comparisons : 0;
	}

protected:
	virtual ~SafeBool() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<> 
class SafeBool<void> : public SafeBoolBase {
public:
	operator bool_type() const {
		return boolean_test() == true ? 
			&SafeBoolBase::this_type_does_not_support_comparisons : 0;
	}

protected:
	virtual bool boolean_test() const = 0;
	virtual ~SafeBool() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U> 
void operator==(const SafeBool<T>& lhs,const SafeBool<U>& rhs) {
	lhs.this_type_does_not_support_comparisons();	
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T,typename U> 
void operator!=(const SafeBool<T>& lhs,const SafeBool<U>& rhs) {
	lhs.this_type_does_not_support_comparisons();
	return false;	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

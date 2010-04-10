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

class safe_bool_base {
public:
	void this_type_does_not_support_comparisons() const {}

protected:
	typedef void (safe_bool_base::*bool_type)() const;

	safe_bool_base() {}
	safe_bool_base(const safe_bool_base&) {}
	safe_bool_base& operator=(const safe_bool_base&) {return *this;}
	virtual ~safe_bool_base() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T = void> 
class SafeBool : public safe_bool_base {
public:
	operator bool_type() const {
		return (static_cast<const T*>(this))->boolean_test() ?
			&safe_bool_base::this_type_does_not_support_comparisons : 0;
	}

protected:
	virtual ~SafeBool() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<> 
class SafeBool<void> : public safe_bool_base {
public:
	operator bool_type() const {
		return boolean_test() == true ? 
			&safe_bool_base::this_type_does_not_support_comparisons : 0;
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

/*******************************************************//**

 @file

 @author Andrew 'nugb00t' Gresyk

 @date 2007-07-02

*//********************************************************/
#ifndef _KN_MATH_INCLUDED_
#define _KN_MATH_INCLUDED_

#include <assert.h>


namespace kaynine {


template <typename T>
inline void clamp(T& operand, const T& lowBound, const T& highBound) {
	assert(lowBound < highBound);
	if (operand < lowBound)
		operand = lowBound;
	if (operand > highBound)
		operand = highBound;
}


} // namespace kaynine


#endif //_KN_MATH_INCLUDED_
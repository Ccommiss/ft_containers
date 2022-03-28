# include "includes.hpp"

#ifndef RELATIONNAL_TOOLS_HPP 
#define RELATIONNAL_TOOLS_HPP 
namespace ft {
/*
**	lexicographical_compare : < 
**	@brief Lexicographical less-than comparison 
**	
** 	@returns  Returns true if the range [first1,last1) 
**	compares lexicographically less than the range [first2,last2).
*/
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1) return false;
		else if (*first1 < *first2) return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}


/*
**	Equal : == 
**	@brief Test whether the elements in two ranges are equal
**	@param first1,last1 Input iterators to the initial and final positions 
**	of the first sequence. 
**	@details The range used is [first1,last1), which contains 
**	all the elements between first1 and last1, including the element pointed 
**	by first1 but not the element pointed by last1.
**	@param Input iterator to the initial position of the second sequence. The comparison includes up to as many elements of this sequence as those in the range [first1,last1).
** 	@returns true if first1 == first 2
*/
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1) {
		if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
			return false;
		++first1; ++first2;
	}
	return true;
}

}

#endif
#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include "includes.hpp"


/**
 *  @brief  Common %iterator class.
 *
 *  This class does nothing but define nested typedefs.  %Iterator classes
 *  can inherit from this class to save some work.  The typedefs are then
 *  used in specializations and overloading.
 *
 *  In particular, there are no default implementations of requirements
 *  such as @c operator++ and the like.  (How could there be?)
 */
namespace ft {

		//@{
	  /**
	   *  @defgroup iterator_tags Iterator Tags
	   *  These are empty types, used to distinguish different iterators.  The
	   *  distinction is not made by what they contain, but simply by what they
	   *  are.  Different underlying algorithms can then be used based on the
	   *  different operations supported by different iterator types.
	  */
	  ///  Marking input iterators.
	struct input_iterator_tag {};
	///  Marking output iterators.
	struct output_iterator_tag {};
	/// Forward iterators support a superset of input iterator operations.
	struct forward_iterator_tag : public input_iterator_tag {};
	/// Bidirectional iterators support a superset of forward iterator
	/// operations.
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	/// Random-access iterators support a superset of bidirectional iterator
	/// operations.
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	//@}


	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

}

#endif 
#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>

/*
** 
**  @brief  Common iterator class.
**
**  This class does nothing but define nested typedefs.  Iterator classes
**  can inherit from this class to save some work.  The typedefs are then
**  used in specializations and overloading.
**
**  In particular, there are no default implementations of requirements
**  such as @c operator++ and the like.  (How could there be?)
** 
*/
namespace ft {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T 			value_type;
		typedef Distance 	difference_type;
		typedef Pointer 	pointer;
		typedef Reference 	reference;
		typedef Category 	iterator_category;
	};

}

#endif

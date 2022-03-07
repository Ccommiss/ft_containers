
#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "includes.hpp"


#include <allocator>


struct bidirectional_iterator_tag {}


template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector {

		public:
		vector(); 
		vector(const allocator_type& __a): _Base(__a) { }
		vector(size_type __n): _Base(__n) { _M_default_initialize(__n); }
		~vector();

		typedef T value_type; // alais 
		typedef Alloc allocator_type; //alias 
		typedef allocator_type::reference reference; // &T 
		typedef allocator_type::const_reference const_referenc; // const &T 
		typedef allocator_type::pointer pointer; // T* 
		typedef allocator_type::const_pointer const_pointer;
		/* Les iterateurs */ 
		typedef ft::random_access_iterator<value_type> iterator; 
		typedef ft::random_access_iterator<const value_type> iterator;
		/* Diff type & size_type */ 
		typedef iterators_traits<iterator>::difference_type difference_type;
		typedef allocator_type::size_type size_type; // std::allocator, vaut siz_t 

		iterator	begin() { return iterator(this->_curr[0]); } };

		private: 
			pointer _curr;
	};
}

# endif
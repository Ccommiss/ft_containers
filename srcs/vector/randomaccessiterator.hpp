
#include "includes.hpp"

#ifndef RANDOM_ACCESS_ITERATORS_HPP
# define RANDOM_ACCESS_ITERATORS_HPP

// https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator.h.html#__gnu_cxx::__normal_iterator 

namespace ft
{
	template <typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		// Ici on herite de la cat generique iterator, avec le tag random access
		public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 			difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type	     		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference 		 		reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category 		iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer 					pointer;

		private:

		pointer _curr; // correspond a  T* 

		public:

		random_access_iterator() : _curr(0) { };
		random_access_iterator(T* rhs) : _curr(rhs) { };
		random_access_iterator(const T* rhs) : _curr(rhs) {  };
		random_access_iterator(const random_access_iterator& rhs) : _curr(rhs._curr) { };
		random_access_iterator(random_access_iterator& rhs) : _curr(rhs._curr) {};



		T* base() const
		{
			return _curr;
		}

		/*
		** 		Pointer like operators
		*/
		reference		operator*() { return *_curr; }
		const T* operator->() const throw() { return _curr; }
		reference operator[](difference_type off) const { return _curr[off]; }
		// /* ARITHMETIQUES */
		/* a + b */ difference_type operator+(const random_access_iterator& rhs) const { return (this->_curr + rhs.base()); }
		/* a + n */ random_access_iterator operator+(const difference_type step) const { return (this->_curr + step); }
		/* TEST*/	random_access_iterator operator+(difference_type step) { return random_access_iterator(_curr + step); } // + step); }

		/* a - b */ difference_type operator-(const random_access_iterator& rhs) const { return (this->_curr - rhs.base()); }
		/* a - n */ random_access_iterator operator-(const difference_type step) const { return random_access_iterator(_curr - step); }
		/* a += n */ random_access_iterator& operator+=(const difference_type step) { this->_curr += step; return *this; }
		/* a -= n */ random_access_iterator& operator-=(const difference_type step) { this->_curr -= step; return *this; }
		/* b = a */ random_access_iterator& operator=(const random_access_iterator& rhs) { this->_curr = rhs._curr; return *this; }

		// /*POINTER OP*/
		random_access_iterator& operator--() { --_curr; return *this; }
		/* ++a */ random_access_iterator& operator++() { ++_curr; return *this; }
		random_access_iterator operator--(int) { random_access_iterator tmp(*this); --(*this); return tmp; }
		/* a++ */ random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++(*this); return tmp; }

		// /* COMPARISONS */
		bool operator<(const random_access_iterator& rhs) { return this->_curr < rhs._curr; }
		bool operator<=(const random_access_iterator& rhs) { return this->_curr <= rhs._curr; }
		bool operator>(const random_access_iterator& rhs) { return this->_curr > rhs._curr; }
		bool operator>=(const random_access_iterator& rhs) { return this->_curr >= rhs._curr; }
		bool operator==(const random_access_iterator& rhs) const { return _curr == rhs._curr; }
		bool operator!=(const random_access_iterator& rhs) const { return _curr != rhs._curr; }

	};
	/* n + a */
	// template <typename T>
	// random_access_iterator<T>   operator+(typename ft::random_access_iterator<T>::difference_type n, random_access_iterator<T> a) { return (a + n); }

	// /*a - b*/
	// template <typename T>
	// typename ft::random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return lhs.base() - rhs.base(); }
}

#endif
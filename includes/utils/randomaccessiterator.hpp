


#ifndef RANDOM_ACCESS_ITERATORS_HPP
# define RANDOM_ACCESS_ITERATORS_HPP

# include "iterator.hpp"
# include <cstddef>

// https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator.h.html#__gnu_cxx::random_access_iterator


template <class T>
struct iterator_traits;


namespace ft
{


	template <typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 			difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type	     		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference 		 		reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category 		iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer 					pointer;

		private:
		/*
		** _curr
		*/
		pointer _curr; // correspond a  T*

		public:

		/*
		**	Contructors
		*/
		/* Default 	*/ 	random_access_iterator() : _curr(0) { };
		/* Copy 	*/	random_access_iterator(T* rhs) : _curr(rhs) { };
		/* Copy 	*/	random_access_iterator(const random_access_iterator& rhs) : _curr(rhs._curr) { };


		/*
		**	base
		**	@brief returns a pointer on the stored object
		*/
		pointer base() const { return _curr; }

		/*
		** 		Pointer like operators
		*/
		/* *a 	*/	reference		operator*() const { return *_curr; }
		/* a->m */	pointer 		operator->() const { return &(operator*()); }
		/* a[i] */	reference		operator[](difference_type off) const { return _curr[off]; }


		/*
		** 		Arithmetic operations
		*/

		/*
		**	Between iterator and integer value
		*/
		/* a + n */	random_access_iterator operator+(const difference_type step) const { return random_access_iterator(_curr + step); } // ajout menage 
		/* n + a : see non-member */
		/* a - n */ random_access_iterator operator-(const difference_type step) const { return random_access_iterator(_curr - step); }

		/*
		** Between two iterators
		*/
		/* a + b */ difference_type operator+(const random_access_iterator& rhs) const { return (_curr + rhs.base()); }
		/* a - b */ difference_type operator-(const random_access_iterator& rhs) const { return (this->_curr - rhs.base()); }

		/*
		**	Compound assignement operations +- and -=
		*/
		/* a += n */ random_access_iterator& operator+=(const difference_type step) { this->_curr += step; return *this; }
		/* a -= n */ random_access_iterator& operator-=(const difference_type step) { this->_curr -= step; return *this; }
		/* b = a */ random_access_iterator& operator=(const random_access_iterator& rhs) { this->_curr = rhs._curr; return *this; }


		/*
		** 		Pointer operations : incrementations and decrementations
		*/
		/* --a */ random_access_iterator& operator--() { --_curr; return *this; }
		/* ++a */ random_access_iterator& operator++() { ++_curr; return *this; }
		/* a-- */ random_access_iterator operator--(int) { random_access_iterator tmp(*this); --(*this); return tmp; }
		/* a++ */ random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++(*this); return tmp; }

		/*
		** 		Comparisons (see also non-member comparisons)
		*/
		bool operator<(const random_access_iterator& rhs) const { return this->_curr < rhs._curr; }
		bool operator<=(const random_access_iterator& rhs) const { return this->_curr <= rhs._curr; }
		bool operator>(const random_access_iterator& rhs) const { return this->_curr > rhs._curr; }
		bool operator>=(const random_access_iterator& rhs) const { return this->_curr >= rhs._curr; }
		bool operator==(const random_access_iterator& rhs) const { return _curr == rhs._curr; }
		bool operator!=(const random_access_iterator& rhs) const { return _curr != rhs._curr; }

		operator random_access_iterator<const T>() const
		{
			return (random_access_iterator<const T>(_curr)); // cast en const
		}

	};

	template<typename _IteratorL, typename _IteratorR>
	inline bool operator==(const random_access_iterator<_IteratorL >& lhs, const random_access_iterator<_IteratorR  >& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template<typename _Iterator   >
	inline bool operator==(const random_access_iterator<_Iterator  >& lhs, const random_access_iterator<_Iterator  >& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template<typename _IteratorL, typename _IteratorR   >
	inline bool operator!=(const random_access_iterator<_IteratorL  >& lhs, const random_access_iterator<_IteratorR  >& rhs)
	{
		return lhs.base() != rhs.base();
	}
	template<typename _Iterator   >
	inline bool operator!=(const random_access_iterator<_Iterator  >& lhs, const random_access_iterator<_Iterator  >& rhs)
	{
		return lhs.base() != rhs.base();
	}

	// Random access iterator requirements
	template<typename _IteratorL, typename _IteratorR   >
	inline bool operator<(const random_access_iterator<_IteratorL  >& lhs, const random_access_iterator<_IteratorR  >& rhs)
	{
		return lhs.base() < rhs.base();
	}
	template<typename _Iterator   >
	inline bool operator<(const random_access_iterator<_Iterator  >& lhs, const random_access_iterator<_Iterator  >& rhs)
	{
		return lhs.base() < rhs.base();
	}
	template<typename _IteratorL, typename _IteratorR   >
	inline bool operator>(const random_access_iterator<_IteratorL  >& lhs, const random_access_iterator<_IteratorR  >& rhs)
	{
		return lhs.base() > rhs.base();
	}
	template<typename _Iterator   >
	inline bool operator>(const random_access_iterator<_Iterator  >& lhs, const random_access_iterator<_Iterator  >& rhs)
	{
		return lhs.base() > rhs.base();
	}
	template<typename _IteratorL, typename _IteratorR   >
	inline bool operator<=(const random_access_iterator<_IteratorL  >& lhs, const random_access_iterator<_IteratorR  >& rhs)
	{
		return lhs.base() <= rhs.base();
	}
	template<typename _Iterator   >
	inline bool operator<=(const random_access_iterator<_Iterator  >& lhs,
		const random_access_iterator<_Iterator  >& rhs)
	{
		return lhs.base() <= rhs.base();
	}
	template<typename _IteratorL, typename _IteratorR   >
	inline bool operator>=(const random_access_iterator<_IteratorL  >& lhs,
		const random_access_iterator<_IteratorR  >& rhs)
	{
		return lhs.base() >= rhs.base();
	}
	template<typename _Iterator   >
	inline bool operator>=(const random_access_iterator<_Iterator  >& lhs, const random_access_iterator<_Iterator  >& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<typename _IteratorL, typename _IteratorR >
	inline typename random_access_iterator<_IteratorL  >::difference_type operator-(const random_access_iterator<_IteratorL  >& lhs, const random_access_iterator<_IteratorR  >& rhs)
	{
		return lhs.base() - rhs.base();
	}

	template<typename _Iterator   >
	inline typename random_access_iterator<_Iterator  >::difference_type operator-(const random_access_iterator<_Iterator  >& lhs, const random_access_iterator<_Iterator  >& rhs)
	{
		return lhs.base() - rhs.base();
	}
	template<typename _Iterator   >
	inline random_access_iterator<_Iterator  > operator+(typename random_access_iterator<_Iterator  >::difference_type n, const random_access_iterator<_Iterator  >& rit)
	{
		return random_access_iterator<_Iterator  >(rit.base() + n);
	}

}

#endif

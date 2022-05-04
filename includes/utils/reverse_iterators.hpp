
# ifndef reverse_random_access_iteratorS_HPP
# define reverse_random_access_iteratorS_HPP

# include "iterator_traits.hpp"

/*	 +---+---+---+---+---+---+---+
**	 |   | 1 | 2 | 3 | 4 | 5 |   |
**	 +---+---+---+---+---+---+---+
**	   ↑   ↑   ↑   ↑
**	   |   |   |   |
**	rend() |     rbegin()  end()
**	   |       rbegin().base()
**	 begin()
**	 rend().base()
**		 rend() - 1
*/


namespace ft
{
	template <class U>
	struct iterator_traits;

	template <typename T>
	class reverse_iterator : public ft::iterator <typename iterator_traits<T>::iterator_category, typename iterator_traits< T>::value_type, typename iterator_traits< T>::difference_type,
		typename iterator_traits< T>::pointer, typename iterator_traits< T>::reference>
	{
		public:
		typedef ft::iterator_traits<T>                			__traits_type;
		typedef T                                   			iterator_type;
		typedef typename __traits_type::difference_type        	difference_type;
		typedef typename __traits_type::pointer                	pointer;
		typedef typename __traits_type::reference               reference;

		protected:
		iterator_type _curr;

		public:


		/*
		**	Contructors
		*/

		/* Default 	*/ 	reverse_iterator() : _curr(0) {};
		/* From rhs	*/	explicit reverse_iterator(iterator_type rhs) : _curr(rhs) {};
		/* Copy 	*/	reverse_iterator(const reverse_iterator& rhs) : _curr(rhs._curr) {};
		/* Overload from another type */ template<typename _Iter> reverse_iterator(const reverse_iterator<_Iter>& lhs) : _curr(lhs.base()) { }

		/*
		**	base
		**	@brief returns the underlying base iterator
		*/
		iterator_type base() const { return _curr; }

		/*
		**	Pointer like operators
		*/
		/* *a 	*/	reference		operator*() const { iterator_type __tmp = _curr; return *--__tmp; }
		/* a->m */	const pointer	operator->() const { return &(operator*()); }
		/* a[i] */	reference 		operator[](difference_type off) const { return *(*this + off); }

		/*
		** 		Arithmetic operations
		*/
		/* a + n */	 reverse_iterator operator+(const difference_type step) const { return reverse_iterator(_curr - step); }
		/* a - n */  reverse_iterator operator-(const difference_type step) const { return reverse_iterator(_curr + step); }
		/* a += n */ reverse_iterator& operator+=(const difference_type step) { _curr -= step; return *this; }
		/* a -= n */ reverse_iterator& operator-=(const difference_type step) { _curr += step; return *this; }

		/*
		**	Pointer like operators
		*/
		reverse_iterator& operator--() { ++_curr; return *this; }
		reverse_iterator& operator++() { --_curr; return *this; }
		reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++_curr; return tmp; }
		reverse_iterator operator++(int) { reverse_iterator tmp(*this); --_curr; return tmp; }

		/*
		**	Arithmetic comparisons
		*/
		inline bool operator<(const reverse_iterator& rhs) const { return _curr > rhs._curr; }
		inline bool operator<=(const reverse_iterator& rhs) const { return _curr >= rhs._curr; }
		inline bool operator>(const reverse_iterator& rhs) const { return rhs._curr > _curr; }
		inline bool operator>=(const reverse_iterator& rhs) const { return _curr <= rhs._curr; }
		inline bool operator==(const reverse_iterator& rhs) const { return _curr == rhs._curr; }
		inline bool operator!=(const reverse_iterator& rhs) const { return _curr != rhs._curr; }

		operator reverse_iterator<const T>() const
		{
			return (reverse_iterator<const T >(_curr));
		}
	};

	/*
	**	Relationnal op : non-members function overload
	*/
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator==(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator!=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
	{
		return !(lhs == rhs);
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator<(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
	{
		return rhs.base() < lhs.base();
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator>(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
	{
		return rhs < lhs;
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator<=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
	{
		return !(rhs < lhs);
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator>=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
	{
		return !(lhs < rhs);
	}
	// a + n
	template<typename _Iterator>
	reverse_iterator<_Iterator> operator+(typename reverse_iterator<_Iterator>::difference_type __n, const reverse_iterator<_Iterator>& lhs)
	{
		return reverse_iterator<_Iterator>(lhs.base() - __n);
	}
	template <class L_Iterator, class R_Iterator>
	typename reverse_iterator<L_Iterator>::difference_type operator-(const reverse_iterator<L_Iterator>& lhs, const reverse_iterator<R_Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

}

#endif

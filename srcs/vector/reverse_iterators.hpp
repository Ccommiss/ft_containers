

# ifndef reverse_random_access_iteratorS_HPP
# define reverse_random_access_iteratorS_HPP

#include "includes.hpp"

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
	template <typename T>
	class reverse_random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 			difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type	 			value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference 		 		reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category 		iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer 					pointer;

		private:
		pointer _curr;

		public:


/*
**	Default constructor 
*/
		reverse_random_access_iterator() : _curr(0) {};

/*
**	 constructor 
*/
		reverse_random_access_iterator(T* rhs) : _curr(rhs) {};

/*
**	Copy constructor 
*/
		reverse_random_access_iterator(const reverse_random_access_iterator& rhs) : _curr(rhs._curr) {};

		/*
		**	@brief A reverse_iterator across other types can be copied if the
		**	underlying %iterator can be converted to the type of @c current.
		**	@tparam the type of other iterator
		*/
		template<typename _Iter>
		reverse_random_access_iterator(const reverse_random_access_iterator<_Iter>& __x) : _curr(__x.base()) { }

		pointer base() const
		{
			return _curr;
		}

		/*
		**	Pointer like operators
		*/
		reference		operator*()
		{
			pointer __tmp = _curr;
			return *--__tmp;
		}
		const pointer operator->() const throw() { return _curr; }
		reference operator[](difference_type off) const { return _curr[off]; }

		// /* ARITHMETIQUES */
		/* a + b */ difference_type operator+(const reverse_random_access_iterator& rhs) const { return (this->_curr + rhs.base()); }
		/* a + n */ reverse_random_access_iterator operator+(const difference_type step) const { return reverse_random_access_iterator(_curr - step); }
		/* TEST */	reverse_random_access_iterator operator+(difference_type step) { return reverse_random_access_iterator(_curr - step); } // + step); }

		/* a - b */ difference_type operator-(const reverse_random_access_iterator& rhs) const { return (this->_curr - rhs.base()); }
		/* a - n */ reverse_random_access_iterator operator-(const difference_type step) const { return reverse_random_access_iterator(_curr + step); }
		/* TEST */ reverse_random_access_iterator operator-(difference_type step) { return reverse_random_access_iterator(_curr + step); }

		/* a += n */ reverse_random_access_iterator& operator+=(const difference_type step) { this->_curr -= step; return *this; }
		/* a -= n */ reverse_random_access_iterator& operator-=(const difference_type step) { this->_curr += step; return *this; }
		/* b = a */ reverse_random_access_iterator& operator=(const reverse_random_access_iterator& rhs) { this->_curr = rhs._curr; return *this; }

		/*
		**	Pointer like operators
		*/
		reverse_random_access_iterator& operator--() { ++_curr; return *this; }
		/* ++a */ reverse_random_access_iterator& operator++() { --_curr; return *this; }
		reverse_random_access_iterator operator--(int) { reverse_random_access_iterator tmp(*this); ++_curr; return tmp; }
		/* a++ */ reverse_random_access_iterator operator++(int) { reverse_random_access_iterator tmp(*this); --_curr; return tmp; }


		/* COMPARISONS */
		bool operator<(const reverse_random_access_iterator& rhs) const { return this->_curr > rhs._curr; }
		bool operator<=(const reverse_random_access_iterator& rhs) const { return this->_curr >= rhs._curr; }
		bool operator>(const reverse_random_access_iterator& rhs)const { return rhs._curr > this->_curr; }
		bool operator>=(const reverse_random_access_iterator& rhs) const { return this->_curr <= rhs._curr; }
		bool operator==(const reverse_random_access_iterator& rhs) const { return _curr == rhs._curr; }
		bool operator!=(const reverse_random_access_iterator& rhs) const { return _curr != rhs._curr; }


		operator reverse_random_access_iterator<const T>() const
		{
			return (reverse_random_access_iterator<const T >(this->_curr));
		}
	};


	template<typename _IteratorL, typename _IteratorR>
	inline bool operator==(const reverse_random_access_iterator<_IteratorL>& __x, const reverse_random_access_iterator<_IteratorR>& __y)
	{
		return __x.base() == __y.base();
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator!=(const reverse_random_access_iterator<_IteratorL>& __x,
		const reverse_random_access_iterator<_IteratorR>& __y)
	{
		return !(__x == __y);
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator<(const reverse_random_access_iterator<_IteratorL>& __x,
		const reverse_random_access_iterator<_IteratorR>& __y)
	{
		return __y.base() < __x.base();
	}
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator>(const reverse_random_access_iterator<_IteratorL>& __x,
		const reverse_random_access_iterator<_IteratorR>& __y)
	{
		return __y < __x;
	}
	template<typename _IteratorL, typename _IteratorR>
	inline   bool
		operator<=(const reverse_random_access_iterator<_IteratorL>& __x,
			const reverse_random_access_iterator<_IteratorR>& __y)
	{
		return !(__y < __x);
	}
	template<typename _IteratorL, typename _IteratorR>
	inline   bool
		operator>=(const reverse_random_access_iterator<_IteratorL>& __x,
			const reverse_random_access_iterator<_IteratorR>& __y)
	{
		return !(__x < __y);
	}
	// a + n  
	template<typename _Iterator>
	typename reverse_random_access_iterator<_Iterator>::difference_type
		operator+(typename reverse_random_access_iterator<_Iterator>::difference_type __n,
			const reverse_random_access_iterator<_Iterator>& __x)
	{
		return reverse_random_access_iterator<_Iterator>(__x.base() - __n);
	}

	template<typename _IteratorL, typename _IteratorR>
	typename reverse_random_access_iterator<_IteratorL>::difference_type
		operator-(const reverse_random_access_iterator<_IteratorL>& __x,
			const reverse_random_access_iterator<_IteratorR>& __y)
	{
		return __y.base() - __x.base();
	}

}



#endif

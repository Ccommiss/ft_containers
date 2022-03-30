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
	template <class U>
	struct iterator_traits;

	template <typename T>
	class reverse_random_access_iterator : public ft::iterator
					<typename iterator_traits<T>::iterator_category,
                      typename iterator_traits< T>::value_type,
                      typename iterator_traits< T>::difference_type,
                      typename iterator_traits< T>::pointer,
                      typename iterator_traits< T>::reference>
	{
		public:
		typedef ft::iterator_traits<T>                			__traits_type;
		typedef T                                   			iterator_type;
		typedef typename __traits_type::difference_type        	difference_type;
		typedef typename __traits_type::pointer                	pointer;
		typedef typename __traits_type::reference               reference;

		private:
		iterator_type _curr;

		public:


		/*
		**	Default constructor
		*/
		reverse_random_access_iterator() : _curr(0) {};

		/*
		**	 constructor
		*/
		reverse_random_access_iterator(iterator_type rhs) : _curr(rhs) {};

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

		iterator_type base() const
		{
			return _curr;
		}

		/*
		**	Pointer like operators
		*/
		reference		operator*() const
		{
			iterator_type __tmp = _curr;
			return *--__tmp;
		}
		const pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type off) const { return *(*this + off); }

		// /* ARITHMETIQUES */
		/* a + b */ difference_type operator+(const reverse_random_access_iterator& rhs) const { return (this->_curr - rhs.base()); }
		/* a + n */ reverse_random_access_iterator operator+(const difference_type step) const { return reverse_random_access_iterator(_curr - step); }
		/* TEST */	reverse_random_access_iterator operator+(difference_type step) { return reverse_random_access_iterator(_curr - step); } // + step); }

		/* a - b */ difference_type operator-(const reverse_random_access_iterator& rhs) const { return (this->_curr + rhs.base()); }
		/* a - n */ reverse_random_access_iterator operator-(const difference_type step) const { return reverse_random_access_iterator(_curr + step); }
		/* TEST */ reverse_random_access_iterator operator-(difference_type step) { return reverse_random_access_iterator(_curr + step); }

		/* a += n */ reverse_random_access_iterator& operator+=(const difference_type step) { this->_curr -= step; return *this; }
		/* a -= n */ reverse_random_access_iterator& operator-=(const difference_type step) { this->_curr += step; return *this; }
		/* b = a */ 
		reverse_random_access_iterator& operator=(const reverse_random_access_iterator& rhs) 
		{ 
			this->_curr = rhs._curr; 
			return *this; 
		}

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
	reverse_random_access_iterator<_Iterator>
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

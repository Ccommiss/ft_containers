

# ifndef REVERSE_ITERATORS_HPP
# define REVERSE_ITERATORS_HPP

#include "includes.hpp"

/*	 +---+---+---+---+---+---+---+
**	 |   | 1 | 2 | 3 | 4 | 5 |   |
**	 +---+---+---+---+---+---+---+
**	   ↑   ↑               ↑   ↑
**	   |   |               |   |
**	rend() |         rbegin()  end()
**	       |                   rbegin().base()
**	     begin()
**	     rend().base()
**		 rend() - 1
*/


namespace ft
{
	template <typename T>
	class reverse_random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
		// Ici on herite de la cat generique iterator, avec le tag random access
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type 			difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type	     		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference 		 		reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category 		iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer 					pointer;

	private:
		pointer _curr;

	public:

		reverse_random_access_iterator() : _curr(0) {debug ("hey reverse");};
		reverse_random_access_iterator(T* rhs) : _curr(rhs) {};
		//random_access_iterator(const random_access_iterator& rhs) : _curr(rhs._curr) {};



		pointer base() const
		{
			return _curr;
		}

		// // Pointer like operators
		reference		operator*()
		{
			pointer __tmp = _curr;
			return *--__tmp;
		}
		//const pointer operator->() const throw() { return _curr; }
		// reference operator[](difference_type off) const { return _curr[off]; }
		// /* ARITHMETIQUES */
		/* a + b */ difference_type operator+(const reverse_random_access_iterator& rhs) const { return (this->_curr + rhs.base()); }
		/* a + n */ reverse_random_access_iterator operator+(const difference_type step) const {  return reverse_random_access_iterator(_curr - step); }
		/* TEST */	reverse_random_access_iterator operator+(difference_type step) { return reverse_random_access_iterator(_curr - step); } // + step); }

		/* a - b */ difference_type operator-(const reverse_random_access_iterator& rhs) const { debug("youhou"); return (this->_curr - rhs.base()); }
		/* a - n */ reverse_random_access_iterator operator-(const difference_type step) const { debug("plop"); return reverse_random_access_iterator(_curr + step); }
		/* TEST */ reverse_random_access_iterator operator-( difference_type step)  { debug("ploup");return reverse_random_access_iterator(_curr + step); }

		/* a += n */ reverse_random_access_iterator& operator+=(const difference_type step) { this->_curr -= step; return *this; }
		/* a -= n */ reverse_random_access_iterator& operator-=(const difference_type step) { this->_curr += step; return *this; }
		/* b = a */ reverse_random_access_iterator& operator=(const reverse_random_access_iterator& rhs) { this->_curr = rhs._curr; return *this; }

		// /*POINTER OP*/
		reverse_random_access_iterator& operator--() {  ++_curr; return *this; }
		/* ++a */ reverse_random_access_iterator& operator++() { --_curr; return *this; }
		reverse_random_access_iterator operator--(int) { reverse_random_access_iterator tmp(*this); ++_curr; return tmp; }
		/* a++ */ reverse_random_access_iterator operator++(int) { reverse_random_access_iterator tmp(*this); --_curr; return tmp; }



//    inline _GLIBCXX17_CONSTEXPR bool
 //   operator>(const reverse_iterator<_Iterator>& __this,
//	      const reverse_iterator<_Iterator>& __y)
//    { return __y < __this; }


  /// Based on operator<
//  template<typename _Tp, typename _Alloc>
 //   inline bool
 //   operator>(const vector<_Tp, _Alloc>& __this, const vector<_Tp, _Alloc>& __y)
  //  { return __y < __this; }
		/* COMPARISONS */
		bool operator<(const reverse_random_access_iterator& rhs) { return this->_curr > rhs._curr; }
		bool operator<=(const reverse_random_access_iterator& rhs) { return this->_curr >= rhs._curr; }
		bool operator>(const reverse_random_access_iterator& rhs) { return rhs._curr > this->_curr; }
		bool operator>=(const reverse_random_access_iterator& rhs) { return this->_curr <= rhs._curr; }
		bool operator==(const reverse_random_access_iterator& rhs) const { return _curr == rhs._curr; }
		bool operator!=(const reverse_random_access_iterator& rhs) const { return _curr != rhs._curr; }

	};
	/* n + a */
	// template <typename T>
	// random_access_iterator<T>   operator+(typename ft::random_access_iterator<T>::difference_type n, random_access_iterator<T> a) { return (a + n); }

	/*a - b*/
	template <typename T>
	typename ft::reverse_random_access_iterator<T>::difference_type operator-(const reverse_random_access_iterator<T>& lhs, const reverse_random_access_iterator<T>& rhs) { return lhs.base() - rhs.base(); }
}



#endif

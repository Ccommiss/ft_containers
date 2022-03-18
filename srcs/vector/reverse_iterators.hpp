

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

		pointer _curr; // correspond a  T* 
		//T _curr;

	public:

		reverse_random_access_iterator() : _curr(0) {};
		reverse_random_access_iterator(T* rhs) : _curr(rhs) {};
		//random_access_iterator(const random_access_iterator& rhs) : _curr(rhs._curr) {};

		T* base() const
		{
			return _curr;
		}

		// // Pointer like operators
		reference		operator*() { return *_curr; }
		// const T* operator->() const throw()  return _curr; }
		// reference operator[](difference_type off) const { return _curr[off]; }
		// /* ARITHMETIQUES */
		/* a + b */ difference_type operator+(const reverse_random_access_iterator& rhs) const { return (this->_curr - rhs.base()); }
		/* a + n */ reverse_random_access_iterator operator+(const difference_type step) const { return (this->_curr - step); }
		/* TEST*/	reverse_random_access_iterator operator+(difference_type step) { return reverse_random_access_iterator(_curr - step); } // + step); }

		/* a - b */ difference_type operator-(const reverse_random_access_iterator& rhs) const { return (this->_curr + rhs.base()); }
		/* a - n */ reverse_random_access_iterator operator-(const difference_type step) const { return reverse_random_access_iterator(_curr + step); }
		/* a += n */ reverse_random_access_iterator& operator+=(const difference_type step) { this->_curr -= step; return *this; }
		/* a -= n */ reverse_random_access_iterator& operator-=(const difference_type step) { this->_curr += step; return *this; }
		/* b = a */ reverse_random_access_iterator& operator=(const reverse_random_access_iterator& rhs) { this->_curr = rhs._curr; return *this; }

		// /*POIINTER OP*/ OK 
		/* ++a */ reverse_random_access_iterator operator++(int) {reverse_random_access_iterator tmp(*this); ++(*this); return tmp; } // va appeler l'overload d'en dessous je suis mindblown
		/* a++ */ reverse_random_access_iterator& operator++() {--_curr; return *this; } // marche pas ???
		reverse_random_access_iterator operator--(int) { reverse_random_access_iterator tmp(*this); --(*this); return tmp; }
		reverse_random_access_iterator& operator--() { ++_curr; return *this; }



		// /* COMPARISONS */
		// bool operator<(const random_access_iterator& rhs) { return this->_curr < rhs._curr; }
		// bool operator<=(const random_access_iterator& rhs) { return this->_curr <= rhs._curr; }
		// bool operator>(const random_access_iterator& rhs) { return this->_curr > rhs._curr; }
		// bool operator>=(const random_access_iterator& rhs) { return this->_curr >= rhs._curr; }
		bool operator==(const reverse_random_access_iterator& rhs) const { return _curr == rhs._curr; }
		bool operator!=(const reverse_random_access_iterator& rhs) const { return _curr != rhs._curr; }

	};
	/* n + a */
	// template <typename T>
	// random_access_iterator<T>   operator+(typename ft::random_access_iterator<T>::difference_type n, random_access_iterator<T> a) { return (a + n); }

	// /*a - b*/
	// template <typename T>
	// typename ft::random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return lhs.base() - rhs.base(); }
}



#endif 
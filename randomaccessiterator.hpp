#ifndef RANDOM_ACCESS_ITERATORS_HPP
# define RANDOM_ACCESS_ITERATORS_HPP
#include <cstddef>
#include <iostream>


// https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator.h.html#__gnu_cxx::__normal_iterator 

namespace ft
{
	template <typename T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		typedef typename ft::random_access_iterator<T>::iterator<random_access_iterator, T>::difference_type diff_type;

		public:
		random_access_iterator() : _curr(0) {};
		random_access_iterator(T* rhs) : _curr(rhs) {};
		random_access_iterator(const random_access_iterator& rhs) : _curr(rhs._curr);

		T* base()
		{
			return _curr;
		}

		// Pointer like operators
		&T operator*() { return *_curr; }
		const T* operator->() const throw() { return _curr; }
		&T operator[](difference_type off) const { return _curr[off]; }
		/* ARITHMETIQUES */
		/* a + b */ random_access_iterator& operator+(const random_access_iterator& rhs) const { return (this->_curr + rhs.base()); }
		/* a + n */ random_access_iterator& operator+(const difference_type step) const { return (this->_curr + step); }
		/* a - b */ random_access_iterator& operator-(const random_access_iterator& rhs) const { return (this->_curr - rhs.base()); }
		/* a - n */ random_access_iterator& operator-(const difference_type step) const { return (this->_curr - step); }
		/* a += n */ random_access_iterator& operator+=(const difference_type step) { this->_curr += step; return *this; }
		/* a -= n */ random_access_iterator& operator-=(const difference_type step) { this->_curr -= step; return *this; }
		/* b = a */ random_access_iterator& operator=(const random_access_iterator& rhs) { this->_curr = rhs._curr; return *this; }

		/*POIINTER OP*/
		random_access_iterator& operator--() { --_curr; return *this; }
		random_access_iterator& operator++() { ++_curr; return *this; }
		random_access_iterator operator--(int) { random_access_iterator tmp(*this); --(*this); return tmp; }
		random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++(*this); return tmp; }

		/* COMPARISONS */
		bool operator<(const random_access_iterator& rhs) { return this->_curr < rhs._curr; }
		bool operator<=(const random_access_iterator& rhs) { return this->_curr <= rhs._curr; }
		bool operator>(const random_access_iterator& rhs) { return this->_curr > rhs._curr; }
		bool operator>=(const random_access_iterator& rhs) { return this->_curr >= rhs._curr; }
		bool operator==(const random_access_iterator& rhs) const { return _curr == rhs._curr; }
		bool operator!=(const random_access_iterator& rhs) const { return _curr != rhs._curr; }

		const _Iterator& base() const
		{
			return _curr;
		}

		private:
		T* _curr;
	};
	/* n + a */
	template <typename T>
	random_access_iterator<T>   operator+(typename ft::random_access_iterator<T>::diff_type n, random_access_iterator<T> a) { return (a + n); }

	/*a - b*/
	template <typename T>
	typename ft::random_access_iterator<T>::diff_type operator-(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return __lhs.base() - __rhs.base(); }
}

#endif
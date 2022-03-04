#include <cstddef>
#include <iostream>

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
struct iterator
{
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
	typedef Category iterator_category;
};

struct random_access_iterator_tag
{
};

namespace ft
{
	template <typename T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
		typedef typename ft::random_access_iterator<T>::iterator<random_access_iterator, T>::difference_type diff_type;

	public:
		T*		base()
		{
			return _curr;
		}

		/* a + b */
		random_access_iterator &operator+(const random_access_iterator &rhs) const
		{
			return (this->_curr + rhs.base());
		}
		/* a + n */
		random_access_iterator &operator+(const difference_type step) const
		{
			return (this->_curr + step);
		}
		/* a - b */
		random_access_iterator &operator+(const random_access_iterator &rhs) const
		{
			return (this->_curr - rhs.base());
		}
		/* a - n */
		random_access_iterator &operator-(const difference_type step) const
		{
			return (this->_curr - step);
		}
		/* a += n */
		random_access_iterator &operator+=(const difference_type step) //pas const
		{
			this->_curr += step;
			return *this;
		}
		/* a -= n */
		random_access_iterator &operator-=(const difference_type step) //pas const
		{
			this->_curr -= step;
			return *this;
		}




		const _Iterator &base() const
		{
			return _curr;
		}

	private:
		T *_curr;
	}

	//} ::iterator::Distance;
}

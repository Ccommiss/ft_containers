

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

namespace ft {

	template <typename T>
	class reverse_iterator : public iterator<ft::iterator_traits::iterator_category, T>
	{
		protected:
			T *_curr;
			typedef ft::iterator_traits<T>                traits_type;

	};


}

#endif 
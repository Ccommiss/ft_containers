
#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

#include <iostream>

namespace ft
{

	/*
	** @brief std::pair is a class template that provides a way to store two heterogeneous objects as a single unit.
	** A pair is a specific case of a std::tuple with two elements.
	** If neither T1 nor T2 is a possibly cv-qualified class type with non-trivial destructor,
	**	or array thereof, the destructor of pair is trivial.
	** @tparam T1,T2 the types of the elements that the pair stores.
	*/
	template <class T1, class T2>
	struct pair
	{

		//private:
		T1 first;
		T2 second;

		public:
		/*
		** 1) Default constructor. Value-initializes both elements of the pair, first and second.
		*/
		pair() : first(T1()), second(T2()) { }

		/*
		** 2) Initializes first with x and second with y.
		*/
		pair(const T1& x, const T2& y) : first(x), second(y) {}

		/*
		** 4) Initializes first with p.first and second with p.second.
		*/
		template <class U1, class U2>
		pair(const pair<U1, U2>& x) : first(x.first), second (x.second)
		{
			//*this = x;
		}

		/*
		** 1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
		*/
		pair<T1, T2>& operator=(const pair<T1, T2>& x)
		{
			first = x.first;
			second = x.second;
			return *this;
		}
	};


	/* ****************************************************
	**	NON MEMBERS FUNCTIONS
	** ****************************************************
	**
	** 	├── Relational Operators - using equal, lexicographical
	** 	  ├── ==
	** 	  ├── !=
	** 	  ├── <, <=
	** 	  └── >, >=
	**
	** operation	equivalent operation
	**	a!=b	|	!(a==b)
	**	a>b		|	b<a
	**	a<=b	|	!(b<a)
	**	a>=b	|	!(a<b)
	**/

	/*
	**	@brief 1-2) Tests if both elements of lhs and rhs are equal,
	**	that is, compares lhs.first with rhs.first and lhs.second with rhs.second.
	*/
	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		if (lhs.first == rhs.first && lhs.second == rhs.second)
			return (true);
		return (false);
	}

	//	**	a!=b	|	!(a==b)
	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}

	/*
	** 	Compares lhs and rhs lexicographically by operator<, that is, compares the
	**	first elements and only if they are equivalent, compares the second elements.
	*/
	template <class T1, class T2>
	bool operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		if (lhs.first != rhs.first)
			return (lhs.first < rhs.first);
		else 
			return (lhs.second < rhs.second);
	}

	template <class T1, class T2>
	/**	a>b		*/
	bool operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (rhs.first < lhs.first);
	}

	// 	**	a<=b	|	!(b<a)
	template <class T1, class T2>
	bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	// ** a>=b	|	!(a<b)
	bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return !(lhs.first < rhs.first);
	}

	/*
	** make_pair
	** @brief Creates a std::pair object, deducing the target type from the types of arguments.
	** @param  t,u- the values to construct the pair from
	** @return A std::pair object containing the given values.
	*/
	template< class T1, class T2 >
	ft::pair<T1, T2> make_pair(T1 t, T2 u)
	{
		ft::pair<T1, T2> new_pair;
		new_pair.first = t;
		new_pair.second = u;
		return (new_pair);
	}

}





/*
**  OVERLOAD <<
**	@brief overloading pair so it is seen as key/value
*/
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, ft::pair<T, U>& pair)
{
	if (&pair != NULL)
	{
		os << "[" << pair.first << "]=\"" << pair.second << "\"";
	}
	return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const ft::pair<T, U>& pair)
{
	if (&pair != NULL)
	{
		os << "[" << pair.first << "]=\"" << pair.second << "\"";
	}
	return os;
}

#endif


#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

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

	private:
		T1 first;
		T2 second;

	public:
		/*
		** 1) Default constructor. Value-initializes both elements of the pair, first and second.
		*/
		pair() : first(0), second(0) {}

		/*
		** 2) Initializes first with x and second with y.
		*/
		pair(const T1 &x, const T2 &y) : first(x), second(y) {}

		/*
		** 4) Initializes first with p.first and second with p.second.
		*/
		template <class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

		/*
		** 1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
		*/
		pair<T1, T2> &operator=(const pair<T1, T2> &x)
		{
			first = x.first;
			second = x.second;
		}
	};
	/*
	**  NON MEMBER FUNCTIONS
	*/

	/*
	**	@brief 1-2) Tests if both elements of lhs and rhs are equal,
	**	that is, compares lhs.first with rhs.first and lhs.second with rhs.second.
	*/
	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		if (lhs.first == rhs.first && lhs.second == rhs.second)
			return (true);
		return (false);
	}
	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	/*
	** 	Compares lhs and rhs lexicographically by operator<, that is, compares the
	**	first elements and only if they are equivalent, compares the second elements.
	*/
 // UTILISER LEXICOGRAPHICAL ?
	template <class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first);
	}

}

#endif
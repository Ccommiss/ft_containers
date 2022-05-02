
# ifndef TEST_HPP
# define TEST_HPP
#include <cstdlib>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include <map>
#include <stack>
#include <vector>
#include "debug.hpp"
#include <typeinfo>


template <typename T>
void example(T& r_vec)
{
	std::cout << BOLD("-> example with real vector only : ") << std::endl;
	std::cout << FG2("Real :") << std::endl;
	typename T::iterator it;
	for (it = r_vec.begin(); it != r_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

}


template <typename T1>
void print(T1& r_vec)
{
	std::cout << BOLD("-> Mine only : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename T1::iterator it;
	for (it = r_vec.begin(); it != r_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

}

template <typename V>
void    capacity_show(ft::vector<V> &my_vec, std::vector<V> &r_vec)
{
     std::cout << DIM("Real capacity : ") << r_vec.capacity() << DIM(" VS my capacity : ") << my_vec.capacity() << std::endl << std::endl;  
}

template <typename V, typename U> // pas de capacite pour les vecteurs 
void    capacity_show(V &my_vec, U &r_vec)
{
    (void)my_vec;
    (void)r_vec;
}

template <typename U, typename V>
void display(U& my_vec, V& r_vec)
{
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename U::iterator it1;
	for (it1 = my_vec.begin(); it1 != my_vec.end(); it1++)
		std::cout << *it1 << " ";
	std::cout << std::endl;

	std::cout << FG2("Real :") << std::endl;
	typename V::iterator it;
	for (it = r_vec.begin(); it != r_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << DIM("Real size : ") << r_vec.size() << DIM(" VS my size : ") << my_vec.size() << std::endl;
    capacity_show(my_vec, r_vec);
}



/*
**	Map  
*/
void    map_tests();
void    vector_tests();

#endif
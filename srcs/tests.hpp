
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



template <typename V>
void    capacity_show(ft::vector<V> &my_container, std::vector<V> &real_container)
{
     std::cout << DIM("Real capacity : ") << real_container.capacity() << DIM(" VS my capacity : ") << my_container.capacity() << std::endl << std::endl;
}

template <typename V, typename U> // pas de capacite pour les vecteurs
void    capacity_show(V &my_container, U &real_container)
{
    (void)my_container;
    (void)real_container;
}


template <typename V>
void    capacity_solo(ft::vector<V> &container)
{
     std::cout << DIM("Capacity : ") << container.capacity() << std::endl << std::endl;
}

template <typename V>
void    capacity_solo(std::vector<V> &container)
{
     std::cout << DIM("Capacity : ") << container.capacity() << std::endl << std::endl;
}

template <typename U> // pas de capacite pour les vecteurs
void    capacity_solo(U &container)
{
    (void)container;
}


template <typename T1>
void print(T1& container)
{
	std::cout << BOLD("-> Output : ") << std::endl;
	typename T1::iterator it;
	for (it = container.begin(); it != container.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << DIM("Size : ") << container.size() << std::endl;
	capacity_solo(container);
}

template <typename U, typename V>
void display(U& my_container, V& real_container)
{
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename U::iterator it1;
	for (it1 = my_container.begin(); it1 != my_container.end(); it1++)
		std::cout << *it1 << " ";
	std::cout << std::endl;

	std::cout << FG2("Real :") << std::endl;
	typename V::iterator it;
	for (it = real_container.begin(); it != real_container.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << DIM("Real size : ") << real_container.size() << DIM(" VS my size : ") << my_container.size() << std::endl;
    capacity_show(my_container, real_container);
}



/*
**	Map
*/
void    map_tests();
void 	comparative_tests_map();
void 	vector_tests();
void 	comparative_tests_vector();

#endif

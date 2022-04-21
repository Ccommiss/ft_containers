

#include "Map.hpp"
#include "ft_tree_vis.cpp"
#include <map>
#include "../includes.hpp"
#include <memory>
#include "../utils/debug.hpp"

#define start head("Test : " << __func__ << " "); 	srand (time(NULL));
#define finish head("End of test : " << __func__ << " ");
#define wait_see               \
	display(my_map, real_map); \
	getwchar();

using namespace std;

/*
**	PRINT FUNCTIONS
**
**
*/

template <typename T, typename U>
void example(std::map<T, U> &r_map)
{
	std::cout << BOLD("-> example with real map only : ") << std::endl;
	std::cout << FG2("Real :") << std::endl;
	typename std::map<T, U>::iterator it;
	for (it = r_map.begin(); it != r_map.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename T, typename U>
void print(ft::map<T, U> &r_map)
{
	std::cout << BOLD("-> Mine only : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename ft::map<T, U>::iterator it;
	for (it = r_map.begin(); it != r_map.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename T, typename U>
void display(ft::map<T, U> &my_map, std::map<T, U> &r_map)
{
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename ft::map<T, U>::iterator it1;
	for (it1 = my_map.begin(); it1 != my_map.end(); it1++)
		std::cout << *it1 << " ";
	std::cout << std::endl;

	std::cout << FG2("Real :") << std::endl;
	typename std::map<T, U>::iterator it;
	for (it = r_map.begin(); it != r_map.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	cout << DIM("Real size : ") << r_map.size() << DIM(" VS my size : ") << my_map.size() << endl;
}

/*
**	TEST FUNCTIONS
**
**
*/

void 	iterators_test()
{
	start;
	int a = rand() % 89 + 1;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = {"Maitre Gims", "Orelsan", "Jimmy Hendrix", "Stromae", "Mozart", "Beethoven"};
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(a, word_array[i]));
		real_map.insert(std::make_pair(a, word_array[i]));
		a = rand() % 89 + 1;
	}
	wait_see;
	ft::map<int, std::string>::iterator		my_map_it = my_map.end();
	std::map<int, std::string>::iterator	real_map_it = real_map.end();

	my_map_it = my_map.begin();
	real_map_it = real_map.begin();
	std::cout << addressof(*real_map.begin()) << " " << addressof(*real_map.end()) << std::endl;

	while (1)
	{
		//std::cout << *(my_map_it) << std::endl;
		std::cout << real_map_it->first << std::endl;
		//my_map_it--;
		real_map_it--;
	}
	// out("End :" << *(my_map_it));
	// out("End :" << *(real_map_it));
	out("--End :" << *(--my_map_it));
	out("--End :" << *(--real_map_it));
	out("Begin :" << *(my_map.begin()));
	out("Begin :" << *(real_map.begin()));
	out("Begin++ :" << *(my_map.begin()++));
	out("Begin++ :" << *(real_map.begin()++));
	out("++Begin :" << *(++my_map.begin()));
	out("++Begin :" << *(++real_map.begin()));
	out("End :" << *(real_map_it));
	out("End :" << *(my_map_it));
	out("End-- :" << *(real_map_it--));
	out("End-- :" << *(my_map_it--));
	finish;
}

void basic_tests_insert_erase()
{
	start;
	ft::map<int, std::string>	my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = {"Ce matin", "a Marseille", "nous avons vu", "des poissons", "dans le ciel", "car nous aimons", "la bouillabaisse"};
	int int_array[] = {1, 2, 3, 4, 58, 65, 75, 65, 23};
	for (int i = 0; i < 7; i++)
	{
		my_map.insert(ft::make_pair(int_array[i], word_array[i]));
		real_map.insert(std::make_pair(int_array[i], word_array[i]));
	}
	wait_see;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "DELETING " << word_array[i] << std::endl;
		my_map.erase(int_array[i]);
		real_map.erase(int_array[i]);
	}
	wait_see;
	for (int i = 3; i < 7; i++)
	{
		std::cout << "DELETING " << word_array[i] << std::endl;
		my_map.erase(int_array[i]);
		real_map.erase(int_array[i]);
	}
	wait_see;
	finish;
}

int main()
{

	void (*functptr[])() = {
		basic_tests_insert_erase,
		iterators_test,
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		(*functptr[i])();    /*  Call first function  */
		getwchar();

	}
}

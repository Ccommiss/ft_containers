
#include "../tests.hpp"


#define see display(my_map, real_map);


void basic_tests_insert_erase()
{
	start;
	ft::map<int, std::string>	my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Ce matin", "a Marseille", "nous avons vu", "des poissons", "dans le ciel", "car nous aimons", "la bouillabaisse" };
	int int_array[] = { 1, 2, 3, 4, 58, 65, 75, 65, 23 };
	for (int i = 0; i < 7; i++)
	{
		my_map.insert(ft::make_pair(int_array[i], word_array[i]));
		real_map.insert(std::make_pair(int_array[i], word_array[i]));
	}
	see;
	for (int i = 0; i < 3; i++)
	{
		my_map.erase(int_array[i]);
		real_map.erase(int_array[i]);
	}
	see;
	for (int i = 3; i < 7; i++)
	{
		my_map.erase(int_array[i]);
		real_map.erase(int_array[i]);
	}
	see;
	finish;
}

void multiple_insert_test()
{
	start;
	ft::map<int, int> my_map;
	std::map<int, int>	real_map;
	for (unsigned int i = 0; i < 1000; i++)
	{
		int a = rand() % 1000 + 1;
		int b = rand() % 1000 + 1;
		my_map.insert(ft::make_pair(a, b));
		real_map.insert(std::make_pair(a, b));
	}
	see;
	finish;
}


void iterators_test()
{
	start;
	int a = rand() % 89 + 1;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Maitre Gims", "Orelsan", "Jimmy Hendrix", "Stromae", "Mozart", "Beethoven" };
	for (unsigned long i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(a, word_array[i]));
		real_map.insert(std::make_pair(a, word_array[i]));
		a = rand() % 89 + 1;
	}
	see;
	ft::map<int, std::string>::iterator		my_map_it = my_map.end();
	std::map<int, std::string>::iterator	real_map_it = real_map.end();

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

void    map_tests()
{
    	void (*functptr[])() = {
		//simple_insert,
		basic_tests_insert_erase,
		multiple_insert_test,
		iterators_test,
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		(*functptr[i])();    /*  Call first function  */
	}
}


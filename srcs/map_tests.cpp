
#include "map.hpp"
#include "debug.hpp"
#include <map>
#include <cstdlib>




void time_test()
{
    start;
    std::cout << "lol" << std::endl;
    finish;
}

void    map_tests()
{
    	void (*functptr[])() = {
		//simple_erase_it,
		//simple_insert,
		//leaks_erase,
		//basic_tests_insert_erase,
		//count_test,
		// fifty_insert_test,
		// iterators_test,
		//reverse_iterators,
		//delete_same_value_test,
		//insert_same_value_test,
		// tricky_pairs_test,
		// access_operator_test,
		//	erase_iterator_test,
		//insert_iterator_test,
		//count_test2,
		//lower_bounds,
		//swap_test,
		time_test
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		(*functptr[i])();    /*  Call first function  */
		getwchar();

	}
}


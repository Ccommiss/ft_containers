#include <fstream>
#include "srcs/tests.hpp"


#ifndef NM
# define NM std

#endif

using namespace NM;

int main()
{
	std::ifstream file("srcs/containers.txt");
	std::cout << file.rdbuf();

	#ifdef vec
		h1("VECTOR")
		comparative_tests_vector();
	#endif
	#ifdef map_macro
		h1("MAP")
		comparative_tests_map();
	#endif
	#ifdef test
		h1("MAP")
		comparative_tests_map();
		h1("VECTOR")
		comparative_tests_vector();
		h1("STACK")
		comparative_tests_stack();
		h1("SET")
		comparative_tests_set();
	#endif
}


#include <fstream>
#include "srcs/tests.hpp"




using namespace NM;

int main()
{

	std::string STRING;
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
	#endif
}

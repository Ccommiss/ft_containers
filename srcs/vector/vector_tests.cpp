
#include "../tests.hpp"







void vector_tests()
{
    void (*functptr[])() = {
       // basic_test
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		(*functptr[i])();    /*  Call first function  */
	}
}

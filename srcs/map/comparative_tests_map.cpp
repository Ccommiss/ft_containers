#include "../tests.hpp"


using namespace NM;

void insert()
{
	map<int, int> test_1;
	int a, b;
	for (unsigned int i = 0; i < 10000; i++)
	{
		i % 2 == 0 ? a = i * 2 : i * 5;
		i % 2 == 0 ? b = i * 6 : i;
		test_1.insert(make_pair(a, b));
	}
	print(test_1);
	finish;
}

void erase()
{
	start;
	map<int, int> test_1;
	int a, b;
	for (unsigned int i = 0; i < 100; i++)
	{
		i % 2 == 0 ? a = i * 2 : i * 5;
		i % 2 == 0 ? b = i * 6 : i;
		test_1.insert(make_pair(a, b));
	}
	test_1.insert(make_pair(15, 15));
	test_1.insert(make_pair(17, 17));
	test_1.insert(make_pair(1, 1));
	test_1.insert(make_pair(5, 5));
	print(test_1);

	map<int, int>::iterator it;
	int i = 0;
	for (it = test_1.begin(); it != test_1.end();)
	{
		map<int, int>::iterator tmp;
		if (it->first % 2 == 0)
		{
			out ("deleting " << (it->first))
			tmp = it;
			it++;
			test_1.erase(tmp);
		}
		else
			it++;
	}
	print(test_1);
	finish;
}



void comparative_tests_map()
{
	insert();
	erase();
}

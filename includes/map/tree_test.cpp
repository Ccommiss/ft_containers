

#include "ft_tree.hpp"
#include "../utils/debug.hpp"
#include <iostream>

#define showtree myTree.display(myTree.getRootPtr());
#define start head("Test : " << __func__ << " ");
#define valid_check                                      \
	if (myTree.validity_check(myTree.getRootPtr()) == 1) \
	{                                                    \
		out("🔴 VALIDITY CHECK IS WRONG !!!!")            \
	}                                                    \
	else                                                 \
	{                                                    \
		out(" ✅ VALIDITY CHECK IS OK !!!!")              \
	}

#define end     \
	valid_check \
		head("End of test : " << __func__ << " ");

void left_heavy()
{
	start
		Tree myTree;

	int array[4] = {42, 32, 12};
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array[i]);
		showtree
			wait
	}
	end;
	// Expected result : left-heavy situation found, rotation + flip colors
}

void left_right()
{
	start

		Tree myTree;
	int array[4] = {50, 43, 45};
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array[i]);
		showtree
			wait
	}
	end;

	head("More");
	int array2[4] = {44, 47, 51};
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array2[i]);
		showtree
			wait
	}
	end;
}

void progressive_test()
{
	start
		Tree myTree;
	int node_value;
	while (1)
	{
		wscanf(L"%d", &node_value);
		myTree.insert(node_value);
		showtree
			wait
	}
	end;
}

void test_simple_recoloring()
{
	start
		Tree myTree;
	int array[4] = {30, 15, 45}; // la base : un root noir, deux siblings rouges (il faut un oncle
	// pour les simples recolor)

	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array[i]);
		showtree
			wait
	}
	myTree.insert(10); // test left
	showtree
		end;
}

void simple_delete()
{
	start;

	head("test 1 : reed leaf")
	{
		Tree myTree;
		int array[] = {10, 5, 2, 9, 30, 25, 40, 38};

		for (int i = 0; i < 8; i++)
		{
			myTree.insert(array[i]);
			wait
		}
		showtree;
		// Check case one, delete red leaf
		out("start to del :: ");
		myTree.del(30);
		showtree;
		end;
	}
	// Check case double black,
	head("test 2 : DB black nephew");
	{
		Tree myTree;
		int array[] = {10, 5, 20, 7, 4};

		for (int i = 0; i < 5; i++)
		{
			myTree.insert(array[i]);
			wait
		}
		showtree;
		out("start to del :: ");
		myTree.del(5);
		showtree;
		end;
	}

	// head("test 2 : DB");
	// {
	// 	Tree myTree;
	// 	int array[] = {10, 5, 20, 15, 30, 65, 78};

	// 	for (int i = 0; i < 7; i++)
	// 	{
	// 		myTree.insert(array[i]);
	// 		wait
	// 	}
	// 	showtree;
	// 	out("start to del :: ");
	// 	myTree.del(15);
	// 	showtree;
	// 	end;
	// }
}

void ten_elem_test1()
{
	start;
	Tree myTree;
	int array[10] = {30, 15, 45, 78, 56, 100, 450, 459, 12, 1};
	for (int i = 0; i < 10; i++)
	{
		myTree.insert(array[i]);
		showtree;
		wait
	}
	out("Definitive tab");
	showtree;
	end
}

void twenty_elem_test1()
{
	start;
	Tree myTree;
	int array[] = {30, 15, 45, 78, 56, 100, 450, 459, 12, 1, 543, 653, 4523, 432, 425, 5425, 764, 6356, 777, 45};
	for (int i = 0; i < 19; i++)
	{
		myTree.insert(array[i]);
		out("===> FROM MAIN (just added " << array[i] << ")");
		showtree;
		wait
	}
	out("Definitive tab");
	showtree;
	end
}

void twenty_elem_only_bigger()
{
	start;
	Tree myTree;
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	for (int i = 0; i < 19; i++)
	{
		myTree.insert(array[i]);
		out("===> FROM MAIN (just added " << array[i] << ")");
		showtree;
		wait
	}
	out("Definitive tab");
	showtree;
	end
}

int main()
{

	void (*functptr[])() = {
		// left_heavy,
		// left_right,
		// test_simple_recoloring,
		// ten_elem_test1,
		// twenty_elem_test1
		// twenty_elem_only_bigger
		simple_delete};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		(*functptr[i])();
		getwchar();
	}
}

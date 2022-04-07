

#include "ft_tree.hpp"
#include "../utils/debug.hpp"
#include <iostream>

# define showtree myTree.display(myTree.getRootPtr());
# define start head("Test : " << __func__ << " ");
# define valid_check 	myTree.validity_check(myTree.getRootPtr());


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
	valid_check;
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

	head("More");
	int array2[4] = {44, 47, 51};
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array2[i]);
		showtree
		wait
	}
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


}

void 	simple_delete()
{
	start;
	Tree myTree;
	int array[4] = {30, 15, 45};
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array[i]);
		wait
	}
	out("start to del :: ")
	for (int i = 0; i < 3; i++)
	{
		myTree.del(array[i]);
		out("deleting " << array[i]);
		wait
		showtree
		out ("end of turn")
	}
}

void ten_elem_test1()
{
	start;

	Tree myTree;
	int array[10] = {30, 15, 45, 78, 56, 100, 450, 459, 12, 1 };
	for (int i = 0; i < 10; i++)
	{
		myTree.insert(array[i]);
		showtree;
		wait
	}
	out("Definitive tab");
	showtree;
}

int main()
{

	void (*functptr[])() = {
		//left_heavy,
		//left_right,
		//test_simple_recoloring,
		ten_elem_test1
		//simple_delete
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
	 	(*functptr[i])(); /*  Call first function  */
	 	head("--- end of tests ---")
	 		getwchar();
	}


	// myTree.insert(53);
	// getwchar();
	// myTree.insert(54);
	// myTree.insert(52);
	// // la on a trois boules
	// myTree.insert(42); // la normalement on va tout flip au dessus
	// // ca fonctionne
	// myTree.insert(58);
	// myTree.insert(56);

	// std::cout << myTree.getRoot() << std::endl;

	// myTree.insert(89);

	// myTree.insert(93);
	// myTree.insert(150);
	//  myTree.insert(90);
	//  myTree.insert(13);
}

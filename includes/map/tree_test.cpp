


#include "ft_tree.hpp"
#include "../utils/debug.hpp"
#include <iostream>


void left_heavy()
{
	head("Left heavy")
	Tree myTree;

	int array[4] = { 42, 32, 12 };
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array[i]);
		wait
	}
	// Expected result : left-heavy situation found, rotation + flip colors
}

void left_right()
{
	head("Left-right");

	Tree myTree;
	int array[4] = { 50, 43, 45 };
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array[i]);
		wait
	}

	head("More");
	int array2[4] = { 44, 47, 51 };
	for (int i = 0; i < 3; i++)
	{
		myTree.insert(array2[i]);
		wait
	}

}

void progressive_test()
{
	head("Progressive tests")
	Tree myTree;
	int node_value;
	while (1)
	{
		wscanf (L"%d",&node_value);
		myTree.insert(node_value);
	}
}

void test_simple_recoloring();



int main()
{

	left_heavy();
	left_right();

	// myTree.insert(53);
	// getwchar();
	// myTree.insert(54);
	// myTree.insert(52);
	// // la on a trois boules
	// myTree.insert(42); // la normalement on va tout flip au dessus
	// // ca fonctionne
	// myTree.insert(58);
	// myTree.insert(56);


	//std::cout << myTree.getRoot() << std::endl;


	//myTree.insert(89);

	//myTree.insert(93);
	//myTree.insert(150);
	// myTree.insert(90);
	// myTree.insert(13);
}




#include "ft_tree.hpp"
#include <iostream>
int main()
{

	Tree myTree;
	myTree.insert(54);
	//std::cout << myTree.getRoot() << std::endl;
	myTree.insert(52);
	myTree.insert(53);
//	myTree.insert(89);
	//myTree.insert(42);
	//myTree.insert(93);
	//myTree.insert(150);
	// myTree.insert(90);
	// myTree.insert(13);



	std::cout << "display ......" << std::endl;
	myTree.display(myTree.getRootPtr());




}
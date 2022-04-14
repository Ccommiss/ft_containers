

#include "Map.hpp"
#include "ft_tree_vis.cpp"
int main()
{
	//ft::Tree<std::string> myTree;

	// myTree.insert("lol");
	// myTree.insert("Je");
	// myTree.insert("m'appelle");
	// myTree.insert("Claire");
	// myTree.insert("Commissaire");
	// myTree.see_tree();

	//ft::map<int, std::string> lol;
	ft::Tree<ft::pair <int, std::string> > TreePair;
	ft::pair<int, std::string> test1(1, "bonjour");
	TreePair.insert(test1);
}

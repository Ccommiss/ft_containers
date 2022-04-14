

#include "Map.hpp"
#include "ft_tree_vis.cpp"
int main()
{
	ft::Tree<std::string> myTree;
	myTree.insert("lol");
	myTree.insert("Je");
	myTree.insert("m'appelle");
	myTree.insert("Claire");
	myTree.insert("Commissaire");
	myTree.insert("lol2");
	myTree.insert("Je2");
	myTree.insert("m'appelle2");
	myTree.insert("Claire2");
	myTree.insert("Commissaire2");
	myTree.see_tree();

	ft::map<int, std::string> lol;
	ft::Tree<ft::pair <int, std::string> > TreePair;
	ft::pair<int, std::string> test1(1, "bonjour");
	ft::pair<int, std::string> test2(2, "je suis");
	ft::pair<int, std::string> test3(3, "contente");
	ft::pair<int, std::string> test4(8, "et toi FDP");
	ft::pair<int, std::string> test5(90, "lol");
	TreePair.insert(test1);
	TreePair.insert(test2);
	TreePair.insert(test3);
	TreePair.insert(test4);
	TreePair.insert(test5);
	TreePair.display(TreePair.getRootPtr());
	TreePair.see_tree();
}

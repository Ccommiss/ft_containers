

#include "Map.hpp"
#include "ft_tree_vis.cpp"
#include <map>

template <typename T>
struct cmpByStringLength {
    bool operator()(const T& a, const T& b) const 
	{ 
		return (a.first != b.first ? a.first > b.first: a.second > b.second );

		//return (a.first.length() != b.first.length() ? a.first.length() < b.first.length() : a.second.length() < b.second.length());
	}
};

int main()
{
	//ft::Tree<std::string> myTree;
	//myTree.insert("lol");
	//myTree.insert("Je");
	//myTree.insert("m'appelle");
	// myTree.insert("Claire");
	// myTree.insert("Commissaire");
	// myTree.insert("lol2");
	// myTree.insert("Je2");
	// myTree.insert("m'appelle2");
	// myTree.insert("Claire2");
	// myTree.insert("Commissaire2");
//	myTree.see_tree();

	//ft::Tree<ft::pair <int, std::string> > TreePair;
	ft::map<int, std::string> lol;
	ft::pair<int, std::string> mypair(1, "uno");
	ft::pair<int, std::string> mypair2(2, "dos");
	ft::pair<int, std::string> mypair3(3, "tres");
	//TreePair.insert(mypair);
	lol.insert(mypair);
	lol.insert(mypair2);
	lol.insert(mypair3);

	lol.debugging();
	ft::map<int, std::string>::iterator it = lol.find(2); // renvoie it sur pair
	std::cout << "ICI BIG TEST " << (lol.find(2))->second << std::endl;
	it++;
	std::cout << "IT 1 = " << (*it).second << std::endl; 
	it--;
	std::cout << "IT 1 = " << (*it).second << std::endl; 

	ft::Tree<ft::pair <int, std::string> >   	TreePair;
	std::map<int, std::string> test;
	std::map<int, std::string>::iterator test_it;
	test.insert(std::make_pair<int, std::string>(8, "Salut"));
	test.insert(std::make_pair<int, std::string>(9, "ici"));
	test_it = test.find(8); 
	std::cout << (*test_it).first  << std::endl;
	test_it++;
	std::cout << (*test_it).first  << std::endl;



//	out("TREE PAIR " << TreePair.getRoot());
	// ft::pair<int, std::string> test1(1, "bonjour");
	// ft::pair<int, std::string> test2(2, "je suis");
	// ft::pair<int, std::string> test3(3, "contente");
	// ft::pair<int, std::string> test4(8, "et toi FDP");
	// ft::pair<int, std::string> test5(90, "lol");
	// TreePair.insert(test1);
	// TreePair.insert(test2);
	// TreePair.insert(test3);
	// TreePair.insert(test4);
	// TreePair.insert(test5);
	// TreePair.display(TreePair.getRootPtr());
	//TreePair.see_tree();


	// std::cout << std::less<int>()(2,3) << std::endl; 
	// ft::Tree< ft::pair <std::string, std::string>, cmpByStringLength< ft::pair <std::string, std::string> > > TreePair2;
	// //ft::Tree<ft::pair <std::string, std::string>, std::less< ft::pair<std::string, std::string> > > TreePair2;
	// ft::Tree<ft::pair <std::string, std::string> > TreePair3; // clone doit marcher pareil que au dessus avec std::less 


	// TreePair2.insert(ft::make_pair<std::string, std::string>("1", "un"));
	// TreePair3.insert(ft::make_pair<std::string, std::string>("1", "un"));

	// TreePair2.insert(ft::make_pair<std::string, std::string>("2", "deux"));
	// TreePair3.insert(ft::make_pair<std::string, std::string>("2", "deux"));

	// TreePair2.insert(ft::make_pair<std::string, std::string>("3", "troisss"));
	// TreePair3.insert(ft::make_pair<std::string, std::string>("3", "troisss"));

	// TreePair2.insert(ft::make_pair<std::string, std::string>("4", "n"));
	// TreePair3.insert(ft::make_pair<std::string, std::string>("4", "n"));

	// TreePair2.insert(ft::make_pair<std::string, std::string>("4", "a"));
	// TreePair3.insert(ft::make_pair<std::string, std::string>("4", "a"));

	// TreePair2.see_tree();
	// TreePair3.see_tree();

	
}

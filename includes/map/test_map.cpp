

#include "Map.hpp"
#include "ft_tree_vis.cpp"
#include <map>
#include "../includes.hpp"

using namespace std;


// struct cmpByStringLength {
// 	bool operator()(const T& a, const T& b) const
// 	{
// 		return (a.first != b.first ? a.first > b.first: a.second > b.second);

// 		//return (a.first.length() != b.first.length() ? a.first.length() < b.first.length() : a.second.length() < b.second.length());
// 	}
// };

template <typename T, typename U>
void example(std::map<T, U>& r_map)
{
	std::cout << BOLD("-> example with real map only : ") << std::endl;
	std::cout << FG2("Real :") << std::endl;
	typename std::map<T, U>::iterator it;
	for (it = r_map.begin(); it != r_map.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

}

template <typename T, typename U>
void print(ft::map<T, U>& r_map)
{
	std::cout << BOLD("-> Mine only : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename ft::map<T, U>::iterator it;
	for (it = r_map.begin(); it != r_map.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

}

template <typename T, typename U>
void display(ft::map<T, U>& my_map, std::map<T, U>& r_map)
{
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename ft::map<T, U>::iterator it1;
	for (it1 = my_map.begin(); it1 != my_map.end(); it1++)
		std::cout << *it1 << " ";
	std::cout << std::endl;

	std::cout << FG2("Real :") << std::endl;
	typename std::map<T, U>::iterator it;
	for (it = r_map.begin(); it != r_map.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	cout << DIM("Real size : ") << r_map.size() << DIM(" VS my size : ") << my_map.size() << endl;
	//cout << DIM("Real capacity : ") << r_map.capacity() << DIM(" VS my capacity : ") << my_map.capacity() << endl << endl;
	//if (r_map.size() != my_map.size())// || r_map.capacity() != my_map.capacity())
	//	getwchar();
}



void test_basic()
{


}


void test_reverse_iterator()
{
	ft::map<int, std::string> my_map;
	std::map<int, std::string> real_map;
	std::string word_array[] = { "Ce matin", "a Marseille", "nous avons vu", "des poissons", "dans le ciel", "car nous aimons", "la bouillabaise"};
	int int_array[] = { 1, 2, 3, 4, 58, 65, 75, 65, 23};
	for (int i = 0; i < 7; i++)
	{
		my_map.insert(ft::make_pair(int_array[i], word_array[i]));
		real_map.insert(std::make_pair(int_array[i], word_array[i]));
	}
	//my_map.debugging();
	display(my_map, real_map);
	getwchar();
	out ("ERASE");
	for (int i = 0; i < 7; i++)
	{	
		std::cout << "DELETING " << word_array[i] << std::endl; 
		my_map.erase(int_array[i]);
		my_map.debugging();
		getwchar();		//real_map.erase(int_array[i]);
	}
	
	//display(my_map, real_map);
	getwchar();
	exit(0);

}


int main()
{
	test_reverse_iterator();

	//ft::Tree<ft::pair <int, std::string> > TreePair;
	ft::map<int, std::string> lol;
	ft::pair<int, std::string> mypair(1, "uno");
	ft::pair<int, std::string> mypair2(2, "dos");
	ft::pair<int, std::string> mypair3(3, "tres");
	ft::pair<int, std::string> mypair4(0, "zero");
	ft::pair<int, std::string> mypair5(73, "soixante tres");
	ft::pair<int, std::string> mypair6(4, "katre");
	//TreePair.insert(mypair);
	lol.insert(mypair);
	lol.insert(mypair2);
	lol.insert(mypair3);
	lol.insert(mypair4);
	lol.insert(mypair5);
	lol.insert(mypair6);
	lol.debugging();
	ft::map<int, std::string>::iterator it = lol.find(2); // renvoie it sur pair
	std::cout << "ICI BIG TEST " << (lol.find(2))->second << std::endl;
	it++;
	std::cout << "IT 1 = " << (*it).second << std::endl;
	it--;
	std::cout << "IT 1 = " << (*it).second << std::endl;

	ft::map<int, std::string>::reverse_iterator it2 = lol.find(2);
	std::cout << "IT 2 = " << (*it2).second << std::endl;
	std::cout << "SIZE = " << lol.size() << std::endl;
	std::cout << "BEGIN = " << lol.begin()->second << std::endl;
	std::cout << "END -- = " << (--lol.end())->second << std::endl;
	ft::map<int, std::string>::reverse_iterator rev_it1 = lol.rbegin();
	while (rev_it1 != lol.rend())
	{
		std::cout << "REBEGIN=" << rev_it1->second << std::endl;
		rev_it1++;
	}
	rev_it1 = lol.rend();
	while (rev_it1 != lol.rbegin())
	{
		rev_it1--;
		std::cout << "REND=" << rev_it1->second << std::endl;
		
	}



	//ft::Tree<ft::pair <int, std::string> >   	TreePair;
	std::map<int, std::string> test;
	std::map<int, std::string>::reverse_iterator test_it(test.end());
	test.insert(std::make_pair<int, std::string>(1, "uno"));
	test.insert(std::make_pair<int, std::string>(2, "dos"));
	test.insert(std::make_pair<int, std::string>(3, "tres"));
	test.insert(std::make_pair<int, std::string>(0, "zero"));
	test.insert(std::make_pair<int, std::string>(73, "soixante tres"));
	test.insert(std::make_pair<int, std::string>(4, "katre"));
	std::cout << (*test_it).second << std::endl;
	test_it++;
	std::cout << (*test_it).first << std::endl;
	std::cout << (--test.end())->second << std::endl;
	test_it = test.rbegin();
	
	while (test_it!= test.rend())
	{
		std::cout << "REAL REBEGIN=" << test_it->second << std::endl;
		test_it++;
	}
	test_it = test.rend();
	while (test_it != test.rbegin())
	{
		test_it--;
		std::cout << "REAL REND=" << test_it->second << std::endl;		
	}
	display(lol, test);



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

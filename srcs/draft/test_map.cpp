
#include "../utils/debug.hpp"
//#include "../includes/utils/debug.hpp"
#include "map.hpp"
#include "ft_tree_vis.cpp"
#include <map>
#include "../includes.hpp"
#include <memory>


#define start head("Test : " << __func__ << " "); 	srand (time(NULL));
#define finish head("End of test : " << __func__ << " ");
#define wait_see               \
	display(my_map, real_map); \
	getwchar();

using namespace std;

/*
**	PRINT FUNCTIONS
**
**
*/


/*
**	TEST FUNCTIONS
**
**
*/


void	reverse_iterators()
{
	start;
	int a = rand() % 89 + 1;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "C'est", "Une", "Phrase", "A", "L'envers", "Pour Tester","Les reverse" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(a, word_array[i]));
		real_map.insert(std::make_pair(a, word_array[i]));
		a = rand() % 89 + 1;
	}
	ft::map<int, std::string >::reverse_iterator ft_rev_it = my_map.rbegin();
	std::map<int, std::string>::reverse_iterator std_rev_it = real_map.rbegin();

	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;

	while (ft_rev_it != my_map.rend())
	{
		std::cout << *ft_rev_it << " ";
		ft_rev_it++;
	}
	out("");
	std::cout << FG2("\nReal :") << std::endl;
	while (std_rev_it != real_map.rend())
	{
		std::cout << *std_rev_it << " ";
		std_rev_it++;
	}
	out("");
	{
		ft::map<char, int> my_map;

		my_map['x'] = 100;
		my_map['y'] = 200;
		my_map['z'] = 300;

		ft::map<char, int>::reverse_iterator rit;
		for (rit = my_map.rbegin(); rit != my_map.rend(); ++rit)
			cout << rit->first << " => " << rit->second << '\n';


		for (ft::map<char, int>::const_reverse_iterator it = my_map.rbegin(); it != my_map.rend(); it++)
			cout << it->first << " => " << it->second << '\n';

		ft::map<char, int>::const_reverse_iterator it = my_map.rbegin();
		ft::map<char, int>::const_reverse_iterator ti = my_map.rend();

		it++;
		++it;
		it--;
		--it;

		ti--;
		--ti;
		++ti;
		ti++;

		ti = it;

		// ft::map<char, int>::reverse_iterator end = my_map.rend();
		// while (it != end)
		// {
		// 	cout << it->first << " => " << it->second << '\n';
		// 	it++;
		// }
	}
}

void 	iterators_test()
{
	start;
	int a = rand() % 89 + 1;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Maitre Gims", "Orelsan", "Jimmy Hendrix", "Stromae", "Mozart", "Beethoven" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(a, word_array[i]));
		real_map.insert(std::make_pair(a, word_array[i]));
		a = rand() % 89 + 1;
	}
	wait_see;
	ft::map<int, std::string>::iterator		my_map_it = my_map.end();
	std::map<int, std::string>::iterator	real_map_it = real_map.end();


	// out("End :" << *(my_map_it));
	// out("End :" << *(real_map_it));
	out("--End :" << *(--my_map_it));
	out("--End :" << *(--real_map_it));
	out("Begin :" << *(my_map.begin()));
	out("Begin :" << *(real_map.begin()));
	out("Begin++ :" << *(my_map.begin()++));
	out("Begin++ :" << *(real_map.begin()++));
	out("++Begin :" << *(++my_map.begin()));
	out("++Begin :" << *(++real_map.begin()));
	out("End :" << *(real_map_it));
	out("End :" << *(my_map_it));
	out("End-- :" << *(real_map_it--));
	out("End-- :" << *(my_map_it--));
	finish;
}

void basic_tests_insert_erase()
{
	start;
	ft::map<int, std::string>	my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Ce matin", "a Marseille", "nous avons vu", "des poissons", "dans le ciel", "car nous aimons", "la bouillabaisse" };
	int int_array[] = { 1, 2, 3, 4, 58, 65, 75, 65, 23 };
	for (int i = 0; i < 7; i++)
	{
		my_map.insert(ft::make_pair(int_array[i], word_array[i]));
		real_map.insert(std::make_pair(int_array[i], word_array[i]));
	}
	wait_see;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "DELETING " << word_array[i] << std::endl;
		my_map.erase(int_array[i]);
		real_map.erase(int_array[i]);
	}
	wait_see;
	for (int i = 3; i < 7; i++)
	{
		std::cout << "DELETING " << word_array[i] << std::endl;
		my_map.erase(int_array[i]);
		real_map.erase(int_array[i]);
	}
	wait_see;
	finish;
}

void fifty_insert_test()
{
	start;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "fifty", "value", "are", "going", "to" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(i + 4, word_array[i]));
		real_map.insert(std::make_pair(i + 4, word_array[i]));
	}
	my_map.erase(5);
	real_map.erase(5);
	wait_see;
	my_map.debugging();
	wait_see;
}


void		delete_same_value_test()
{
	start;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Delete", "Same", "Value", "Test" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(i + 4, word_array[i]));
		real_map.insert(std::make_pair(i + 4, word_array[i]));
	}
	//my_map.debugging();
	//wait_see;
	my_map.erase(4);
	real_map.erase(4);
	//wait_see;
	my_map.erase(4);
	real_map.erase(4);
	//wait_see;
	finish;
}

void		insert_same_value_test()
{
	start;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Insert", "Same", "Value", "Test" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(i + 4, word_array[i]));
		real_map.insert(std::make_pair(i + 4, word_array[i]));
	}
	// Key, not value does import.
	my_map.insert(ft::make_pair(5, "not supposed"));
	real_map.insert(std::make_pair(5, "not supposed"));
	wait_see;
	finish;
}


void		tricky_pairs_test()
{
	start;
	ft::map < ft::pair<int, int>, std::string>	my_map;
	std::map< std::pair<int, int>, std::string>	real_map;

	std::make_pair(std::make_pair(1, 2), "One two");
	ft::make_pair(ft::make_pair(1, 2), "One two");
	my_map.insert(ft::make_pair(ft::make_pair(1, 2), "One two"));
	real_map.insert(std::make_pair(std::make_pair(1, 2), "One two"));

	ft::pair<ft::pair<int, int>, std::string> mypairs[10];
	std::pair<std::pair<int, int>, std::string> realpairs[10];

	std::string word_array[] = { "Very", "Tricky", "Stuff", "Here" };
	for (int i = 0; i < 4; i++)
	{
		my_map.insert(ft::make_pair(ft::make_pair(i, i + 10), word_array[i]));
		real_map.insert(std::make_pair(std::make_pair(i, i + 10), word_array[i]));
	}
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << my_map[ft::make_pair(i, i + 10)] << " ";
	out("");
	std::cout << FG2("Real :") << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << real_map[std::make_pair(i, i + 10)] << " ";
	out("")
		finish;
}

void access_operator_test()
{
	start;
	int a = rand() % 100 + 1;
	ft::map<int, std::string>	my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Can", "You", "Access", "Me ?" };
	for (int i = 0; i < 4; i++)
	{
		a = rand() % 100 + 1;
		my_map.insert(ft::make_pair(a, word_array[i]));
		real_map.insert(std::make_pair(a, word_array[i]));
	}
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	std::cout << my_map[a] << " ";
	out("");
	std::cout << FG2("Real : ") << std::endl;
	std::cout << real_map[a] << " ";
	out("")
		test("Impossible index : ")
		std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	std::cout << my_map[709] << " ";
	out("");
	std::cout << FG2("Real :") << std::endl;
	std::cout << real_map[709] << " ";
	out("")
}

void count_test2()
{
	start;
	ft::map<int, std::string>	my_map;
	std::map<int, std::string>	real_map;
	std::string word_array[] = { "Ce matin", "a Marseille", "nous avons vu", "des poissons", "dans le ciel", "car nous aimons", "la bouillabaisse" };
	int int_array[] = { 1, 2, 3, 4, 58, 62, 75, 65, 23 };
	for (int i = 0; i < 7; i++)
	{
		my_map.insert(ft::make_pair(int_array[i], word_array[i]));
		real_map.insert(std::make_pair(int_array[i], word_array[i]));
	}
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	std::cout << my_map.count(2) << " " << real_map.count(78); out("");
	std::cout << FG2("Real :") << std::endl;
	std::cout << real_map.count(2) << " " << real_map.count(78); out("");

	ft::map<int, std::string>::const_iterator	my_map1 = my_map.begin();
	std::map<int, std::string>::const_iterator	std_Map1 = real_map.begin();
	ft::map<int, std::string>::iterator	my_reg_it = my_map.begin();
	std::map<int, std::string>::iterator std_reg_it = real_map.begin();

	std_reg_it->second = "fuck"; // compiler
	//std_Map1->second = "fuck"; // ne va pas cmpiler

	my_reg_it->second = "fuck"; // compiler car non-const
	//my_map1->second = "fuck"; // ne va pas cmpiler
	out(*my_map1);
	*my_map1++;
	out(*my_map1);
	*my_map1++;

	out(*std_Map1);
	*std_Map1++;
	out(*std_Map1);
	*std_Map1++;

	std_Map1++;
	my_map1++;
	out(*std_Map1);
	out(*my_map1);


}


void erase_iterator_test()
{
	start;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;
	out("APRES CONSTRUCTION")
		std::string word_array[] = { "Erase", "Me", "With", "iterators" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(i + 9, word_array[i]));
		real_map.insert(std::make_pair(i + 9, word_array[i]));
	}
	real_map.erase(real_map.begin(), --real_map.end());
	my_map.erase(my_map.begin(), --my_map.end());
	wait_see;
}


void insert_iterator_test()
{
	start;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;

	ft::map<int, std::string> my_map2;
	std::map<int, std::string>	real_map2;

	std::string word_array[] = { "Erase", "Me", "With", "iterators" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(ft::make_pair(i + 9, word_array[i]));
		real_map.insert(std::make_pair(i + 9, word_array[i]));
	}

	std::string word_array2[] = { "second", "try", "of ", "insert" };
	for (int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map2.insert(ft::make_pair(i + 49, word_array2[i]));
		real_map2.insert(std::make_pair(i + 49, word_array2[i]));
	}
	ft::map<int, std::string>::iterator beg = my_map2.begin();
	real_map.insert(real_map2.begin(), real_map2.end());
	//real_map.insert(lol.begin(), lol.end());		   // ne compile pas, deducted conflicting types...
	my_map.insert(real_map2.begin(), real_map2.end()); // mais moi ok
	my_map.insert(my_map2.begin(), my_map2.end()); // ca ok


	//my_map.erase(my_map.begin(), --my_map.end());
	out("Lower bound")
		out(*my_map.lower_bound(54));
	//	out(*real_map.lower_bound(54)); // le real segfault

	wait_see;
}


void leaks_erase()
{
	start;
	ft::map<int, std::string> my_map;
	std::map<int, std::string>	real_map;

	my_map.insert(ft::make_pair(1, "a supp"));
	my_map.insert(ft::make_pair(2, "a supp2"));
	//my_map.debugging();
	getwchar();
	my_map.erase(2);
	//my_map.debugging();
	wait;
}

void count_test()
{
	start;
	ft::map<char, int> mymap;
	char c;

	mymap['a'] = 101;
	std::cout << "assigned 'a' \n";
	std::cout << mymap['a'] << std::endl;
	mymap['c'] = 202;
	std::cout << mymap['c'] << "    " << mymap['a'] << std::endl;
	std::cout << "assiged 'c'\n";
	mymap['f'] = 303;
	std::cout << "assigned 'f'\n";

	std::cout << "Map x " << mymap['x'] << std::endl;
	cout << "end of assignations\n";
	for (c = 'a'; c < 'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c) > 0)
			std::cout << " is an element of mymap.\n";
		else
			std::cout << " is not an element of mymap.\n";
	}
}

void simple_erase_it()
{
	start;
	ft::map<char, int> mymap;
	ft::map<char, int>::iterator it;

	// insert some values:
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['e'] = 50;
	mymap['f'] = 60;

	it = mymap.find('b');
	cout << "found b\n";

	mymap.erase(it);                   // erasing by iterator

	cout << "erase iterator to b\n";
	//  mymap.debugging();
	wait;
	mymap.erase('c');                  // erasing by key
	cout << "erase by key 'c'\n";
	//      //mymap.debugging();
	// 	wait;
	it = mymap.find('e');
	cout << "erase by range 'e' to end\n";   mymap.erase(it, mymap.end());    // erasing by range
  //     // mymap.debugging();
  // 	wait;


	cout << " display :\n";
	// mymap.debugging();
	 // show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		cout << it->first << " => " << it->second << '\n';
}



void 		simple_insert()
{
	// first insert function version (single parameter):
	ft::map<char, int> mymap;
	//ft::map<char,int>::iterator it;


	mymap.insert(ft::pair<char, int>('a', 100));
	mymap.insert(ft::pair<char, int>('z', 200));

	ft::pair<ft::map <char, int>::iterator, bool> ret;
	ret = mymap.insert(ft::pair<char, int>('z', 500));
	if (ret.second == false) {
		std::cout << "element 'z' already exists";
		std::cout << " with a value of " << ret.first->second << '\n';//->second << '\n';
	}

	// second insert function version (with hint position):
	ft::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, ft::pair<char, int>('b', 300));  // max efficiency inserting
	mymap.insert(it, ft::pair<char, int>('c', 400));  // no max efficiency inserting

	// third insert function version (range insertion):
	ft::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it = anothermap.begin(); it != anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void lower_bounds()
{
	start;
	ft::map<char, int> mymap;
	ft::map<char, int>::iterator itlow, itup;

	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;


	itlow = mymap.lower_bound('b');  // itlow points to b
	itup = mymap.upper_bound('d');   // itup points to e (not d!)

	cout << "low : " << itlow->first << '\n';
	cout << "up : " << itup->first << '\n';
	getwchar();
	// mymap.debugging();

	mymap.erase(itlow, itup);        // erases [itlow,itup)
	  // mymap.debugging();
	// print content:
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	finish;
}



void 	swap_test()
{
	start;
	ft::map<char, int> mymap;
	ft::map<char, int> mymap2;
	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;

	mymap2['z'] = 20;
	mymap2['y'] = 40;
	// mymap2['x'] = 60;
	// mymap2['t'] = 80;
	// mymap2['o'] = 100;

	mymap2.swap(mymap);
	for (ft::map<char, int>::iterator it = mymap2.begin(); it != mymap2.end(); it++)
		std::cout << "did it swap ?" << it->first << " " << it->second << std::endl;

	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); it++)
		std::cout << "2did it swap ?" << it->first << " " << it->second << std::endl;

	{
		ft::map<char, int> foo, bar;

		foo['x'] = 100;
		foo['y'] = 200;

		bar['a'] = 11;
		bar['b'] = 22;
		bar['c'] = 33;


		ft::map<char, int>::const_iterator tmp = foo.begin(); //tmp iterates through foo
		ft::map<char, int>::const_iterator tmp2 = bar.begin(); //tmp2 iterates through bar

		foo.swap(bar); //tmp iterates through bar
					  //tmp2 iterates through foo


		ft::map<char, int>	other;

		other['1'] = 73;
		other['2'] = 173;
		other['3'] = 763;
		other['4'] = 73854;
		other['5'] = 74683;
		other['6'] = 753;

		ft::map<char, int>::const_iterator tmp3 = other.begin(); // tmp3 iterates through other

		cout << "foo contains:\n";
		for (ft::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
			cout << it->first << " => " << it->second << '\n';
		cout << "bar contains:\n";
		for (ft::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
			cout << it->first << " => " << it->second << '\n';

		while (tmp != bar.end())
		{
			cout << tmp->first << " => " << tmp->second << '\n';
			tmp++;
		}
		tmp--;


		exit(0);
	}


}

void time_test()
{
	ft::map<int, int> foo;
	int a = 0, b = 80000;
	for (int i = 0; i < 200000; i++)
	{
		if (a%2 == 0)
			foo.insert(ft::make_pair(a, b));
		else
			foo.insert(ft::make_pair(b, a));
		a++;
		b--;
	}
	std::cout << foo.size() << "ok " << foo[78] << "\n";
	ft::map<int, int>::iterator it = foo.begin();
	while (it != foo.end())
	{
		ft::map<int, int>::iterator tmp = it;
		it++;
		foo.erase(tmp);
	}

	std::cout << foo.size() << "ok\n";

	// std::map<int, int> foo;
	// int a = 0, b = 920;
	// for (int i = 0; i < 100000; i++)
	// {
	// 	if (a%2 == 0)
	// 		foo.insert(std::make_pair(a, b));
	// 	else
	// 		foo.insert(std::make_pair(b, a));
	// }
	// std::cout << "ok\n";
}

int main()
{

	void (*functptr[])() = {
		//simple_erase_it,
		//simple_insert,
		//leaks_erase,
		//basic_tests_insert_erase,
		//count_test,
		// fifty_insert_test,
		// iterators_test,
		//reverse_iterators,
		//delete_same_value_test,
		//insert_same_value_test,
		// tricky_pairs_test,
		// access_operator_test,
		//	erase_iterator_test,
		//insert_iterator_test,
		//count_test2,
		//lower_bounds,
		//swap_test,
		time_test
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		(*functptr[i])();    /*  Call first function  */
	//	getwchar();

	}
}
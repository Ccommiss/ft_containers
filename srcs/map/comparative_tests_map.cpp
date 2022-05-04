#include "../tests.hpp"

using namespace NM;

void insert()
{
	start;
	map<int, int> test_1;
	int a, b;
	for (unsigned int i = 0; i < 10000; i++)
	{
		i % 2 == 0 ? a = i * 2 : i * 5;
		i % 2 == 0 ? b = i * 6 : i;
		test_1.insert(make_pair(a, b));
	}
	out(test_1.size());
	finish;
}

void erase()
{
	start;
	out(FG1("Part 1"));

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
	// Ne reste que ces 4 la a la fin
	print(test_1);

	map<int, int>::iterator it;
	// erase it
	for (it = test_1.begin(); it != test_1.end();)
	{
		map<int, int>::iterator tmp;
		if (it->first % 2 == 0)
		{
			tmp = it;
			it++;
			test_1.erase(tmp);
		}
		else
			it++;
	}
	print(test_1);
	test_1.erase(17);
	print(test_1);

	{
		out(FG1("Part 2"));

		map<int, std::string> my_map;
		std::string word_array[] = {"Erase", "Me", "With", "iterators"};
		for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
			my_map.insert(pair<int, std::string>(i + 9, word_array[i]));

		my_map.erase(my_map.begin(), --my_map.end());
		print(my_map);
	}
	finish;
}


void	big_big_insert_erase()
{
	start;
	map<int, int> test_1;
	for (unsigned int i = 0; i < 10000; i++)
	{
		test_1.insert(make_pair(i, i * 4));
	}
	out("Size after insert : " << test_1.size());
	for (unsigned int i = 0; i < 18000; i++)
	{
		test_1.erase(i / 2);
	}
	out("Size after : " << test_1.size());
	finish;
}

void iterators()
{
	start;
	int a = rand() % 89 + 1;
	map<int, std::string> my_map;
	std::string word_array[] = {"Toto", "Est", "Un", "Sacre", "Blagueur", "Non ?"};
	for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(pair<int, std::string>(a, word_array[i]));
		a = rand() % 89 + 1;
	}
	print(my_map);
	map<int, std::string>::iterator my_map_it = my_map.end();
	out("--End :" << *(--my_map_it));
	out("Begin :" << *(my_map.begin()));
	out("Begin++ :" << *(my_map.begin()++));
	out("++Begin :" << *(++my_map.begin()));
	out("End :" << *(my_map_it));
	out("End-- :" << *(my_map_it--));
	finish;
}

void reverse_iterators()
{
	start;
	int a = 50;
	map<int, std::string> my_map;
	std::string word_array[] = {"C'est", "Une", "Phrase", "A", "L'envers", "Pour Tester", "Les reverse"};
	for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(pair<int, std::string>(a, word_array[i]));
		a % 2 == 0 ? a -= 3 : a += 8;
	}
	map<int, std::string>::reverse_iterator ft_rev_it = my_map.rbegin();

	std::cout << BOLD("-> output : ") << std::endl;
	while (ft_rev_it != my_map.rend())
	{
		std::cout << *ft_rev_it << " ";
		ft_rev_it++;
	}
	out("");

	{
		map<char, int> my_map;
		my_map['x'] = 100;
		my_map['y'] = 200;
		my_map['z'] = 300;

		map<char, int>::reverse_iterator rit;
		for (rit = my_map.rbegin(); rit != my_map.rend(); ++rit)
			out(rit->first << " => " << rit->second << '\n');

		for (map<char, int>::const_reverse_iterator it = my_map.rbegin(); it != my_map.rend(); it++)
			out(it->first << " => " << it->second << '\n');

		map<char, int>::const_reverse_iterator it = my_map.rbegin();
		map<char, int>::const_reverse_iterator ti = my_map.rend();
		out("Rbegin : " << *it);
		it++;
		++it;
		out("Avance de deux : " << *it);
		it--;
		--it;
		out("Revenu a rbegin() :" << *it);

		out("--Rend (= begin, because rend is past first elem) : " << *--ti);
		ti--;
		--ti;
		out("Meeting last elem :" << *ti);
		++ti;
		ti++;
		if (++ti == my_map.rend())
			out("Rend back reached again !");

		ti = it;
		out(*ti);

		map<char, int>::reverse_iterator end = my_map.rend();
		while (it != end)
		{
			out(it->first << " => " << it->second);
			it++;
		}
	}
}

void swap()
{
	map<int, char> map1;
	map<int, char> map2;

	map1[45] = 'n';
	map1[68] = 'u';
	map1[79] = 'l';
	map2[12] = 'd';
	map2[85] = 'e';
	map2[101] = 'u';
	map2[156] = 'z';

	out(BOLD("\n--- BEFORE SWAP --- \n"))
		out(DIM("Map1 === >"))
			print(map1);
	out(DIM("Map2 === >"))
		print(map2);
	map<int, char>::iterator it = map1.begin();

	out("\n*it value:");
	out(*it);

	map1.swap(map2);
	out(BOLD("--- AFTER SWAP ---\n"))
		out(DIM("Map1 now contains"))
			print(map1);
	out(DIM("Map2 now contains"))
		print(map2);
	out("\n*it still valid:");
	out(*it);
}

void count()
{
	start;
	map<int, std::string> my_map;
	std::string word_array[] = {"Ce matin", "rigolo", "foutaise", "i love coding", "i like trees", "jellyfish", "yop", "samedi", "la capmpagne", "un ascenseur", "David Bowie", "cadavre exquis", "le dadaisme", "Andre Breton", "Alan Ginsberg", "Jack Kerouac", "a Marseille", "nous avons vu",
								"des poissons", "dans le ciel", "car nous aimons", "la bouillabaisse"};

	int a = 50;
	for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_map.insert(pair<int, std::string>(a, word_array[i]));
		a += 8;
	}
	out("Should fail : " << my_map.count(3));
	out("Should succeed : " << my_map.count(50));
	out("Should fail : " << my_map.count(196));
	out("Should succeed : " << my_map.count(58));
	finish;
}

void bounds_equal_range()
{

	out(FG1("Part 1"));
	{
		map<char, int> mymap;
		map<char, int>::iterator itlow, itup;

		mymap['a'] = 20;
		mymap['b'] = 40;
		mymap['c'] = 60;
		mymap['d'] = 80;
		mymap['e'] = 100;

		itlow = mymap.lower_bound('b'); //  b
		itup = mymap.upper_bound('d');	// e

		out("low : " << itlow->first << '\n');
		out("up : " << itup->first << '\n');

		mymap.erase(itlow, itup);
		for (map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	out(FG1("Part 2"));
	{
		map<int, std::string> my_map;
		std::string word_array[] = {"Ce matin", "rigolo", "foutaise", "i love coding", "i like trees", "jellyfish", "yop", "samedi", "la capmpagne", "un ascenseur", "David Bowie", "cadavre exquis", "le dadaisme", "Andre Breton", "Alan Ginsberg", "Jack Kerouac", "a Marseille", "nous avons vu",
									"des poissons", "dans le ciel", "car nous aimons", "la bouillabaisse"};

		int a = 50;
		for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
		{
			my_map.insert(pair<int, std::string>(a, word_array[i]));
			a += 8;
		}

		out("Equal of existing  :" << *(my_map.equal_range(66).first) << " and " << *(my_map.equal_range(66).second));

		out("Equal		:" << *(my_map.equal_range(51).first) << " and " << *(my_map.equal_range(51).second));
	}
	finish;
}

void empty()
{
	start;
	map<int, std::string> my_map;
	out("Is empty ? => " << std::boolalpha << my_map.empty());
	my_map.insert(pair<int, std::string>(5, "bonjour"));
	out("Is empty ? => " << std::boolalpha << my_map.empty());
	my_map.clear();
	out("Is empty ? => " << std::boolalpha << my_map.empty());
}

void operators()
{
	start;
	{
		out(FG1("Part 1"));

		map<char, int> foo, bar;
		foo['a'] = 100;
		foo['b'] = 200;
		bar['a'] = 10;
		bar['z'] = 1000;

		if (foo == bar)
			std::cout << "foo and bar are equal\n";
		if (foo != bar)
			std::cout << "foo and bar are not equal\n";
		if (foo < bar)
			std::cout << "foo is less than bar\n";
		if (foo > bar)
			std::cout << "foo is greater than bar\n";
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar\n";
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar\n";
	}
	{
		out(FG1("Part 2"));
		map<char, int> foo, bar;
		bar['a'] = 100;
		bar['b'] = 100;
		foo['a'] = 100;
		foo['5'] = 1000;
		foo['z'] = 1000;

		if (foo == bar)
			std::cout << "foo and bar are equal\n";
		if (foo != bar)
			std::cout << "foo and bar are not equal\n";
		if (foo < bar)
			std::cout << "foo is less than bar\n";
		if (foo > bar)
			std::cout << "foo is greater than bar\n";
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar\n";
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar\n";
	}
	finish;
}

void tricky_pairs_test()
{
	start;
	map<pair<int, int>, std::string> my_map;
	my_map.insert(pair<pair<int, int>, std::string>(pair<int, int>(1, 2), "One two"));

	std::string word_array[] = {"Very", "Tricky", "Stuff", "Here"};
	for (int i = 0; i < 4; i++)
	{
		my_map.insert(pair<pair<int, int>, std::string>(pair<int, int>(i, i + 10), word_array[i]));
	}
	print(my_map);
	out("")
		finish;
}

void access_operators_test()
{
	start;
	int a = rand() % 100 + 1;
	map<int, std::string> my_map;
	std::string word_array[] = {"Can", "You", "Access", "Me ?"};
	for (int i = 0; i < 4; i++)
	{
		a = rand() % 100 + 1;
		my_map[a] = word_array[i];
	}
	out(FG1("-> output :"));
	std::cout << my_map[a] << "\n";
	out(FG1("-> Impossible index : "));
	std::cout << my_map[709] << " ";
	out("")
}

void comparative_tests_map()
{
	insert();
	erase();
	big_big_insert_erase();
	iterators();
	reverse_iterators();
	swap();
	count();
	bounds_equal_range();
	empty();
	operators();
	tricky_pairs_test();
	access_operators_test();
}

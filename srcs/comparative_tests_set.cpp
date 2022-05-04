#include "tests.hpp"
#include <assert.h>

using namespace NM;

void static  insert()
{
	start;
  set<int> my_set;
 
  pair<set<int>::iterator, bool>  result_1 = my_set.insert(3);
  assert(result_1.first != my_set.end()); // it's a valid iterator
  assert(*result_1.first == 3);
  if (result_1.second)
    std::cout << "insert done\n";
 
  pair<set<int>::iterator, bool> result_2 = my_set.insert(3);
  assert(result_2.first == result_1.first); // same iterator
  assert(*result_2.first == 3);
  if (!result_2.second)
    std::cout << "no insertion\n";

	print(my_set);
	finish;
}

void static  erase()
{
	start;

    set<int> c;
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    c.insert(array, array + 7);
 
    print(c);
 
    std::cout << "Erase all odd numbers:\n";
    for(set<int>::iterator it = c.begin(); it != c.end(); ) 
    {
        set<int>::iterator tmp = it;
        it++;
        if(*tmp % 2 != 0)
        {
            c.erase(tmp);
        }
    }
    print(c);
 
    std::cout << "Erase 1, erased count: " << c.erase(1) << '\n';
    std::cout << "Erase 2, erased count: " << c.erase(2) << '\n';
    std::cout << "Erase 2, erased count: " << c.erase(2) << '\n';
    print(c);
	finish;
}


// void	big_big_insert_erase()
// {
// 	start;
// 	set<int> test_1;
// 	for (unsigned int i = 0; i < 10000; i++)
// 	{
// 		test_1.insert(make_pair(i, i * 4));
// 	}
// 	out("Size after insert : " << test_1.size());
// 	for (unsigned int i = 0; i < 18000; i++)
// 	{
// 		test_1.erase(i / 2);
// 	}
// 	out("Size after : " << test_1.size());
// 	finish;
// }

void static  iterators()
{
	start;
	int a = rand() % 89 + 1;
	set< pair<int, std::string> > my_set;
	std::string word_array[] = {"Toto", "Est", "Un", "Sacre", "Blagueur", "Non ?"};
	for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_set.insert(pair<int, std::string>(a, word_array[i]));
		a = rand() % 89 + 1;
	}
	print(my_set);
	set< pair<int, std::string> > ::iterator my_set_it = my_set.end();
	out("--End :" << *(--my_set_it));
	out("Begin :" << *(my_set.begin()));
	out("Begin++ :" << *(my_set.begin()++));
	out("++Begin :" << *(++my_set.begin()));
	out("End :" << *(my_set_it));
	out("End-- :" << *(my_set_it--));
	finish;
}

void static  reverse_iterators()
{
	start;
    {
        out(FG1("Part 1"));

	set<std::string> my_set;
	std::string word_array[] = {"C'est", "Une", "Phrase", "A", "L'envers", "Pour Tester", "Les reverse"};
	for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
	{
		my_set.insert(word_array[i]);
	}
	set<std::string>::reverse_iterator ft_rev_it = my_set.rbegin();

	std::cout << BOLD("-> output : ") << std::endl;
	while (ft_rev_it != my_set.rend())
	{
		std::cout << *ft_rev_it << " ";
		ft_rev_it++;
	}
	out("");
    }
	{
        out(FG1("Part 2"));

		set<int> my_set;
		my_set.insert(100);
        my_set.insert(400);
        my_set.insert(600);

		set<int>::reverse_iterator rit;
		for (rit = my_set.rbegin(); rit != my_set.rend(); ++rit)
			std::cout << (*rit) << " ";
        out("")

		for (set<int>::const_reverse_iterator it = my_set.rbegin(); it != my_set.rend(); it++)
		    std::cout << (*it) << " ";
        out("")

		set<int>::const_reverse_iterator it = my_set.rbegin();
		set<int>::const_reverse_iterator ti = my_set.rend();
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
		if (++ti == my_set.rend())
			out("Rend back reached again !");

		ti = it;
		out(*ti);

		set<int>::reverse_iterator end = my_set.rend();
		while (it != end)
		{
			out(*it);
			it++;
		}
	}
}

void static  swap()
{
	set<char> set1;
	set<char> set2;

    char array1[] = {'n', 'u', 'l'};
    char array2[] = {'d', 'e', 'u', 'z'};
    set1.insert(array1, array1 + 3);
    set2.insert(array2, array2 + 4);

	out(BOLD("\n--- BEFORE SWAP --- \n"))
		out(DIM("set1 === >"))
			print(set1);
	out(DIM("set2 === >"))
		print(set2);
	set<char>::iterator it = set1.begin();

	out("\n*it value:");
	out(*it);

	set1.swap(set2);
	out(BOLD("--- AFTER SWAP ---\n"))
		out(DIM("set1 now contains"))
			print(set1);
	out(DIM("set2 now contains"))
		print(set2);
	out("\n*it still valid:");
	out(*it);
}

void static  count()
{
	start;
	set<int> my_set;

	int a = 50;
	for (unsigned int i = 0; i < 10; i++)
	{
		my_set.insert(a);
		a += 8;
	}
	out("Should fail : " << my_set.count(3));
	out("Should succeed : " << my_set.count(50));
	out("Should fail : " << my_set.count(196));
	out("Should succeed : " << my_set.count(58));
	finish;
}

void static  bounds_equal_range()
{

	out(FG1("Part 1"));
	{
		set<pair<char, int> > myset;
		set<pair<char, int> >::iterator itlow, itup;

		myset.insert(pair<char, int>('a', 20));
		myset.insert(pair<char, int>('b', 40));
		myset.insert(pair<char, int>('c', 60));
		myset.insert(pair<char, int>('d', 80));
		myset.insert(pair<char, int>('e', 100));
		itlow = myset.lower_bound(pair<char, int>('b', 40)); //  b
		itup = myset.upper_bound(pair<char, int>('d', 80));	// e

		out("low : " << *itlow << '\n');
		out("up : " << *itup << '\n');

		myset.erase(itlow, itup);
		for (set<pair<char, int> >::iterator it = myset.begin(); it != myset.end(); ++it)
			std::cout << *it << '\n';
	}

	out(FG1("Part 2"));
	{
		set<pair<int, std::string> > my_set;
		std::string word_array[] = {"Ce matin", "rigolo", "foutaise", "i love coding", "i like trees", "jellyfish", "yop", "samedi", "la capmpagne", "un ascenseur", "David Bowie", "cadavre exquis", "le dadaisme", "Andre Breton", "Alan Ginsberg", "Jack Kerouac", "a Marseille", "nous avons vu",
									"des poissons", "dans le ciel", "car nous aimons", "la bouillabaisse"};

		int a = 50;
		for (unsigned int i = 0; i < sizeof(word_array) / sizeof(word_array[0]); i++)
		{
			my_set.insert(pair<int, std::string>(a, word_array[i]));
			a += 8;
		}

		out("Equal of existing  :" << *(my_set.equal_range(pair<int, std::string>(50, "Ce matin")).first)); 

		out("Equal		:" << *(my_set.equal_range(pair<int, std::string>(55, "Ce matin")).first));
	}
	finish;
}

void static  empty()
{
	start;
	set<pair<int, std::string> > my_set;
	out("Is empty ? => " << std::boolalpha << my_set.empty());
	my_set.insert(pair<int, std::string>(5, "bonjour"));
	out("Is empty ? => " << std::boolalpha << my_set.empty());
	my_set.clear();
	out("Is empty ? => " << std::boolalpha << my_set.empty());
    finish;
}



void   comparative_tests_set()
{
	insert();
	erase();
    count();
	iterators();
	reverse_iterators();
	swap();
	bounds_equal_range();
	empty();
}


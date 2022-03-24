# include "includes.hpp"
#include <vector>

using namespace std;

void example(std::vector<int>& r_vec)
{
	std::cout << BOLD("-> example with real vector only : ") << std::endl;
	std::cout << FG2("Real :") << std::endl;
	std::vector<int>::iterator it;
	for (it = r_vec.begin(); it != r_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

}

template <typename T>
void display(ft::vector<T>& my_vec, std::vector<T>& r_vec)
{
	std::cout << BOLD("-> output : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	typename ft::vector<T>::iterator it1;
	for (it1 = my_vec.begin(); it1 != my_vec.end(); it1++)
		std::cout << *it1 << " ";
	std::cout << std::endl;

	std::cout << FG2("Real :") << std::endl;
	typename std::vector<T>::iterator it;
	for (it = r_vec.begin(); it != r_vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	cout << DIM("Real size : ") << r_vec.size() << DIM(" VS my size : ") << my_vec.size() << endl;
	cout << DIM("Real capacity : ") << r_vec.capacity() << DIM(" VS my capacity : ") << my_vec.capacity() << endl << endl;
	if (r_vec.size() != my_vec.size() || r_vec.capacity() != my_vec.capacity())
		getwchar();
}

void	test_insert()
{
	cout << HEADER("\n**** TESTS INSERT ****") << endl;

	//cout << "** TESTING VECTORS OF SAME SIZE ** " << endl;
	std::vector<int> vec1(10, 8);
	std::vector<int> temoinv(10, 6);


	ft::vector<int>	my_vec(10, 8);
	ft::vector<int>	my_tem(10, 6);

	test("** TEST0 : construction ** ");
	display(my_vec, vec1);

	test("** TEST1 : insert(iterator position, const T& x) ** ");
	my_vec.insert(my_vec.begin() + 1, 30);
	vec1.insert(vec1.begin() + 1, 30);
	display(my_vec, vec1);

	test("** TEST2 : insert(iterator position, size_type n, const T& x)  ** ");
	my_vec.insert(my_vec.begin() + 5, 2, 404);
	vec1.insert(vec1.begin() + 5, 2, 404);
	display(my_vec, vec1);

	test("** TEST3 : insert(iterator position, InputIterator first, InputIterator last) ** ");

	my_vec.insert(my_vec.begin(), my_tem.begin(), my_tem.end());
	vec1.insert(vec1.begin(), temoinv.begin(), temoinv.end());
	display(my_vec, vec1);

	test("** TEST4 : insert avec wnd puis begin**");

	try
	{
		vec1.insert(vec1.begin(), temoinv.rend(), temoinv.rbegin());
		example(vec1);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}


}

void 	test_erase()
{
	cout << HEADER("\n**** TESTS ERASE ****") << endl;


	test("** TEST1 erase(iterator position) ** ");

	ft::vector<int>	my_vec(10, 8);
	std::vector<int> vec1(10, 8);

	my_vec.push_back(404);
	my_vec.insert(my_vec.begin(), 3);
	vec1.push_back(404);
	vec1.insert(vec1.begin(), 3);
	display(my_vec, vec1);
	my_vec.erase(my_vec.begin());
	vec1.erase(vec1.begin());
	display(my_vec, vec1);

	test("** TESTS erase(iterator first, iterator last)**");

	vec1.erase(vec1.begin() + 1, vec1.end() - 3);
	my_vec.erase(my_vec.begin() + 1, my_vec.end() - 3);
	display(my_vec, vec1);


	my_vec.push_back(1024);
	vec1.push_back(1024);
	display(my_vec, vec1);

	test("** TESTS POP BACK USING ERASE ** ");

	my_vec.pop_back();
	vec1.pop_back();
	display(my_vec, vec1);
	vec1.reserve(74832);
}


void 	test_construct()
{
	cout << "** TEST1 : insert nb ** " << endl;


}

void test_reserve()
{
	cout << HEADER("\n***TESTS RESERVE****") << endl;
	{
		ft::vector<int> 		my_vec(3, 8);
		std::vector<int> 		r_vec(3, 8);
		display(my_vec, r_vec);
		my_vec.reserve(46);
		r_vec.reserve(46);
		display(my_vec, r_vec);
		my_vec.push_back(78);
		r_vec.push_back(78);
		display(my_vec, r_vec);
		my_vec.push_back(78);
		r_vec.push_back(78);
		my_vec.push_back(78);
		r_vec.push_back(78);
		display(my_vec, r_vec);
		my_vec.pop_back();
		r_vec.pop_back();
		my_vec.pop_back();
		r_vec.pop_back();
		display(my_vec, r_vec);
	}
	{
		ft::vector<int> 		my_vec(10, 404);
		std::vector<int> 		r_vec(10, 404);
		display(my_vec, r_vec);

		my_vec.push_back(20);
		r_vec.push_back(20);
		display(my_vec, r_vec);
		my_vec.push_back(20);
		r_vec.push_back(20);
		display(my_vec, r_vec);
		my_vec.insert(my_vec.end(), 12, 707);
		r_vec.insert(r_vec.end(), 12, 707);
		display(my_vec, r_vec);
	}



	test("**TEST MAX SIZE EXCEPTION**");
	ft::vector<int> 		my_vec(10, 404);
	std::vector<int> 		r_vec(10, 404);
	try
	{
		my_vec.reserve(my_vec.max_size() + 1);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}


void		test_resize()
{
	cout << HEADER("\n***TESTS RESIZE****") << endl;

	cout << "Base" << endl;
	ft::vector<int> myvec(4, 5);
	std::vector<int> realvec(4, 5);
	display(myvec, realvec);

	cout << "Resize bigger" << endl;
	realvec.resize(40);
	myvec.resize(40);
	display(myvec, realvec);

	cout << "Resize smaller" << endl;
	realvec.resize(3);
	myvec.resize(3);
	display(myvec, realvec);

}


void 	test_strings()
{
	cout << HEADER("\n***TESTS VECTOR OF STRINGS****") << endl;

	test("Inserting through input iterator : ");
	std::vector<std::string> myvector;
	std::string myarray[] = { "Hi","hello","wassup" };
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	ft::vector<std::string> lol;
	std::string myarray2[] = { "Hi","hello","wassup" };
	lol.insert(lol.begin(), myarray2, myarray2 + 3);

	display < std::string >(lol, myvector);

	test("Erase several time : ");
	myvector.erase(myvector.begin());
	lol.erase(lol.begin());
	display < std::string >(lol, myvector);

	myvector.erase(myvector.begin(), myvector.end());
	lol.erase(lol.begin(), lol.end());
	display < std::string >(lol, myvector);



}


void test_access()
{
	cout << HEADER("\n***TESTS ACCESS ***") << endl;
	std::vector<std::string> myvector;
	std::string myarray[] = { "I am 1","I am 2","I am 3" };
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	ft::vector<std::string> lol;
	std::string myarray2[] = { "I am 1","I am 2","I am 3" };
	lol.insert(lol.begin(), myarray2, myarray2 + 3);

	test("** Test 1 : subscript [] accessing an existing elem ( n <= size ) **");
	std::cout << myvector[2] << std::endl;
	std::cout << lol[2] << std::endl;

	test("** Test 2 : subscript [] accessing an inexistant elem (n > size) **");
	std::cout << myvector[77] << std::endl;
	std::cout << lol[77] << std::endl;

	test("** Test 3 : at(n) accessing an existant elem (n <= size) **");
	std::cout << myvector.at(2) << std::endl;
	std::cout << lol.at(2) << std::endl;

	test("** Test 4 : at(n) accessing an inexistant elem (n > size) --> thrown exception **");
	std::cout << FG2("Real :") << std::endl;
	try
	{
		std::cout << myvector.at(77) << std::endl;
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}
	std::cout << FG1("Mine :") << std::endl;
	try
	{
		std::cout << lol.at(77) << std::endl;
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}

}

void		test_front_back()
{
	int myarray[] = { 45, 895, 452, 7895, 45487, 78 };

	cout << HEADER("**TESTS FRONT / BACK") << endl;
	std::vector<int> r_vec;
	r_vec.insert(r_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	ft::vector<int> my_vec;
	my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	display(my_vec, r_vec);

	test("testing front and back");
	cout << FG1("Mine") << endl;
	cout << my_vec.front() << " " << my_vec.back() << endl;

	cout << FG2("Real") << endl;
	cout << r_vec.front() << " " << r_vec.back() << endl;

}



void		tests_simple_it()
{
	cout << HEADER("**TESTS SIMPLE IT *** ") << endl;

	int myarray[] = { 10, 20, 30, 40, 50, 60 };

	std::vector<int> r_vec;
	r_vec.insert(r_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	ft::vector<int> my_vec;
	my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	display(my_vec, r_vec);

	test("*-* Test 1 : begin() et end() *-*");
	cout << FG1("Mine") << endl;
	cout << *(my_vec.begin()) << " " << *(my_vec.end() - 1) << endl;

	cout << FG2("Real") << endl;
	cout << *(r_vec.begin()) << " " << *(r_vec.end() - 1) << endl;

	test("** Test 2 : operators a++ **");
	std::vector<int>::iterator		it = r_vec.begin();
	ft::vector<int>::iterator		my_it = my_vec.begin();

	cout << "Start point : mine = " << *my_it << " vs real = " << *it << endl;

	cout << FG2("Real with a++") << endl;
	while (it != r_vec.end())
		cout << *(it++) << " ";
	cout << endl;

	cout << FG1("Mine with a++") << endl;
	while (my_it != my_vec.end())
		cout << *(my_it++) << " ";
	cout << endl;

	test("** Test 3 : operators ++a **");

	it = r_vec.begin();
	my_it = my_vec.begin();

	cout << "Start point : mine = " << *my_it << " vs real = " << *it << endl;

	cout << FG2("Real with ++a") << endl;
	while (it < r_vec.end() - 1)
		cout << *(++it) << " ";
	cout << endl;

	cout << FG1("Mine with ++a") << endl;
	while (my_it < my_vec.end() - 1)
		cout << *(++my_it) << " ";
	cout << endl;

	test("** Test 4 : operators a-- **");
	it = r_vec.end() - 1;
	my_it = my_vec.end() - 1;

	cout << FG2("Real with a--") << endl;
	while (it != r_vec.begin())
		cout << *(it--) << " ";
	cout << endl;

	cout << FG1("Mine with a--") << endl;
	while (my_it != my_vec.begin())
		cout << *(my_it--) << " ";
	cout << endl;

	test("** Test 5 : operators --a **");
	it = r_vec.end() - 1;
	my_it = my_vec.end() - 1;

	cout << FG2("Real with --a") << endl;
	while (it > r_vec.begin())
		cout << *(--it) << " ";
	cout << endl;

	cout << FG1("Mine with --a") << endl;
	while (my_it > my_vec.begin())
		cout << *(--my_it) << " ";
	cout << endl;

	test("**Comparisons**")
		it = r_vec.end();
	my_it = my_vec.end();
	std::cout << ft::distance(my_it, my_vec.begin()) << std::endl;
	std::cout << std::distance(it, r_vec.begin()) << std::endl;

}

void		tests_reverse()
{

	int myarray[] = { 45, 895, 452, 7895, 45487, 78 };

	cout << HEADER("**TESTS REVERSE *** ") << endl;


	std::vector<int> r_vec;
	r_vec.insert(r_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	ft::vector<int> my_vec;
	my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	display(my_vec, r_vec);

	// NOTE : REND A AFFICHER = BUFFER OVERFLOW ! VOIR SCHEMA

	test("*-* Test 1 : rbegin() et rend() *-*");
	cout << FG1("Mine") << endl;
	cout << *(my_vec.rbegin()) << " " << *(my_vec.rend().base()) << endl;

	cout << FG2("Real") << endl;
	cout << *(r_vec.rbegin()) << " " << *(r_vec.rend().base()) << endl;

	test("** Test 2 : operators a++ **");
	std::vector<int>::reverse_iterator		it = r_vec.rbegin();
	ft::vector<int>::reverse_iterator		my_it = my_vec.rbegin();

	cout << "Start point : mine = " << *my_it << " vs real = " << *it << endl;

	cout << FG2("Real with a++") << endl;
	debug("it + 1 = " << *(it + 1));
	while (it != r_vec.rend())
		cout << *(it++) << " ";
	cout << endl;

	cout << FG1("Mine with a++") << endl;
	debug("my_it + 1 = " << *(my_it + 1));
	while (my_it != my_vec.rend())
		cout << *(my_it++) << " ";
	cout << endl;

	test("** Test 3 : operators ++a **");

	it = r_vec.rbegin();
	my_it = my_vec.rbegin();

	cout << "Start point : mine = " << *my_it << " vs real = " << *it << endl;

	cout << FG2("Real with ++a") << endl;
	while (it < r_vec.rend() - 1)
		cout << *(++it) << " ";
	cout << endl;

	cout << FG1("Mine with ++a") << endl;
	while (my_it < my_vec.rend() - 1)
		cout << *(++my_it) << " ";
	cout << endl;

	test("** Test 4 : operators a-- **");
	it = r_vec.rend() - 1;
	my_it = my_vec.rend() - 1;

	cout << FG2("Real with a--") << endl;
	debug("it - 1 = " << *(it - 1));
	debug("r_vec rbegin() + 2 " << *(r_vec.rbegin() + 2));
	while (it != r_vec.rbegin())
		cout << *(it--) << " ";
	cout << endl;

	cout << FG1("Mine with a--") << endl;
	debug("my_it - 1 = " << *(my_it - 1));
	debug("my_vec rbegin() + 2 " << *(my_vec.rbegin() + 2));
	while (my_it != my_vec.rbegin())
		cout << *(my_it--) << " ";
	cout << endl;

	test("** Test 5 : operators --a **");
	it = r_vec.rend() - 1;
	my_it = my_vec.rend() - 1;

	cout << "Start point : mine = " << *my_it << " vs real = " << *it << endl;
	cout << "Last point : mine = " << *my_vec.rbegin() << " vs real = " << *r_vec.rbegin() << endl;

	cout << "Comparisons :" << endl;
	cout << std::__addressof(*it) << " " << std::__addressof(*r_vec.rbegin()) << endl;
	cout << std::__addressof(*my_it) << " " << std::__addressof(*my_vec.rbegin()) << endl;

	cout << std::distance(r_vec.rbegin(), r_vec.rend()) << endl; // 5 TOUJOURS UN PB ICI
	cout << ft::distance(my_vec.rbegin(), my_vec.rend()) << endl; // PQ CA MARCHE AVEC LES NORMAUX ???
	cout << (it > r_vec.rbegin()) << endl; // equivaut a 1
	cout << (my_it > my_vec.rbegin()) << endl; // equivaut a 0 car rend < rbegin


	cout << FG2("Real with --a") << endl;
	while (it > r_vec.rbegin())
		cout << *(--it) << " ";
	cout << endl;

	cout << FG1("Mine with --a") << endl;
	while (my_it > my_vec.rbegin()) // PROBLEME ; my_it !
		cout << *(--my_it) << " ";
	cout << endl;


	test("** Test 6 : operators a + n **");
	it = r_vec.rbegin();
	my_it = my_vec.rbegin();
	cout << FG2("Real") << endl;
	cout << *(it + 3) << " ";
	cout << endl;

	cout << FG1("Mine") << endl;
	cout << *(my_it + 3) << " ";
	cout << endl;

	test("** Test 7 : operators a - 1 en partant de rbegin + 1 **"); // va SF si on part de rbegin
	it = r_vec.rbegin() + 1;
	my_it = my_vec.rbegin() + 1;
	cout << FG2("Real") << endl;
	cout << *(it - 1) << " ";
	cout << endl;

	cout << FG1("Mine") << endl;
	cout << *(my_it - 1) << " ";
	cout << endl;
}


void		tests_swap()
{
	{

		int myarray[] = { 45, 895, 452, 7895, 45487, 78 };
		int mynegarray[] = { -1, -2, -5, -78, -75, -59 };


		cout << HEADER("*** TESTS SWAP *** ") << endl;

		test("-- Basic test, same initial size --")

			std::vector<int> r_vec;
		std::vector<int> r_vec_neg;
		r_vec.insert(r_vec.begin(), myarray, myarray + 6);
		r_vec_neg.insert(r_vec_neg.begin(), mynegarray, mynegarray + 6);
		r_vec_neg.swap(r_vec);

		ft::vector<int> my_vec;
		ft::vector<int> my_vec_neg;
		my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));
		my_vec_neg.insert(my_vec_neg.begin(), mynegarray, mynegarray + sizeof(mynegarray) / sizeof(mynegarray[0]));
		my_vec_neg.swap(my_vec);

		test("NEG ARE NOW POS...")
			display(my_vec_neg, r_vec_neg);

		test("AND VICE VERSA")
			display(my_vec, r_vec);
	}

	{
		test("-- Basic test, not the same initial size --");

		int myarray[] = { 45, 895, 452, 7895, 45487, 78, 789, 456, 8541 }; // 9
		int mynegarray[] = { -1, -2, -5, -78, -75, -59 }; // 6
		std::vector<int> r_vec;
		std::vector<int> r_vec_neg;
		r_vec.insert(r_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));
		r_vec_neg.insert(r_vec_neg.begin(),  mynegarray, mynegarray + sizeof(mynegarray) / sizeof(mynegarray[0]));
		r_vec_neg.swap(r_vec);

		ft::vector<int> my_vec;
		ft::vector<int> my_vec_neg;
		my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));
		my_vec_neg.insert(my_vec_neg.begin(), mynegarray, mynegarray + sizeof(mynegarray) / sizeof(mynegarray[0]));
		my_vec_neg.swap(my_vec);

		test("NEG ARE NOW POS...")
			display(my_vec_neg, r_vec_neg);

		test("AND VICE VERSA")
			display(my_vec, r_vec);
	}

}




void basic_construct()
{
	cout << HEADER("*** TESTS COPY CONSTRUCT *** ") << endl;
	ft::vector<int> lol(15, 3);
	ft::vector<int> lol2(lol);
	std::vector<int> r_vec(15, 3);
	std::vector<int> r_vec2(r_vec);

	display(lol, r_vec);
	display(lol2, r_vec2);



}
int main()
{

	void (*functptr[])() = {
			basic_construct,
			test_insert,
			test_erase,
			test_reserve,
			test_resize,
			test_strings,
			test_access,
			test_front_back,
			tests_simple_it,
			tests_reverse,
			tests_swap
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		getwchar();
		(*functptr[i])();    /*  Call first function  */
		test("--- end of tests ---")
	}

	// basic_construct();
	// test_insert();
	// test_erase();
	// test_reserve();
	// test_resize();
	// test_strings();
	// test_access();
	// test_front_back();
	// tests_simple_it();
	// tests_reverse();
	// tests_swap();

}

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

void print(ft::vector<int>& r_vec)
{
	std::cout << BOLD("-> Mine only : ") << std::endl;
	std::cout << FG1("Mine :") << std::endl;
	ft::vector<int>::iterator it;
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


void 	test_ints()
{
		ft::vector<int> JOHN;
	ft::vector<int> BOB(5, 8);
	cout << "BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		cout << BOB[i] << ' ';
	cout << '\n';
	ft::vector<int> MIKE(BOB);

	// CTORs
	cout << "\nCTORS\n";
	cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	cout << "BOB is empty? " << BOB.empty() << '\n';

	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;


	// RESIZE
	size_t	bob_resize = 2;
	cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

	size_t	mike_resize = 9;
	bob_resize = 0;
	
	BOB.resize(bob_resize);
	cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, 3);
	/*






	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_resize)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	// RESERVE
	cout << "\nRESERVE\n";

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	/*






	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= john_reserve)
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_reserve)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_reserve)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//AT
	cout << "\nAT\n";
	try
	{
		cout << MIKE.at(2) << '\n';
		cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		cout << "OOR error caught\n";
	}

	// FRONT / BACK
	cout << "\nFRONT / BACK\n";
	cout << "front() of MIKE : " << MIKE.front() << '\n';
	cout << "back() of MIKE : " << MIKE.back() << '\n';

	//ASSIGN
	cout << "\nASSIGN\n";
	BOB.assign(42, 7);

	//ASSIGN RANGE
	cout << "\nASSIGN RANGE\n";
	ft::vector<int>	assign_range;
	assign_range.assign(8, 5);
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	cout << "\nEMPTY\n";
	cout << "BOB is empty ? " << BOB.empty() << '\n';
	cout << "BOB at(41) : " << BOB.at(41) << '\n';

	//PUSH/POP_BACK
	cout << "\nPUSH/POP_BACK\n";
	BOB.push_back(53);
	cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	cout << "last elem of BOB : " << BOB.back() << '\n';

	//INSERT
	cout << "\nINSERT\n";
	vector<int>	insert_in_me;
	for (int i = 0; i < 15; i++)
		insert_in_me.push_back(i);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::iterator	tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, 42);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::const_iterator const_it(insert_in_me.begin());
	cout << "Const it : " << std::endl;
	cout << *const_it << '\n';
//	*const_it = 89; // Does not compile because it's a const_iterator


	//INSERT
	cout << "\nINSERT\n";
	vector<int>	std_insert_in_me;
	for (int i = 0; i < 15; i++)
		std_insert_in_me.push_back(i);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::iterator	std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, 42);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';


	//INSERT RANGE
	cout << "\nINSERT RANGE\n";
	vector<int>	insert_bis;
	for (int i = 0; i < 7; i++)
		insert_bis.push_back(3 * i);
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';


	//ERASE
	cout << "\nERASE\n";

	test("INT : ERASE 10")
	ft::vector<int>	erase_in_me;
	for (int i = 0; i < 15; i++)
		erase_in_me.push_back(2 * i);
	print(erase_in_me);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	test("INT : ERASE begin() + 7")
	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	test("INT : ERASE RANGE")
	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	//SWAP
	cout << "\nSWAP\n";
	BOB.swap(MIKE);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 272\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 277\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 282\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	MIKE.swap(JOHN);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 298\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 303\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 308\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//CLEAR
	cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	/*



	
	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 327\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 332\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 337\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//NON MEMBER Functions
	cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 355\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 360\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 365\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;
	
	//RELATIONAL OPERATORS
	cout << "\nRELATIONAL OPERATORS\n";
	ft::vector<int> MIKE_2(MIKE);
	cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	cout << "\nReal Vector\n";
	ft::vector<int> real;
	real.assign(5, 7);
	for (ft::vector<int>::iterator it = real.begin(); it != real.end(); it++)
		cout << *it << " ";
	cout << '\n';

	cout << std::endl;
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
	ft::vector<int>::iterator mit = my_vec.insert(my_vec.begin() + 1, 30);
	std::vector<int>::iterator rit = vec1.insert(vec1.begin() + 1, 30);
	display(my_vec, vec1);

	cout << DIM("** Tests de retour ** ") << endl;
	cout << *mit << endl;
	cout << *rit << endl;


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



	{
		test("** TEST5 : POSITION, VALUE **");
		ft::vector<int> myvector(3, 100);
		ft::vector<int>::iterator it;

		std::vector<int> myvector_r(3, 100);
		std::vector<int>::iterator it_r;

		it = myvector.begin();
		it = myvector.insert(it, 200);

		it_r = myvector_r.begin();
		it_r = myvector_r.insert(it_r, 200);

		display(myvector, myvector_r); // ok

		myvector.insert(it, 2, 300);
		myvector_r.insert(it_r, 2, 300);

		display(myvector, myvector_r);


		it = myvector.begin();
		it_r = myvector_r.begin();

		//****** 
		test("** TEST6 : begin() + 2, anothervector.begin(), anothervector.end() ***" );

		ft::vector<int> anothervector(2, 400);
		myvector.insert(it + 2, anothervector.begin(), anothervector.end());

		std::vector<int> anothervector_r(2, 400);
		myvector_r.insert(it_r + 2, anothervector_r.begin(), anothervector_r.end());

		display(myvector, myvector_r);

		//***** 
		test("** TEST7 : begin(), array array + 3 ***" );

		int myarray[] = { 501,502,503 };
		myvector.insert(myvector.begin(), myarray, myarray + 3);
		myvector_r.insert(myvector_r.begin(), myarray, myarray + 3);


		display(myvector, myvector_r);


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

	std::vector<int>::iterator r_test1 = vec1.erase(vec1.begin() + 1, vec1.end() - 3);
	ft::vector<int>::iterator my_test1 = my_vec.erase(my_vec.begin() + 1, my_vec.end() - 3);
	display(my_vec, vec1);
	cout << FG2("Real") << *(r_test1) << endl;
	cout << FG1("Mine") << *(my_test1) << endl;


	my_vec.push_back(1024);
	vec1.push_back(1024);
	display(my_vec, vec1);

	test("** TESTS POP BACK USING ERASE ** ");

	my_vec.pop_back();
	vec1.pop_back();
	display(my_vec, vec1);

	test("** TESTS RET OF IT** ");
	display(my_vec, vec1);
	cout << __addressof(*(vec1.begin() + 3)) << endl;
	std::vector<int>::iterator r_test = vec1.erase(vec1.begin() + 2);
	ft::vector<int>::iterator my_test = my_vec.erase(my_vec.begin() + 2);
	display(my_vec, vec1);

	cout << FG2("Real") << *(r_test) << endl;
	cout << FG1("Mine") << *(my_test) << endl;

	test("** TESTS RET OF IT** ");

	ft::vector<int> mine;
	std::vector<int> real;


	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++) mine.push_back(i);
	for (int i = 1; i <= 10; i++) real.push_back(i);
	display(mine, real);


	// erase the 6th element
	mine.erase(mine.begin() + 5);
	real.erase(real.begin() + 5);
	display(mine, real);



	// erase the first 3 elements:
	mine.erase(mine.begin(), mine.begin() + 3);
	real.erase(real.begin(), real.begin() + 3);


	display(mine, real);


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
		r_vec_neg.insert(r_vec_neg.begin(), mynegarray, mynegarray + sizeof(mynegarray) / sizeof(mynegarray[0]));
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
	ft::vector<int> test;
	ft::vector<int> tmp(45, 4);

	test.insert(test.begin(), tmp.begin(), tmp.end());


	cout << HEADER("*** TESTS COPY CONSTRUCT *** ") << endl;
	ft::vector<int> lol(15, 3);
	ft::vector<int> lol2(lol);
	std::vector<int> r_vec(15, 3);
	std::vector<int> r_vec2(r_vec);

	display(lol, r_vec);
	display(lol2, r_vec2);



}


void	mazoise_swap()
{
	ft::vector<int> foo(3, 100);   // three ints with a value of 100
	ft::vector<int> bar(5, 200);   // five ints with a value of 200

	bar.swap(foo);

	cout << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		cout << ' ' << foo[i];
	cout << '\n';

	cout << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		cout << ' ' << bar[i];
	cout << '\n';

	// OK ICI 

	{
		ft::vector<int> foo, bar;

		foo.push_back(100);
		foo.push_back(200);

		bar.push_back(11);
		bar.push_back(22);
		bar.push_back(33);


		ft::vector<int>::const_iterator tmp = foo.begin(); //tmp iterates through foo
		ft::vector<int>::const_iterator tmp2 = bar.begin(); //tmp2 iterates through bar
		debug ("*** SWAP 2 ***")
		ft::swap(bar, foo); //tmp iterates through bar
						//tmp2 iterates through foo

		debug ("*** SWAP 2 DONE ***")
		debug (*tmp);
		debug ("*** OK TMP ***")


		ft::vector<int>	other;

		other.push_back(73);
		other.push_back(173);
		other.push_back(763);
		other.push_back(73854);
		other.push_back(74683);
		other.push_back(753);

		ft::vector<int>::const_iterator tmp3 = other.begin(); // tmp3 iterates through other

		cout << "foo contains:\n";
		for (ft::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
			cout << *it << ' ';
		cout << endl;

		cout << "bar contains:\n";
		for (ft::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
			cout << *it << ' ';
		cout << endl;

		while (tmp != bar.end()) // tmp = foo begin 
		{
			cout << *tmp << '\n'; // la ca chie 
			tmp++;
		}
		tmp--;

		while (tmp2 != foo.end())
		{
			cout << *tmp2 << '\n';
			tmp2++;
		}
		tmp2--;

		swap(other, foo); //tmp2 iterates through other
						//tmp3 iterates throught foo
		print(other);
		print(foo);
		print(bar);
		while (tmp != bar.begin())
		{
			cout << *tmp << ' ';
			tmp--;
		}
		cout << *tmp << '\n';

		while (tmp2 != other.begin())
		{
			cout << *tmp2 << ' ';
			tmp2--;
		}
		cout << *tmp2 << '\n';

		while (tmp3 != foo.end())
		{
			cout << *tmp3 << '\n';
			tmp3++;
		}
		tmp3--;

		swap(bar, foo);
		swap(foo, bar);
		swap(bar, foo); //tmp3 iterates through bar
					//tmp iterates through foo

		print(other);
		print(foo);
		print(bar);

		while (tmp != foo.end())
		{
			cout << *tmp << '\n';
			tmp++;
		}

		while (tmp2 != other.end())
		{
			cout << *tmp2 << '\n';
			tmp2++;
		}

		while (tmp3 != bar.begin())
		{
			cout << *tmp3 << '\n';
			tmp3--;
		}
		cout << *tmp3 << '\n';
	}

	//return 0;
}


void	test_relationnal()
{
	test("TEST 1 : relationnal operators ")
	ft::vector<int> test1(47, 42);
	ft::vector<int> test2(47, 42);
	cout << std::boolalpha << "bonjour" << (test1 == test2) << endl;

}


void mazoise_other()
{
        cout << "INITIALIZATION" << ENDL;
        cout << "operations..." << ENDL;
        ft::vector<int> fill(10, 42);
        ft::vector<int> tmp;
        ft::vector<int>::iterator it1;
        ft::vector<int>::iterator it2;
        cout << "print..." << ENDL;
        print(fill);

        cout << "ERASE" << ENDL;
        cout << "operations..." << ENDL;
        it1 = fill.begin();
        it1 += 5;
        it2 = fill.end();
        it2 -=2;

        fill.erase(it1, it2);
        cout << "print..." << ENDL;
        print(fill);

        cout << "POP_BACK/PUSH_BACK" << ENDL;
        cout << "operations..." << ENDL;
        fill.pop_back();
        fill.push_back(13);
        fill.push_back(69);
        cout << "print..." << ENDL;
        print(fill);

        cout << "OPERATOR[]" << ENDL;
        cout << "operations..." << ENDL;
        fill[3] = -13;
        fill[5] = 123456789;
        cout << "print..." << ENDL;
        print(fill);

        cout << "SWAP" << ENDL;
        cout << "operations..." << ENDL;
        fill.swap(tmp);
        fill.swap(tmp);
        cout << "print..." << ENDL;
        print(fill);

        cout << "FRONT/BACK/AT" << ENDL;
        cout << "operations..." << ENDL;
        fill.front() = -42;
        fill.back() /= -2;
        fill.at(1) = 0;
        cout << "print..." << ENDL;
        print(fill);

        cout << "INSERT" << ENDL;
        cout << "operations..." << ENDL;
        it1 = fill.begin();
        it1 += 2;

        fill.insert(it1, 3, 987654321);
        cout << "print..." << ENDL;
        print(fill);


        cout << "RESIZE" << ENDL;
        cout << "operations..." << ENDL;
        fill.resize(20);
        fill.resize(13);
        cout << "print..." << ENDL;
        print(fill);

        try
        {
                cout << "AT(error)" << ENDL;
                cout << "operations..." << ENDL;
                fill.at(-1) = -1;
        }
        catch (std::out_of_range& oor)
        {
                (void)oor;
                cout << "OOR error caught\n";
        }
        try
        {
                fill.at(15) = -1;
        }
        catch (std::out_of_range& oor)
        {
                (void)oor;
                cout << "OOR error caught\n";
        }
        cout << "print..." << ENDL;
        print(fill);

}

int main()
{

	void (*functptr[])() = {
		//basic_construct,
		//test_insert,
		//test_erase,
		//test_reserve,
		//test_resize,
		//test_strings,
		// test_access,
		// test_front_back,
		// tests_simple_it,
		// tests_reverse,
		//tests_swap,
		//mazoise_swap
		//test_ints,
		//test_relationnal,
		mazoise_other
	};

	for (unsigned int i = 0; i < sizeof(functptr) / sizeof(functptr[0]); i++)
	{
		(*functptr[i])();    /*  Call first function  */
		test("--- end of tests ---")
			getwchar();

	}
}

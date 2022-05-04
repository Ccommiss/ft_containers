#include "../tests.hpp"

using namespace NM;

void test_ints()
{
	start;
	vector<int> JOHN;
	vector<int> BOB(5, 8);
	std::cout << "BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		std::cout << BOB[i] << ' ';
	std::cout << '\n';
	vector<int> MIKE(BOB);

	// CTORs
	std::cout << "\nCTORS\n";
	std::cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	std::cout << "BOB is empty? " << BOB.empty() << '\n';

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;

	// RESIZE
	size_t bob_resize = 2;
	std::cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

	size_t mike_resize = 9;
	bob_resize = 0;

	BOB.resize(bob_resize);
	std::cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, 3);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_resize)
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	// RESERVE
	std::cout << "\nRESERVE\n";

	size_t john_reserve = 5;
	size_t bob_reserve = 3;
	size_t mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= john_reserve)
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_reserve)
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_reserve)
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	// AT
	std::cout << "\nAT\n";
	try
	{
		std::cout << MIKE.at(2) << '\n';
		std::cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range &oor)
	{
		(void)oor;
		std::cout << "OOR error caught\n";
	}

	// FRONT / BACK
	std::cout << "\nFRONT / BACK\n";
	std::cout << "front() of MIKE : " << MIKE.front() << '\n';
	std::cout << "back() of MIKE : " << MIKE.back() << '\n';
	// ASSIGN
	std::cout << "\nASSIGN\n";
	BOB.assign(42, 7);

	// ASSIGN RANGE
	std::cout << "\nASSIGN RANGE\n";
	vector<int> assign_range;
	assign_range.assign(8, 5);
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	// EMPTY
	std::cout << "\nEMPTY\n";
	std::cout << "BOB is empty ? " << BOB.empty() << '\n';
	std::cout << "BOB at(41) : " << BOB.at(41) << '\n';

	// PUSH/POP_BACK
	std::cout << "\nPUSH/POP_BACK\n";
	BOB.push_back(53);
	std::cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	std::cout << "last elem of BOB : " << BOB.back() << '\n';

	// INSERT
	std::cout << "\nINSERT\n";
	vector<int> insert_in_me;
	for (int i = 0; i < 15; i++)
		insert_in_me.push_back(i);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		std::cout << insert_in_me.at(i) << ' ';
	std::cout << '\n';

	vector<int>::iterator tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, 42);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		std::cout << insert_in_me.at(i) << ' ';
	std::cout << '\n';

	vector<int>::const_iterator const_it(insert_in_me.begin());
	std::cout << "Const it : " << std::endl;
	std::cout << *const_it << '\n';
	//	*const_it = 89; // Does not compile because it's a const_iterator

	// INSERT
	std::cout << "\nINSERT\n";
	vector<int> std_insert_in_me;
	for (int i = 0; i < 15; i++)
		std_insert_in_me.push_back(i);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		std::cout << std_insert_in_me.at(i) << ' ';
	std::cout << '\n';

	vector<int>::iterator std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, 42);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		std::cout << std_insert_in_me.at(i) << ' ';
	std::cout << '\n';

	// INSERT RANGE
	std::cout << "\nINSERT RANGE\n";
	vector<int> insert_bis;
	for (int i = 0; i < 7; i++)
		insert_bis.push_back(3 * i);
	for (size_t i = 0; i < insert_bis.size(); i++)
		std::cout << insert_bis[i] << ' ';
	std::cout << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		std::cout << insert_bis[i] << ' ';
	std::cout << '\n';

	// ERASE
	std::cout << "\nERASE\n";

	out("INT : ERASE 10")
		vector<int>
			erase_in_me;
	for (int i = 0; i < 15; i++)
		erase_in_me.push_back(2 * i);
	print(erase_in_me);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	out("INT : ERASE begin() + 7")
		erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	out("INT : ERASE RANGE")
		erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			std::cout << ' ';
		std::cout << erase_in_me.at(i) << ' ';
	}
	std::cout << '\n';

	// SWAP
	std::cout << "\nSWAP\n";
	BOB.swap(MIKE);

	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 272\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 277\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 282\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	MIKE.swap(JOHN);
	/*




	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 298\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 303\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 308\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	// CLEAR
	std::cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	/*




	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 327\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 332\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 337\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	// NON MEMBER Functions
	std::cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	/*




	*/
	std::cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		std::cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 355\n";
	std::cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		std::cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 360\n";
	std::cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		std::cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 365\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		std::cout << MIKE[i] << ' ';
	std::cout << std::endl;

	// RELATIONAL OPERATORS
	std::cout << "\nRELATIONAL OPERATORS\n";
	vector<int> MIKE_2(MIKE);
	std::cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	std::cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	vector<int> myvec;
	myvec.assign(5, 7);
	for (vector<int>::iterator it = myvec.begin(); it != myvec.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';

	std::cout << std::endl;
	finish;
}
void test_insert()
{
	start;
	// std::cout << "** TESTING VECTORS OF SAME SIZE ** " << std::endl;

	vector<int> my_vec(10, 8);
	vector<int> my_tem(10, 6);

	out("** TEST0 : construction ** ");
	print(my_vec);
	out("** TEST1 : insert(iterator position, const T& x) ** ");
	vector<int>::iterator mit = my_vec.insert(my_vec.begin() + 1, 30);
	print(my_vec);
	std::cout << DIM("** Tests de retour ** ") << std::endl;
	std::cout << *mit << std::endl;

	out("** TEST2 : insert(iterator position, size_type n, const T& x)  ** ");
	my_vec.insert(my_vec.begin() + 5, 2, 404);
	print(my_vec);

	out("** TEST3 : insert(iterator position, InputIterator first, InputIterator last) ** ");
	my_vec.insert(my_vec.begin(), my_tem.begin(), my_tem.end());
	print(my_vec);

	out("** TEST4 : insert avec wnd puis begin**"); // regarder sur linux
	// try
	// {
	// 	my_vec.insert(my_vec.begin(), my_tem.rend(), my_tem.rbegin());
	// 	print(my_vec);
	// }
	// catch (std::exception &e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }
	{
		out("** TEST5 : POSITION, VALUE **");
		vector<int> myvector(3, 100);
		vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert(it, 200);
		print(myvector);

		myvector.insert(it, 2, 300);
		print(myvector);

		it = myvector.begin();
		//******
		out("** TEST6 : begin() + 2, anothervector.begin(), anothervector.end() ***");

		vector<int> anothervector(2, 400);
		myvector.insert(it + 2, anothervector.begin(), anothervector.end());

		print(myvector);

		//*****
		out("** TEST7 : begin(), array array + 3 ***");

		int myarray[] = {501, 502, 503};
		myvector.insert(myvector.begin(), myarray, myarray + 3);
		print(myvector);
	}
	finish;
}

void test_erase()
{
	start;

	out("** TEST1 erase(iterator position) ** ");

	vector<int> my_vec(10, 8);

	my_vec.push_back(404);
	my_vec.insert(my_vec.begin(), 3);
	print(my_vec);
	my_vec.erase(my_vec.begin());
	print(my_vec);

	out("** TESTS erase(iterator first, iterator last)**");

	vector<int>::iterator my_test1 = my_vec.erase(my_vec.begin() + 1, my_vec.end() - 3);
	print(my_vec);
	std::cout << FG1("-> output") << *(my_test1) << std::endl;

	my_vec.push_back(1024);
	print(my_vec);
	out("** TESTS POP BACK USING ERASE ** ");

	my_vec.pop_back();
	print(my_vec);
	out("** TESTS RET OF IT** ");
	print(my_vec);
	vector<int>::iterator my_test = my_vec.erase(my_vec.begin() + 2);
	print(my_vec);
	std::cout << FG1("-> output") << *(my_test) << std::endl;

	out("** TESTS RET OF IT** ");

	vector<int> mine;

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++)
		mine.push_back(i);

	print(mine);

	// erase the 6th element
	mine.erase(mine.begin() + 5);
	print(mine);

	// erase the first 3 elements:
	mine.erase(mine.begin(), mine.begin() + 3);
	print(mine);
	finish;
}

void test_reserve()
{
	start;
	{
		vector<int> my_vec(3, 8);
		print(my_vec);
		my_vec.reserve(46);
		print(my_vec);
		my_vec.push_back(78);
		print(my_vec);
		my_vec.push_back(78);
		my_vec.push_back(78);
		print(my_vec);
		my_vec.pop_back();
		my_vec.pop_back();
		print(my_vec);
	}
	{
		vector<int> my_vec(10, 404);
		print(my_vec);
		my_vec.push_back(20);
		print(my_vec);
		my_vec.push_back(20);
		print(my_vec);
		my_vec.insert(my_vec.end(), 12, 707);
		print(my_vec);
	}

	out("**TEST MAX SIZE EXCEPTION**");
	vector<int> my_vec(10, 404);
	try
	{
		my_vec.reserve(my_vec.max_size() + 1);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	finish;
}

void test_resize()
{
	start;

	std::cout << "Base" << std::endl;
	vector<int> myvec(4, 5);
	print(myvec);

	std::cout << "Resize bigger" << std::endl;
	myvec.resize(40);
	print(myvec);

	std::cout << "Resize smaller" << std::endl;
	myvec.resize(3);
	print(myvec);
	finish;
}

void test_strings()
{
	start;
	out("Inserting through input iterator : ");
	vector<std::string> lol;
	std::string myarray2[] = {"Hi", "hello", "wassup"};
	lol.insert(lol.begin(), myarray2, myarray2 + 3);
	print(lol);
	out("Erase several time : ");
	lol.erase(lol.begin());
	print(lol);
	lol.erase(lol.begin(), lol.end());
	print(lol);
	finish;
}

void test_access()
{
	start;
	vector<std::string> lol;
	std::string myarray2[] = {"I am 1", "I am 2", "I am 3"};
	lol.insert(lol.begin(), myarray2, myarray2 + 3);

	out("** Test 1 : subscript [] accessing an existing elem ( n <= size ) **");
	std::cout << lol[2] << std::endl;

	out("** Test 2 : subscript [] accessing an inexistant elem (n > size) **");
	std::cout << lol[77] << std::endl;

	out("** Test 3 : at(n) accessing an existant elem (n <= size) **");
	std::cout << lol.at(2) << std::endl;

	out("** Test 4 : at(n) accessing an inexistant elem (n > size) --> thrown exception **");
	std::cout << FG1("-> output :") << std::endl;
	try
	{
		std::cout << lol.at(77) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	finish;
}

void test_front_back()
{
	start;
	int myarray[] = {45, 895, 452, 7895, 45487, 78};

	std::cout << HEADER("**TESTS FRONT / BACK") << std::endl;

	vector<int> my_vec;
	my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	print(my_vec);

	out("testing front and back");
	std::cout << FG1("-> output") << std::endl;
	std::cout << my_vec.front() << " " << my_vec.back() << std::endl;
	finish;
}

void tests_simple_it()
{
	std::cout << HEADER("**TESTS SIMPLE IT *** ") << std::endl;

	int myarray[] = {10, 20, 30, 40, 50, 60};

	vector<int> my_vec;
	my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	print(my_vec);

	out("*-* Test 1 : begin() et end() *-*");
	std::cout << FG1("-> output") << std::endl;
	std::cout << *(my_vec.begin()) << " " << *(my_vec.end() - 1) << std::endl;

	out("** Test 2 : operators a++ **");
	vector<int>::iterator my_it = my_vec.begin();

	std::cout << FG1("-> output with a++") << std::endl;
	while (my_it != my_vec.end())
		std::cout << *(my_it++) << " ";
	std::cout << std::endl;

	out("** Test 3 : operators ++a **");

	my_it = my_vec.begin();

	std::cout << FG1("-> output with ++a") << std::endl;
	while (my_it < my_vec.end() - 1)
		std::cout << *(++my_it) << " ";
	std::cout << std::endl;

	out("** Test 4 : operators a-- **");
	my_it = my_vec.end() - 1;

	std::cout << FG1("-> output with a--") << std::endl;
	while (my_it != my_vec.begin())
		std::cout << *(my_it--) << " ";
	std::cout << std::endl;

	out("** Test 5 : operators --a **");
	my_it = my_vec.end() - 1;

	std::cout << FG1("-> output with --a") << std::endl;
	while (my_it > my_vec.begin())
		std::cout << *(--my_it) << " ";
	std::cout << std::endl;

	out("**Comparisons**")
		my_it = my_vec.end();
	std::cout << distance(my_it, my_vec.begin()) << std::endl;
}

void tests_reverse()
{

	int myarray[] = {45, 895, 452, 7895, 45487, 78};

	std::cout << HEADER("**TESTS REVERSE *** ") << std::endl;

	vector<int> my_vec;
	my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));

	print(my_vec);

	// NOTE : REND A AFFICHER = BUFFER OVERFLOW ! VOIR SCHEMA

	out("*-* Test 1 : rbegin() et rend() *-*");
	std::cout << FG1("-> output") << std::endl;
	std::cout << *(my_vec.rbegin()) << " " << *(my_vec.rend().base()) << std::endl;

	out("** Test 2 : operators a++ **");
	vector<int>::reverse_iterator my_it = my_vec.rbegin();

	std::cout << FG1("-> output with a++") << std::endl;
	out("my_it + 1 = " << *(my_it + 1));
	while (my_it != my_vec.rend())
		std::cout << *(my_it++) << " ";
	std::cout << std::endl;

	out("** Test 3 : operators ++a **");

	my_it = my_vec.rbegin();

	std::cout << FG1("-> output with ++a") << std::endl;
	while (my_it < my_vec.rend() - 1)
		std::cout << *(++my_it) << " ";
	std::cout << std::endl;

	out("** Test 4 : operators a-- **");
	my_it = my_vec.rend() - 1;

	std::cout << FG1("-> output with a--") << std::endl;
	while (my_it != my_vec.rbegin())
		std::cout << *(my_it--) << " ";
	std::cout << std::endl;

	out("** Test 5 : operators --a **");
	my_it = my_vec.rend() - 1;

	std::cout << "Comparisons :" << std::endl;

	std::cout << distance(my_vec.rbegin(), my_vec.rend()) << std::endl; // PQ CA MARCHE AVEC LES NORMAUX ???
	std::cout << (my_it > my_vec.rbegin()) << std::endl;					// equivaut a 0 car rend < rbegin

	std::cout << FG1("-> output with --a") << std::endl;
	while (my_it > my_vec.rbegin()) // PROBLEME ; my_it !
		std::cout << *(--my_it) << " ";
	std::cout << std::endl;

	out("** Test 6 : operators a + n **");
	my_it = my_vec.rbegin();

	std::cout << FG1("-> output") << std::endl;
	std::cout << *(my_it + 3) << " ";
	std::cout << std::endl;

	out("** Test 7 : operators a - 1 en partant de rbegin + 1 **"); // va SF si on part de rbegin
	my_it = my_vec.rbegin() + 1;

	std::cout << FG1("-> output") << std::endl;
	std::cout << *(my_it - 1) << " ";
	std::cout << std::endl;
}

void tests_swap()
{
	{

		int myarray[] = {45, 895, 452, 7895, 45487, 78};
		int mynegarray[] = {-1, -2, -5, -78, -75, -59};

		std::cout << HEADER("*** TESTS SWAP *** ") << std::endl;

		out("-- Basic test, same initial size --")

			vector<int>
				my_vec;
		vector<int> my_vec_neg;
		my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));
		my_vec_neg.insert(my_vec_neg.begin(), mynegarray, mynegarray + sizeof(mynegarray) / sizeof(mynegarray[0]));
		my_vec_neg.swap(my_vec);

		out("NEG ARE NOW POS...")
			print(my_vec_neg);

		out("AND VICE VERSA")
			print(my_vec);
	}

	{
		out("-- Basic test, not the same initial size --");

		int myarray[] = {45, 895, 452, 7895, 45487, 78, 789, 456, 8541}; // 9
		int mynegarray[] = {-1, -2, -5, -78, -75, -59};					 // 6

		vector<int> my_vec;
		vector<int> my_vec_neg;
		my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray) / sizeof(myarray[0]));
		my_vec_neg.insert(my_vec_neg.begin(), mynegarray, mynegarray + sizeof(mynegarray) / sizeof(mynegarray[0]));
		my_vec_neg.swap(my_vec);

		out("NEG ARE NOW POS...");
		print(my_vec_neg);

		out("AND VICE VERSA");
		print(my_vec);
	}
}

void basic_construct()
{

	std::cout << HEADER("*** TESTS COPY CONSTRUCT *** ") << std::endl;
	vector<int> test;
	vector<int> tmp(45, 4);

	test.insert(test.begin(), tmp.begin(), tmp.end());

	std::cout << HEADER("*** TESTS COPY CONSTRUCT *** ") << std::endl;
	vector<int> lol(15, 3);
	vector<int> lol2(lol);
	print(lol2);
}

void mazoise_swap()
{
	vector<int> foo(3, 100); // three ints with a value of 100
	vector<int> bar(5, 200); // five ints with a value of 200

	bar.swap(foo);

	std::cout << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

	// OK ICI

	{
		vector<int> foo, bar;

		foo.push_back(100);
		foo.push_back(200);

		bar.push_back(11);
		bar.push_back(22);
		bar.push_back(33);

		vector<int>::const_iterator tmp = foo.begin();	// tmp iterates through foo
		vector<int>::const_iterator tmp2 = bar.begin(); // tmp2 iterates through bar
		out("*** SWAP 2 ***");
		swap(bar, foo); // tmp iterates through bar
							// tmp2 iterates through foo

		out("*** SWAP 2 DONE ***");
		out(*tmp);
		out("*** OK TMP ***");

		vector<int>
			other;

		other.push_back(73);
		other.push_back(173);
		other.push_back(763);
		other.push_back(73854);
		other.push_back(74683);
		other.push_back(753);

		vector<int>::const_iterator tmp3 = other.begin(); // tmp3 iterates through other

		std::cout << "foo contains:\n";
		for (vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << *it << ' ';
		std::cout << std::endl;

		std::cout << "bar contains:\n";
		for (vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
			std::cout << *it << ' ';
		std::cout << std::endl;

		while (tmp != bar.end()) // tmp = foo begin
		{
			std::cout << *tmp << '\n'; // la ca chie
			tmp++;
		}
		tmp--;

		while (tmp2 != foo.end())
		{
			std::cout << *tmp2 << '\n';
			tmp2++;
		}
		tmp2--;

		swap(other, foo); // tmp2 iterates through other
						  // tmp3 iterates throught foo
		print(other);
		print(foo);
		print(bar);
		while (tmp != bar.begin())
		{
			std::cout << *tmp << ' ';
			tmp--;
		}
		std::cout << *tmp << '\n';

		while (tmp2 != other.begin())
		{
			std::cout << *tmp2 << ' ';
			tmp2--;
		}
		std::cout << *tmp2 << '\n';

		while (tmp3 != foo.end())
		{
			std::cout << *tmp3 << '\n';
			tmp3++;
		}
		tmp3--;

		swap(bar, foo);
		swap(foo, bar);
		swap(bar, foo); // tmp3 iterates through bar
						// tmp iterates through foo

		print(other);
		print(foo);
		print(bar);

		while (tmp != foo.end())
		{
			std::cout << *tmp << '\n';
			tmp++;
		}

		while (tmp2 != other.end())
		{
			std::cout << *tmp2 << '\n';
			tmp2++;
		}

		while (tmp3 != bar.begin())
		{
			std::cout << *tmp3 << '\n';
			tmp3--;
		}
		std::cout << *tmp3 << '\n';
	}

	// return 0;
}

void test_relationnal()
{
	out("TEST 1 : relationnal operators ")
		vector<int>
			test1(47, 42);
	vector<int> test2(47, 42);
	std::cout << std::boolalpha << "bonjour" << (test1 == test2) << std::endl;
}

void mazoise_other()
{
	start;
	{
		std::cout << "INITIALIZATION" << std::endl;
		std::cout << "operations..." << std::endl;
		vector<int> fill(10, 42);
		vector<int> tmp;
		vector<int>::iterator it1;
		vector<int>::iterator it2;
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "ERASE" << std::endl;
		std::cout << "operations..." << std::endl;
		it1 = fill.begin();
		it1 += 5;
		it2 = fill.end();
		it2 -= 2;

		fill.erase(it1, it2);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "POP_BACK/PUSH_BACK" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.pop_back();
		fill.push_back(13);
		fill.push_back(69);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "OPERATOR[]" << std::endl;
		std::cout << "operations..." << std::endl;
		fill[3] = -13;
		fill[5] = 123456789;
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "SWAP" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.swap(tmp);
		fill.swap(tmp);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "FRONT/BACK/AT" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.front() = -42;
		fill.back() /= -2;
		fill.at(1) = 0;
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "INSERT" << std::endl;
		std::cout << "operations..." << std::endl;
		it1 = fill.begin();
		it1 += 2;

		fill.insert(it1, 3, 987654321);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "RESIZE" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.resize(20);
		fill.resize(13);
		std::cout << "print..." << std::endl;
		print(fill);

		try
		{
			std::cout << "AT(error)" << std::endl;
			std::cout << "operations..." << std::endl;
			fill.at(-1) = -1;
		}
		catch (std::out_of_range &oor)
		{
			(void)oor;
			std::cout << "OOR error caught\n";
		}
		try
		{
			fill.at(15) = -1;
		}
		catch (std::out_of_range &oor)
		{
			(void)oor;
			std::cout << "OOR error caught\n";
		}
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << HEADER("END OF MINE") << std::endl;
	}
	{
		std::cout << "INITIALIZATION" << std::endl;
		std::cout << "operations..." << std::endl;
		vector<int> fill(10, 42);
		vector<int> tmp;
		vector<int>::iterator it1;
		vector<int>::iterator it2;
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "ERASE" << std::endl;
		std::cout << "operations..." << std::endl;
		it1 = fill.begin();
		it1 += 5;
		it2 = fill.end();
		it2 -= 2;

		fill.erase(it1, it2);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "POP_BACK/PUSH_BACK" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.pop_back();
		fill.push_back(13);
		fill.push_back(69);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "OPERATOR[]" << std::endl;
		std::cout << "operations..." << std::endl;
		fill[3] = -13;
		fill[5] = 123456789;
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "SWAP" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.swap(tmp);
		fill.swap(tmp);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "FRONT/BACK/AT" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.front() = -42;
		fill.back() /= -2;
		fill.at(1) = 0;
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "INSERT" << std::endl;
		std::cout << "operations..." << std::endl;
		it1 = fill.begin();
		it1 += 2;

		fill.insert(it1, 3, 987654321);
		std::cout << "print..." << std::endl;
		print(fill);

		std::cout << "RESIZE" << std::endl;
		std::cout << "operations..." << std::endl;
		fill.resize(20);
		fill.resize(13);
		std::cout << "print..." << std::endl;
		print(fill);

		try
		{
			std::cout << "AT(error)" << std::endl;
			std::cout << "operations..." << std::endl;
			fill.at(-1) = -1;
		}
		catch (std::out_of_range &oor)
		{
			(void)oor;
			std::cout << "OOR error caught\n";
		}
		try
		{
			fill.at(15) = -1;
		}
		catch (std::out_of_range &oor)
		{
			(void)oor;
			std::cout << "OOR error caught\n";
		}
		std::cout << "print..." << std::endl;
		print(fill);
	}
	finish;
}

void leaks_test()
{
	start;
	vector<int> test1(3, 3);
	vector<vector<int> > to_be_filled;
	to_be_filled.assign(4, test1);
	finish;
}

void comparative_tests_vector()
{
	basic_construct();
	test_insert();
	test_erase();
	test_reserve();
	test_resize();
	test_strings();
	test_access();
	test_front_back();
	tests_simple_it();
	tests_reverse();
	tests_swap();
	mazoise_swap();
	test_ints();
	test_relationnal();
}

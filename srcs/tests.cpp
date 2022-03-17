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
	cout << DIM("Real size : ") << r_vec.size() << DIM(" VS my size : ") << my_vec.size() << endl << endl;
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
	ft::vector<int> 		my_vec(3, 8);
	my_vec.reserve(46);
	std::cout << my_vec.capacity() << std::endl;

	ft::vector<int>::iterator it1;
	for (it1 = my_vec.begin(); it1 != my_vec.end(); it1++)
		std::cout << "MINE it = " << *it1 << std::endl;

	test("**TEST MAX SIZE EXCEPTION**");
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

	test("** Test 3 : at(n) accessing an inexistant elem (n > size) --> thrown exception **");
	std::cout << FG2("Real :") << std::endl;
	try
	{
		std::cout << myvector.at(77) << std::endl;
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
	}
	std::cout << FG1("Mine :") << std::endl;
	try
	{
		std::cout << lol.at(77) << std::endl;
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
	}

}

void		test_front_back()
{
	int myarray[] = { 45, 895, 452, 7895, 45487, 78};

	cout << HEADER("**TESTS FRONT / BACK") << endl;
	std::vector<int> r_vec;
	r_vec.insert(r_vec.begin(), myarray, myarray + sizeof(myarray)/sizeof(myarray[0]));

	ft::vector<int> my_vec;
	my_vec.insert(my_vec.begin(), myarray, myarray + sizeof(myarray)/sizeof(myarray[0]));

	display(my_vec, r_vec);

	test("testing front and back");
	cout << FG1("Mine") << endl;
	cout << my_vec.front() << " " << my_vec.back() << endl;

	cout << FG2("Real") << endl;
	cout << r_vec.front() << " " << r_vec.back() << endl;

}

int main()
{

	//test_insert();
	//test_erase();
	//test_reserve();
	//test_resize();
	//test_strings();
	//test_access();
	test_front_back();



	{

		//for (it1 = my_vec.begin(); it1 != my_vec.end(); it1++)
		// 	std::cout << "MINE it = " << *it1 << std::endl;
	}
	//my_vec.insert (my_vec.begin() + 2, 4, 5);
	//my_vec2.insert  (my_vec.begin() + 2, 30, 5);


	//std::cout << my_vec.capacity() << " VS " << r_vec.capacity() << std::endl;
	//std::cout << my_vec.size() << " VS " << r_vec.size() << std::endl;


	//my_vec.insert(my_vec.begin() + 2, 4, 5);

	// ft::vector<int>::iterator it1;
	// for (it1 = my_vec.begin(); it1 != my_vec.end(); it1++)
	//  	std::cout << "MINE it = " << *it1 << std::endl;
	//std::cout << my_vec.size() << std::endl;


	// std::cout << "My vec begin is " << *(my_vec.begin()) << ' ';
	// std::cout << "My vec end is " << *(my_vec.end()) << ' ';
	// std::cout << "DIFFERENCE IS " << my_vec.end() - my_vec.begin() << std::endl;
	// std::cout << "CURR " << *(my_vec.begin()) << "+ STEP 3 = " << *(my_vec.begin() + 3) << std::endl;

	// std::cout << "RANGE SHOULD BE CALLED" << std::endl;
	// ft::vector<int> my_vec2(my_vec.begin(), my_vec.end());

	// std::vector<int>		r_vec(9, 7);
	// r_vec.insert(r_vec.begin() + 2, 4, 5);

	// std::cout << r_vec.size() << std::endl;


	//for (int i: r_vec)
   // std::cout << "Begin is " << *(r_vec.begin()) << ' ';
}

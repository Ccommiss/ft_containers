# include "includes.hpp"
#include <vector>

using namespace std;


void display(ft::vector<int> & my_vec, std::vector<int> & r_vec)
{
	ft::vector<int>::iterator it1;
	for (it1 = my_vec.begin(); it1 != my_vec.end(); it1++)
	 	std::cout << "MINE it = " << *it1 << " ";
	std::cout << std::endl;


	//(void)r_vec;
	std::vector<int>::iterator it;
	for (it = r_vec.begin(); it != r_vec.end(); it++)
		std::cout << "REAL it = " << *it << " ";
	std::cout << std::endl;

	cout << "Real size : " << r_vec.size() << " VS my size : " << my_vec.size() << endl;
}

void	test_insert()
{
	//cout << "** TESTING VECTORS OF SAME SIZE ** " << endl;
	std::vector<int> vec1   (10, 8);
	std::vector<int> temoinv(10, 6);


	ft::vector<int>	my_vec(10, 8);
	ft::vector<int>	my_tem(10, 6);

	cout << "\n** TEST0 : construction ** " << endl;
	display(my_vec, vec1);

	cout << "\n** TEST1 : insert(iterator position, const T& x) ** " << endl;
	my_vec.insert(my_vec.begin() + 1, 30);
	vec1.insert(vec1.begin() + 1, 30);
	display (my_vec, vec1);

	cout << "\n** TEST2 : insert(iterator position, size_type n, const T& x)  ** " << endl;
	my_vec.insert(my_vec.begin() + 5, 2, 404);
	vec1.insert(vec1.begin() + 5, 2, 404);
	display (my_vec, vec1);

	cout << "\n** TEST3 : insert(iterator position, InputIterator first, InputIterator last) ** " << endl;

	my_vec.insert(my_vec.begin(), my_tem.begin(), my_tem.end());
	vec1.insert(vec1.begin(), temoinv.begin(), temoinv.end());
	display (my_vec, vec1);



}

void 	test_erase()
{
	cout << "\n\n** TESTS ERASE ** " << endl;


	cout << "\n\n** TEST1 erase(iterator position) ** " << endl;

	ft::vector<int>	my_vec(10, 8);
	std::vector<int> vec1   (10, 8);

	my_vec.push_back(404);
	my_vec.insert(my_vec.begin(), 3);
	vec1.push_back(404);
	vec1.insert(vec1.begin(), 3);
	display(my_vec, vec1);
	my_vec.erase(my_vec.begin());
	vec1.erase(vec1.begin());
	display(my_vec, vec1);

	cout << "\n\n** TESTS erase(iterator first, iterator last)** " << endl;

	vec1.erase(vec1.begin() + 1, vec1.end() - 3);
	my_vec.erase(my_vec.begin() + 1, my_vec.end() - 3);
	display(my_vec, vec1);

	
	my_vec.push_back(1024);
	vec1.push_back(1024);
	display(my_vec, vec1);

	cout << "\n\n** TESTS POP BACK USING ERASE ** " << endl;

	my_vec.pop_back();
	vec1.pop_back();
	display(my_vec, vec1);






}


void 	test_construct()
{
		cout << "** TEST1 : insert nb ** " << endl;


}


int main()
{

	test_insert();
	test_erase();
	//ft::vector<int> 		my_vec(1, 8);
	//std::vecto
	//ft::vector<int> 		my_vec2(9, 7);
	//std::vector<int>		r_vec(9, 7);

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

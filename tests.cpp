# include "includes.hpp"
#include <vector>

int main()
{
	std::cout << "FILL SHOULD BE CALLED" << std::endl;
	ft::vector<int> my_vec(1, 7);
	//for (int a: my_vec)
   	std::cout << "My vec begin is " << *(my_vec.begin()) << ' ';
	std::cout << "My vec end is " << *(my_vec.end()) << ' ';
	std::cout << "DIFFERENCE IS " << my_vec.end() - my_vec.begin() << std::endl;
	std::cout << "CURR " << *(my_vec.begin()) << "+ STEP 3 = " << *(my_vec.begin() + 3) << std::endl;

	std::cout << "RANGE SHOULD BE CALLED" << std::endl;
	ft::vector<int> my_vec2(my_vec.begin(), my_vec.end());

	std::vector<int>		r_vec(5, 8);
	std::vector<int>::iterator it;
	for (it = r_vec.begin(); it != r_vec.end(); it++)
		std::cout << " it = " << *it << std::endl;
	//for (int i: r_vec)
   // std::cout << "Begin is " << *(r_vec.begin()) << ' ';
}

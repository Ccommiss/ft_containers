# include "includes.hpp"
#include <vector>

int main()
{
	ft::vector<int> my_vec(7, 9);
	//for (int a: my_vec)
   	std::cout << "My vec begin is " << *(my_vec.begin()) << ' ';
	std::cout << "My vec end is " << *(my_vec.end()) << ' ';
	std::cout << "DIFFERENCE IS " << my_vec.end() - my_vec.begin() << std::endl;
	std::cout << "CURR " << *(my_vec.begin()) << "+ STEP 3 = " << *(my_vec.begin() + 3) << std::endl;
	
	std::vector<int>		r_vec(5);

	//for (int i: r_vec)
    std::cout << "Begin is " << *(r_vec.begin()) << ' ';
}
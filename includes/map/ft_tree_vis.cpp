

#include <cstdarg>
//#   include  <iomanip>
#include "ft_tree.hpp"

/* ---------------------------------------------------------------------------- */
/*							DEBUG FUNCS											*/
/* ---------------------------------------------------------------------------- */
template <typename U, typename V, typename Alloc>
void ft::Tree<U, V, Alloc>::display_children(ft::Node<U> *_curr)
{
	std::string colors;
	_curr->color == ft::Node<U>::BLACK ? colors = "⚫" : colors = "🔴";
	std::cout << "---------------------------"
			  << "\n";
	std::cout << "|";
	std::cout << std::setw(10) << " NODE " << _curr->_data << " (" << colors << ")"
			  << "	  |\n";
	std::cout << "---------------------------"
			  << "\n";
	std::cout << "|";
	if (_curr->leftChild != Tree::nil_node)
	{
		std::cout << std::setw(10) << _curr->leftChild->_data << "  ";
	}
	else
		std::cout << std::setw(10) << "(null)"
				  << "  ";
	std::cout << "|";

	if (_curr->rightChild != Tree::nil_node)
	{
		std::cout << std::setw(10) << _curr->rightChild->_data << "  ";
	}
	else
		std::cout << std::setw(10) << "(null)"
				  << "  ";
	std::cout << "|";
}

template <typename U, typename V, typename Alloc>
int ft::Tree<U, V, Alloc>::validity_check(ft::Node<U> *_curr)
{
	static int i = 0;
	if (_curr == Tree::nil_node)
		return 0;
	if (_curr->leftChild != Tree::nil_node && _curr->color == ft::Node<U>::RED && _curr->leftChild->color == ft::Node<U>::RED)
	{
		out("🔴 ERROR : " << _curr->_data << " is red and so is its left child " << _curr->leftChild->_data);
		return 1;
	}
	if (_curr->rightChild != Tree::nil_node && _curr->color == ft::Node<U>::RED && _curr->rightChild->color == ft::Node<U>::RED)
	{
		out("🔴 ERROR : " << _curr->_data << " is red and so is its righ child " << _curr->rightChild->_data);
		return 1;
	}
	validity_check(_curr->leftChild);
	validity_check(_curr->rightChild);
	return 0;
}

template <typename U, typename V, typename Alloc>
void ft::Tree<U, V, Alloc>::display(ft::Node<U> *_curr)
{
	if (_curr == Tree::nil_node)
		return;
	display_children(_curr);
	std::cout << "\n";
	display(_curr->leftChild);
	display(_curr->rightChild);
}

// template <typename U, typename V, typename Alloc>
// void ft::Tree<U, V, Alloc>::display_data(int a, ...)
// {
// 	va_list args;
// 	va_start(args, a);
// 	std::string family[3] = {" > ft::Node<U> ", " > Parent ", " > GP "};
// 	for (int i = 0; i < 3; i++)
// 	{

// 		ft::Node<U> *_curr = va_arg(args, ft::Node<U> *);
// 		if (_curr != Tree::nil_node)
// 		{
// 			out(family[i] << _curr->_data << " has color " << _curr->color);
// 			// out("ft::Node<U> contains " << _curr->color);
// 		}
// 		else
// 		{
// 			out("Tree::nil_node");
// 		}
// 	}
// }

template <typename T>
void ft_null_ptr(T *p) {
	p = ft::make_pair(404, "null");
}

template <>
void ft_null_ptr(ft::pair<const int, std::string> *p) { ft::pair<const int, std::string> tmp(ft::make_pair<const int, std::string>(-404, "nullnull")); p = &tmp; }


template <>
void ft_null_ptr(ft::pair<const char, int> *p) { ft::pair<const char, int> tmp(ft::make_pair('z', 78785154)); p = &tmp;  }

template <>
void ft_null_ptr(ft::pair<std::string, std::string> *p) { ft::pair<std::string, std::string> tmp(ft::make_pair("nullnull", "nullnull")); p = &tmp; }

template <>
void ft_null_ptr(ft::pair<int, int> *p) { ft::pair<int, int>  tmp(ft::make_pair<int, int>(-404, -404)); p = &tmp; }

template <>
void ft_null_ptr(ft::pair<std::string, int> *p) { ft::pair<std::string, int> tmp(ft::make_pair<std::string, int>("nullnull", -404)); p = &tmp; }

// template <>
// void ft_null_ptr(std::string *p) { p = "null"; }

// template <>
// void ft_null_ptr(int *p) { p = -404; }

template <typename U, typename V, typename Alloc>
void ft::Tree<U, V, Alloc>::calculate_height(ft::Node<U> *node)
{
	U to_be_null;
	ft_null_ptr(&to_be_null);
	if (node == Tree::nil_node)
		return;
	ft::Node<U> *tmp = node;
	int i = 0;
	while (tmp != root)
	{
		tmp = tmp->parent;
		i++;
	}
	int j = 0;
	while (j < 10 && *array[i][j] != U())
		j++;

	array[i][j] = new U(node->_data);
	if (i > this->height)
		this->height = i; // on va prendre que les remplis
	if (node->leftChild != Tree::nil_node)
		calculate_height(node->leftChild);
	else
	{
		int j = 0;
		while (j < 10 && *array[i + 1][j] != U())
			j++;
		array[i + 1][j] = new U(to_be_null);
		array[i + 2][j * 2] = new U(to_be_null);
		array[i + 2][j * 2 + 1] = new U(to_be_null);
		calculate_height(node->leftChild);
	}
	if (node->rightChild != Tree::nil_node)
		calculate_height(node->rightChild);
	else
	{
		int j = 0;
		while (j < 10 && *array[i + 1][j] != U())
			j++;
		array[i + 1][j] = new U(to_be_null);
		array[i + 2][j * 2] = new U(to_be_null);
		array[i + 2][j * 2 + 1] = new U(to_be_null);
		calculate_height(node->rightChild);
	}
}

template <typename U, typename V, typename Alloc>
int ft::Tree<U, V, Alloc>::curr_black_height(U data)
{
	ft::Node<U> *node = find(data);
	int i = 0;
	while (node != root)
	{
		if (node->color == ft::Node<U>::BLACK)
			i++;
		node = node->parent;
	}
	return i;
}

template <typename U, typename V, typename Alloc>
void ft::Tree<U, V, Alloc>::see_tree()
{
	array = new U **[100];
	int a = 0, b = 0;
	while (a < 100)
	{
		array[a] = new U *[100];
		while (b < 100)
		{
			array[a][b] = new U();
			b++;
		}
		b = 0;
		a++;
	}
	U to_be_null;
	ft_null_ptr(&to_be_null);
	height = 0;
	Node<U> *node = root;
		calculate_height(node);
	std::cout << std::setw(40) << (*array[0][0]) << " " << std::endl;
	int nb = 2;
	int black_path = 0;
	for (int i = 1; i < height + 1; i++)
	{
		for (int j = 0; j < nb; j++)
		{
			std::string color = "⚫️";
			if (find(*array[i][j]) != Tree::nil_node)
			{
				color = find(*array[i][j])->color == ft::Node<U>::RED ? "🔴 " : "⚫️";
				if (j % 2 == 0)
					std::cout << std::setw(80 / (nb + 1) - i) << (*array[i][j]) << color << "--|"
							  << "(" << curr_black_height(*array[i][j]) << ")";
				else
					std::cout << std::setw(80 / (nb + 1) - i) << "|--" << (*array[i][j]) << color << "(" << curr_black_height(*array[i][j]) << ")";
			}
			else if (*array[i][j] == to_be_null)
			{
				if (j % 2 == 0)
					std::cout << std::setw(80 / (nb + 1) - i + 2) << "N" << color << "--|";
				else
					std::cout << std::setw(80 / (nb + 1) - i + 2) << "|--"
							  << "N" << color;
			}
		}
		nb *= 2;
		std::cout << "\n\n";
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
			array[i][j] = new U();
	}
}

template <typename U, typename V, typename Alloc>
void ft::Tree<U, V, Alloc>::light_display(ft::Node<U> *root)
{
	if (root == Tree::nil_node)
		return;
	std::cout << root->_data << " ";
	if (root->leftChild != Tree::nil_node)
		light_display(root->leftChild);
	if (root->rightChild != Tree::nil_node)
		light_display(root->rightChild);
}

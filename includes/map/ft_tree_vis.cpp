
#include <iostream>
#include <iomanip>
#include <cstdarg>

#include "ft_tree.hpp"

/* ---------------------------------------------------------------------------- */
/*							DEBUG FUNCS											*/
/* ---------------------------------------------------------------------------- */
template <typename U>
void ft::Tree<U>::display_children(ft::Node<U> *_curr)
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
	if (_curr->leftChild != nullptr)
	{
		std::cout << std::setw(10) << _curr->leftChild->_data << "  ";
	}
	else
		std::cout << std::setw(10) << "(null)"
				  << "  ";
	std::cout << "|";

	if (_curr->rightChild != nullptr)
	{
		std::cout << std::setw(10) << _curr->rightChild->_data << "  ";
	}
	else
		std::cout << std::setw(10) << "(null)"
				  << "  ";
	std::cout << "|";
}

template <typename U>
int ft::Tree<U>::validity_check(ft::Node<U> *_curr)
{
	static int i = 0;
	if (_curr == nullptr)
		return 0;
	if (_curr->leftChild != nullptr && _curr->color == ft::Node<U>::RED && _curr->leftChild->color == ft::Node<U>::RED)
	{
		out("🔴 ERROR : " << _curr->_data << " is red and so is its left child " << _curr->leftChild->_data);
		return 1;
	}
	if (_curr->rightChild != nullptr && _curr->color == ft::Node<U>::RED && _curr->rightChild->color == ft::Node<U>::RED)
	{
		out("🔴 ERROR : " << _curr->_data << " is red and so is its righ child " << _curr->rightChild->_data);
		return 1;
	}
	validity_check(_curr->leftChild);
	validity_check(_curr->rightChild);
	return 0;
}

template <typename U>
void ft::Tree<U>::display(ft::Node<U> *_curr)
{
	if (_curr == nullptr)
		return;
	display_children(_curr);
	std::cout << "\n";
	display(_curr->leftChild);
	display(_curr->rightChild);
}

template <typename U>
void ft::Tree<U>::display_data(int a, ...)
{
	va_list args;
	va_start(args, a);
	std::string family[3] = {" > ft::Node<U> ", " > Parent ", " > GP "};
	for (int i = 0; i < 3; i++)
	{

		ft::Node<U> *_curr = va_arg(args, ft::Node<U> *);
		if (_curr != nullptr)
		{
			out(family[i] << _curr->_data << " has color " << _curr->color);
			// out("ft::Node<U> contains " << _curr->color);
		}
		else
		{
			out("Nullptr");
		}
	}
}

template <typename U>
void ft::Tree<U>::calculate_height(ft::Node<U> *node)
{
	if (node == nullptr)
		return;
	ft::Node<U> *tmp = node;
	int i = 0;
	while (tmp != root)
	{
		tmp = tmp->parent;
		i++;
	}
	int j = 0;
	while (j < 10 && array[i][j] != U())
		j++;
	array[i][j] = node->_data;
	if (i > this->height)
		this->height = i; // on va prendre que les remplis
	if (node->leftChild != nullptr)
		calculate_height(node->leftChild);
	else
	{
		int j = 0;
		while (j < 10 && array[i + 1][j] != U())
			j++;
		this->array[i + 1][j] = -1;
		this->array[i + 2][j * 2] = -1;
		this->array[i + 2][j * 2 + 1] = -1;
		calculate_height(node->leftChild);
	}
	if (node->rightChild != nullptr)
		calculate_height(node->rightChild);
	else
	{
		int j = 0;
		while (j < 10 && array[i + 1][j] != U())
			j++;
		array[i + 1][j] = -1;
		array[i + 2][j * 2] = -1;
		array[i + 2][j * 2 + 1] = -1;
		calculate_height(node->rightChild);
	}
}

template <typename U>
int ft::Tree<U>::curr_black_height(U data)
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

template <typename U>
void ft::Tree<U>::see_tree()
{
	height = 0;
	calculate_height(root);

	std::cout << std::setw(40) << (array[0][0]) << " " << std::endl;
	;
	int nb = 2;
	int black_path = 0;
	for (int i = 1; i < height + 1; i++)
	{
		for (int j = 0; j < nb; j++)
		{
			std::string color = "⚫️";
			if (find(array[i][j]) != nullptr)
			{
				color = find(array[i][j])->color == ft::Node<U>::RED ? "🔴 " : "⚫️";
				if (j % 2 == 0)
					std::cout << std::setw(80 / (nb + 1) - i) << (array[i][j]) << color << "--|"
							  << "(" << curr_black_height(array[i][j]) << ")";
				else
					std::cout << std::setw(80 / (nb + 1) - i) << "|--" << (array[i][j]) << color << "(" << curr_black_height(array[i][j]) << ")";
			}
			else // if (array[i][j] == - reinterpret_cast<U> (-1))
			{
				if (j % 2 == 0)
					std::cout << std::setw(80 / (nb + 1) - i + 2) << "N" << color << "--|";
				else
					std::cout << std::setw(80 / (nb + 1) - i + 2) << "|--"
							  << "N" << color;
			}
		}
		nb *= 2;
		out("\n")
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
			array[i][j] = U();
	}
}

template <typename U>
void ft::Tree<U>::light_display(ft::Node<U> *root)
{
	if (root == nullptr)
		return;
	std::cout << root->_data << " ";
	if (root->leftChild != nullptr)
		light_display(root->leftChild);
	if (root->rightChild != nullptr)
		light_display(root->rightChild);
}


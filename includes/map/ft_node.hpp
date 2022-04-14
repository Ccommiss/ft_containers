#ifndef NODE_HPP
#define NODE_HPP
#include "ft_tree.hpp"
#define out(x) std::cout << x << std::endl;

namespace ft
{

	template <typename T>
	class Node
	{
		template <typename U>
		friend class Tree;
		friend class ft_tree_vis;

	public:
		Node()
		{
			_data = T();
		}
		Node(T data)
		{
			root = nullptr;
			leftChild = nullptr;
			rightChild = nullptr;
			parent = nullptr;
			_data = data;
			color = RED; // par default
		}
		~Node(){};

		Node *getLeftChild()
		{
			return leftChild;
		}
		Node *getRightChild()
		{
			return rightChild;
		}
		Node *getParent()
		{
			return parent;
		}
		int getColor()
		{
			return color;
		}
		void setColor(int newColor)
		{
			color = newColor;
		}
		void flipColor()
		{
			std::string from = color == RED ? "🔴 " : "⚫️";
			std::string to = color == RED ? "⚫️" : "🔴 ";
			out(_data << " goes from " << from << " to " << to);
			color == RED ? color = BLACK : color = RED;
		}

		/*
		 ** If addresses are the same, then this is a left child
		 */
		bool is_left_child()
		{
			if (parent == nullptr) // c root
				return false;
			if (parent->leftChild == nullptr)
				return false;
			if (this == parent->leftChild)
				return true;
			return false;
		}
		bool is_right_child()
		{
			if (parent == nullptr) // c root
				return false;
			if (parent->rightChild == nullptr)
				return false;
			if (this == parent->rightChild)
				return true;
			return false;
		}

		T &getData()  
		{
			return (_data);
		}
		void setData(int data)
		{
			_data = data;
		}

		void setLeftChild(Node *node)
		{
			if (node != nullptr)
				out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
			leftChild = node;
		}
		void setRightChild(Node *node)
		{
			if (node != nullptr)
				out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
			rightChild = node;
		}
		void setParent(Node *newParent)
		{
			if (newParent != nullptr)
				out("Func is :" << __func__ << " on this " << _data << " with node " << newParent->_data);
			;
			parent = newParent;
		}

		enum colors
		{
			RED = 439,
			BLACK = 81435,
			NIL = 404
		};

	private:
		T _data;
		Node *root;
		Node *leftChild;
		Node *rightChild;
		Node *parent;

		int color;
	};
}

template <class T>
std::ostream &operator<<(std::ostream &os, ft::Node<T> &node)
{
	if (&node != nullptr)
	{
		std::string colors;
		node.getColor() == ft::Node<T>::BLACK ? colors = "⚫" : colors = "🔴";
		os << "Node " << node.getData() << " " << colors;
	}
	return os;
}



// // template <>
// std::ostream &operator<<(std::ostream &os, ft::pair < int, std::string> &node)
// {
// 	// ft::pair<int, std::string> lol(4, "bonjour");
// 	// if (&node!= nullptr)
// 	// {
// 		os << node.first;
// 	// }
// 	return os;
// }

#endif

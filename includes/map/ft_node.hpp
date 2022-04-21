#ifndef NODE_HPP
#define NODE_HPP
#include "ft_tree.hpp"
#define out(x) std::cout << x << std::endl;


namespace ft
{
	template <typename U, typename V, typename Alloc>
	class Tree;

	template <typename T>
	class Node
	{
		template <typename U, typename V, typename Alloc>
		friend class Tree;
		friend class ft_tree_vis;

		template <typename Key, typename value, typename Compare, typename Allocator>
		friend class map;

		template<typename it>
		friend struct _Rb_tree_iterator;

		template<typename type>
		friend ft::Node<type>* _Rb_tree_increment(ft::Node<type>* __x) throw();
		template<typename type>
		friend ft::Node<type>* _Rb_tree_decrement(ft::Node<type>* __x) throw();


	public:
		Node()
		{
			_data = T();
		}
		Node(T data, Node *nil_ptr) : _data(data), nil_node(nil_ptr)
		{
			color = RED;
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
			if (parent == nil_node) // c root
				return false;
			if (parent->leftChild == nil_node)
				return false;
			if (this == parent->leftChild)
				return true;
			return false;
		}
		bool is_right_child()
		{
			if (parent == nil_node) // c root
				return false;
			if (parent->rightChild == nil_node)
				return false;
			if (this == parent->rightChild)
				return true;
			return false;
		}

		T &getData()
		{
			return (_data);
		}
		void setData(T data)
		{
			_data = data;
		}

		void setLeftChild(Node *node)
		{
			if (node != nil_node)
				out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
			leftChild = node;
		}
		void setRightChild(Node *node)
		{
			if (node != nil_node)
				out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
			rightChild = node;
		}
		void setParent(Node *newParent)
		{
			if (newParent != nil_node)
				out("Func is :" << __func__ << " on this " << _data << " with node " << newParent->_data);
			;
			parent = newParent;
		}

		enum colors
		{
			RED = 439,
			BLACK = 81435,
		};

	private:
		T 		_data;
		Node 	*root;
		Node 	*leftChild;
		Node 	*rightChild;
		Node 	*parent;
		int		color;
		Node 	*nil_node;
		void	*tree;
	};
}

template <class T>
std::ostream &operator<<(std::ostream &os, ft::Node<T> &node)
{
	if (&node != NULL)
	{
		std::string colors;
		node.getColor() == ft::Node<T>::BLACK ? colors = "⚫" : colors = "🔴";
		os << "Node " << node.getData() << " " << colors;
	}
	return os;
}

#endif

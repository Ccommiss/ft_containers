#ifndef NODE_HPP
#define NODE_HPP
//#include "../utils/debug.hpp"
#include "debug.hpp"
#include "ft_tree.hpp"


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
		template<typename it>
		friend struct _Rb_tree_const_iterator;

		template<typename type>
		friend ft::Node<type>* _Rb_tree_increment(ft::Node<type>* __x) throw();
		template<typename type>
		friend ft::Node<type>* _Rb_tree_decrement(ft::Node<type>* __x) throw();

	public:
		Node() : _data(T())
		{
			color = RED;
		}

		Node(T data, Node *nil_ptr) : _data(data), nil_node(nil_ptr)
		{
			leftChild = nil_node;
			rightChild = nil_node;
			parent = nil_node;
			max = nil_node;
			color = RED;
		}

		Node(const Node<T> &x) : _data(x._data)
		{
			*this = x;
		}

		/*
		**	Operator = overload
		*/
		Node<T> &operator=(const Node<T> &x)
		{
			if (this != &x)
			{
				this->color = x.color;
				this->parent = x.parent;
				this->leftChild = x.leftChild;
				this->rightChild = x.rightChild;
				this->nil_node = x.nil_node;
			}
			return (*this);
		}

		~Node(){ };

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
			color == RED ? color = BLACK : color = RED;
		}

		/*
		** If addresses are the same, then this is a left child
		 */
		bool is_left_child()
		{
			if (this == nil_node)
			{
				if (parent->rightChild != nil_node)
					return true; 
				return false;
			}
			if (parent == nil_node) 
				return false;
			if (parent->leftChild == nil_node)
				return false;
			if (this == parent->leftChild)
				return true;
			return false;
		}

		bool is_right_child()
		{
			if (this == nil_node)
			{
				if (parent->leftChild != nil_node)
					return true; 
				return false;
			}
			if (parent == nil_node) 
				return false;
			if (parent->rightChild == nil_node)
				return false;
			if (this == parent->rightChild)
				return true;
			return false;
		}

		T &getData() const
		{
			return (_data);
		}
	
		void setLeftChild(Node *node)
		{
			leftChild = node;
		}

		void setRightChild(Node *node)
		{
			rightChild = node;
		}

		void setParent(Node *newParent)
		{
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
		Node	*max;
	};
}

template <class T>
std::ostream &operator<<(std::ostream &os, ft::Node<T> &node)
{
	std::string colors;
	node.getColor() == ft::Node<T>::BLACK ? colors = "⚫" : colors = "🔴";
	os << "Node " << node.getData() << " " << colors;
	return os;
}

#endif

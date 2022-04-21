
#include "../includes.hpp"
#include "ft_node.hpp"
#include "ft_tree.hpp"

namespace ft
{
	template<typename T>
	ft::Node<T>* _Rb_tree_increment(ft::Node<T>* x) throw()
	{
		if (x->rightChild != x->nil_node)
		{
			x = x->rightChild;
			while (x->leftChild != x->nil_node) // PAS SURE
				x = x->leftChild;
		}
		else
		{
			ft::Node<T>* y = x->parent;
			if (y == x->nil_node) //mon ajout a 18h
				return y->nil_node; //en gros on a un seul elem je crois on est sur le root
			while (x == y->rightChild)
			{
				x = y;
				y = y->parent;
			}
			if (x->rightChild != y)
				x = y;
		}
		return x;
	}

	template<typename T>
	ft::Node<T>* _Rb_tree_decrement(ft::Node<T>* x) throw ()
	{
		if (x->color == Node<T>::RED && x->parent->parent == x)
			x = x->rightChild;
		else if (x->leftChild != x->nil_node)
		{
			ft::Node<T>* y = x->leftChild;
			while (y->rightChild != x->nil_node)
				y = y->rightChild;
			x = y;
		}
		else
		{
			ft::Node<T>* y = x->parent;
			while (x == y->leftChild)
			{
				x = y;
				y = y->parent;
			}
			x = y;
		}
		return x;
	}

	template<typename T>
	struct _Rb_tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef T  value_type; // la paire
		typedef T& reference; // reference sur paire
		typedef T* pointer; // ptr sur paire

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t			 	   difference_type;

		typedef _Rb_tree_iterator<T>		_Self;
		typedef Node<T>* node;
		//typedef _Rb_tree_node<T>* _Link_type;

		_Rb_tree_iterator() : _curr(0) { }
		_Rb_tree_iterator(node x) : _curr(x) { }
		reference operator*() const
		{
			return (_curr->_data);
		}
		pointer operator->() const
		{
			return &(operator*());
		}
		_Self& operator++()
		{
			_curr = _Rb_tree_increment(_curr);
			return *this;
		}

		_Self operator++(int)
		{
			_Self __tmp = *this;
			_curr = _Rb_tree_increment(_curr);
			return __tmp;
		}

		_Self& operator--()
		{
			Tree <T, T, std::allocator<T> > *tree = (Tree <T, T, std::allocator<T> > *)_curr->tree;
			if (_curr == _curr->nil_node)
				_curr = tree->getMaxSuccessor(tree->getRootPtr());
			else
				_curr = _Rb_tree_decrement(_curr);
			return *this;
		}

		_Self operator--(int)
		{
			_Self __tmp = *this;
			Tree <T, T, std::allocator<T> > *tree = (Tree <T, T, std::allocator<T> > *)_curr->tree;
			if (_curr == _curr->nil_node)
				_curr = tree->getMaxSuccessor(tree->getRootPtr());
			else
				_curr = _Rb_tree_decrement(_curr);
			return __tmp;
		}

		friend bool operator==(const _Self& x, const _Self& y)
		{
			return x._curr == y._curr;
		}

		friend bool operator!=(const _Self& x, const _Self& y)
		{
			return x._curr != y._curr;
		}
		node  _curr; // les it sont des ptr sur noeuds
	};

}

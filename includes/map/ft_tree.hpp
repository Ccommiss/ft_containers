#ifndef TREE_HPP
#define TREE_HPP

#include "ft_pair.hpp"
#include "ft_node.hpp"
#include "debug.hpp"

namespace ft
{

	template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T> >
	class Tree
	{
		template <typename U>
		friend class Node;
		template <typename Key, typename valuetype, typename compfunc, typename alloctype>
		friend class map;

		typedef typename Allocator::size_type 							size_type;
		typedef typename Allocator::template rebind< Node<T> >::other 	_allocnode;


	private:
		Node<T> 							*root;
		Node<T> 							*nil_node;
		size_type 							_size; 
		Compare 							_comp;
		_allocnode 							alloc;

		// pour debug
		int blacks;
		T ***array; 
		int height;

		public:
		Tree(Compare c) : _comp(c), alloc(_allocnode()) 
		{
			Node<T> nullnode;
			nil_node = alloc.allocate(1);
			alloc.construct(nil_node, nullnode);
			nil_node->leftChild = nil_node;
			nil_node->rightChild = nil_node;
			nil_node->parent = nil_node;
			nil_node->nil_node = nil_node;
			root = nil_node;
			blacks = 0;
			_size = 0;
		}

		void delete_nodes(Node<T> *node)
		{
			if (node != nil_node)
			{
				Node<T> *tmp_right = node->rightChild;
				Node<T> *tmp_left = node->leftChild;
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				delete_nodes(tmp_left);
				delete_nodes(tmp_right);
			}
		}

		Tree<T, Compare, Allocator>& operator=(const Tree<T, Compare, Allocator> &x)
		{
			Node<T> *copy_root(x.root);
			Node<T> *copy_nil(x.nil_node);
			root = copy_root;
			nil_node = copy_nil;
			_size = x._size;
			return (*this);
		}

		~Tree()
		{
			delete_nodes(root);
			alloc.destroy(nil_node);
			alloc.deallocate(nil_node, 1);
		}


		void	swap(Tree<T, Compare, Allocator> &x)
		{
			std::swap(root, x.root);
			std::swap(nil_node, x.nil_node);
			std::swap(_size, x._size);
		}

		/*
		** Functions;
		*/
		int getRoot()
		{
			return root->_data;
		}

		Node<T> *getRootPtr()
		{
			return root;
		}

		/**************************************************/
		/**	FIND 										  */
		/**************************************************/

		Node<T> *find(const T key) const
		{
			Node<T> *node = root;
			while (node != nil_node)
			{
				if (!_comp(key, node->_data) && !_comp(node->_data, key))
				{
					nil_node->max = getMaxSuccessor(root);
					return node;
				}
				else if (_comp(key, node->_data) == true)
					node = node->leftChild;
				else
					node = node->rightChild;
			}
			nil_node->max = getMaxSuccessor(root);
			return nil_node;
		}

		/***************************************************
		**
		**	Insert
		**
		****************************************************/

		template <typename data_type>
		bool is_in_tree(data_type data)
		{
			return (find(data) != nil_node ? true : false);
		}

		template <typename X, typename Y>
		bool is_in_tree(ft::pair<X, Y> data)
		{
			return (find(data) != nil_node ? true : false);
		}

		/*
		**	insert
		**	@brief first inserr
		*/
		Node<T>* insert(const T data)
		{
			Node<T> tmp(data, nil_node);
			Node<T> *node = alloc.allocate(1);
			alloc.construct(node, tmp);
			if (is_in_tree(data))
			{
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				return find(data);
			}
			root = insert(root, node);
			recolorAndRotate(node);
			_size += 1;
			nil_node->max = getMaxSuccessor(root);
			return node;
		}

		Node<T> *insert(Node<T> *node, Node<T> *newNode)
		{
			if (root == nil_node)
			{
				newNode->setColor(Node<T>::BLACK);
				root = newNode;
				return newNode;
			}
			if (node == nil_node)
				return (newNode);
			if (_comp(newNode->_data, node->_data) == true)
			{
				node->setLeftChild(insert(node->leftChild, newNode));
				node->leftChild->setParent(node);
			}
			if (_comp(newNode->_data, node->_data) == false)
			{
				node->setRightChild(insert(node->rightChild, newNode));
				node->rightChild->setParent(node);
			}
			return node;
		}

		/*
		**	Recolor and rotate
		**	@brief Once we just inserted the node at the right place,
		**		 	we check its position relatively
		**
		** 	@param node the newly inserted node
		*/
		void recolorAndRotate(Node<T> *node)
		{
			Node<T> *parent = node->getParent();
			if (node != root && node->color == Node<T>::RED && parent->color == Node<T>::RED)
			{
				Node<T> *grandParent = node->parent->parent;
				Node<T> *uncle;
				if (grandParent == nil_node)
					uncle = nil_node;
				else
					uncle = parent->is_left_child() ? uncle = grandParent->rightChild : uncle = grandParent->leftChild;
				if (uncle != nil_node && uncle->getColor() == Node<T>::RED)
					handleRecoloring(parent, uncle, grandParent);
				else if (parent && parent->is_left_child())
					handle_lefts(node, parent, grandParent);
				else if (parent && !parent->is_left_child())
					handle_rights(node, parent, grandParent);
			}
			root->setColor(Node<T>::BLACK);
		}

		/*
		** updateChildrenOfParentNode replace nde by tempnode
		**	@brief tempNode now replaces node as the left or right child of node->parent
		**	@param node the old child node
		**	@param tempNode the new child of node->parent
		*/
		void updateChildrenOfParentNode(Node<T> *node, Node<T> *tempNode)
		{
			Node<T>* tmp = node;
			if (node->parent == nil_node)
				root = tempNode;
			else if (node->is_left_child())
				node->parent->setLeftChild(tempNode);
			else
				node->parent->setRightChild(tempNode);
			if (tempNode == nil_node)
			{
				alloc.destroy(tmp);
				alloc.deallocate(tmp, 1);
			}
		}

		/*
		**	RotateLeft
		**	@brief shifts a subtree to be shifted
		**	@param the node to be shifted as a left child
		**
		**	example right-left situation
		**
		**       input:         output:
		**        x               y
		**       / \             / \     x and y
		**      .   y           x   .    swapped
		**         / \         / \
		**        z   .       .   z
		**
		*/
		void rotateLeft(Node<T> *node)
		{
			// Node<T> is x
			Node<T> *rightNode = node->rightChild;
			// right node = y
			node->setRightChild(rightNode->leftChild);
			// new child of x is z
			if (node->rightChild != nil_node)
			{
				// new parent of z is x
				node->rightChild->setParent(node);
			}
			// new left child of y is x
			rightNode->setLeftChild(node);
			// new parent of y is ex parent of x (nil_node in this case)
			rightNode->setParent(node->parent);
			updateChildrenOfParentNode(node, rightNode);
			// new parent of x is y
			node->setParent(rightNode);
		}

		/*
		**
		**	Rotate right:
		**	Shifts a subtree to the right
		**
		**     input:         output:
		**         x             y
		**        / \           / \       x and y
		**       y   .         .   x      swapped
		**      / \               / \
		**     .   z             z   .
		**
		*/
		void rotateRight(Node<T> *node)
		{
			Node<T> *leftNode = node->leftChild;
			node->setLeftChild(leftNode->rightChild);
			if (node->leftChild != nil_node)
				node->leftChild->setParent(node);
			leftNode->setRightChild(node);
			leftNode->setParent(node->parent);
			updateChildrenOfParentNode(node, leftNode);
			node->setParent(leftNode);
		}

		/*
		**	Handle lefts
		**	@brief handles left-situation : left-heavy or left-right situations
		**	@param node,parent,grandParent nodes to be shifted
		*/
		void handle_lefts(Node<T> *node, Node<T> *parent, Node<T> *grandParent)
		{
			int LR = 0;
			if (node->is_right_child())
			{
				rotateLeft(parent);
				LR = 1;
			}
			if (LR == 1)
				node->flipColor();
			else
				parent->flipColor();
			if (grandParent != nil_node)
				grandParent->flipColor();
			rotateRight(grandParent);
			if (node != root)
				recolorAndRotate(node->is_left_child() ? parent : grandParent);
		}

		/*
		**	Handle rights
		**	@brief handles right situations : right-heavy or right-left situations
		**	@param node,parent,grandParent nodes to be shifted
		*/
		void handle_rights(Node<T> *node, Node<T> *parent, Node<T> *grandParent)
		{
			int RL = 0;
			if (node->is_left_child())
			{
				rotateRight(parent);
				RL = 1;
			}
			if (RL == 1)
				node->flipColor();
			else
				parent->flipColor();
			if (grandParent != nil_node)
				grandParent->flipColor();
			rotateLeft(grandParent);
			if (node != root)
				recolorAndRotate(node->is_left_child() ? grandParent : parent);
		}

		void handleRecoloring(Node<T> *parent, Node<T> *uncle, Node<T> *grandParent)
		{
			uncle->flipColor();
			parent->flipColor();
			grandParent->flipColor();
			recolorAndRotate(grandParent);
		}

		/*	**************************************************
		**
		**	DELETE
		**
		*/

		bool erase(T data)
		{
			if (erase_and_balance(data) == true)
			{
				_size -= 1;
				nil_node->max = getMaxSuccessor(root);
				return true;
			}
			nil_node->max = getMaxSuccessor(root);
			return false;
		}

		Node<T> *getMaxSuccessor(Node<T> *node) const
		{
			if (node->rightChild != nil_node)
				return getMaxSuccessor(node->rightChild);
			return node;
		}

		Node<T> *getMinSuccessor(Node<T> *node) const
		{
			if (node == nil_node)
				return nil_node;
			if (node->leftChild != nil_node)
				return getMinSuccessor(node->leftChild);
			return node;
		}

		Node<T> *getSibling(Node<T> *node)
		{
			if (node->is_left_child() && node->parent->rightChild != nil_node)
				return node->parent->rightChild;
			else if (node->is_right_child() && node->parent->leftChild != nil_node)
				return node->parent->leftChild;
			return nil_node;
		}

		bool black_nephews(Node<T> *node)
		{
			if (!(getSibling(node)->leftChild == nil_node || (getSibling(node)->leftChild != nil_node && getSibling(node)->leftChild->getColor() == Node<T>::BLACK)))
				return false;
			if (!(getSibling(node)->rightChild == nil_node || getSibling(node)->rightChild->getColor() == Node<T>::BLACK)) 
				return false;
			return true;
		}

		void handleBlackSiblingWithAtLeastOneRedChild(Node<T> *node, Node<T> *sibling)
		{
			bool nodeIsLeftChild = node->is_left_child();
			/*Case 5: Black sibling with at least one red child + "outer nephew" is black
			 	--> Recolor sibling and its child, and rotate around sibling */
			if (nodeIsLeftChild && (sibling->rightChild == nil_node || sibling->rightChild->color == Node<T>::BLACK))
			{
				sibling->leftChild->color = Node<T>::BLACK;
				sibling->color = Node<T>::RED;
				rotateRight(sibling);
				sibling = getSibling(node);
			}
			else if (!nodeIsLeftChild && (sibling->rightChild == nil_node 
				|| sibling->leftChild->color == Node<T>::BLACK))
			{
				sibling->rightChild->color = Node<T>::BLACK;
				sibling->color = Node<T>::RED;
				rotateLeft(sibling);
				sibling = getSibling(node);
			}
			/*Case 6: Black sibling with at least one red child + "outer nephew" is red
			 	--> Recolor sibling + parent + sibling's child, and rotate around parent */
			sibling->color = node->parent->color;
			node->parent->color = Node<T>::BLACK;
			if (nodeIsLeftChild)
			{
				sibling->rightChild->color = Node<T>::BLACK;
				rotateLeft(node->parent);
			}
			else
			{
				sibling->leftChild->color = Node<T>::BLACK;
				rotateRight(node->parent);
			}
		}

		/* Recolor and rotate */ 
		void handleRedSibling(Node<T> *node, Node<T> *sibling)
		{
			sibling->setColor(Node<T>::BLACK);
			node->parent->color = Node<T>::RED;
			if (node == node->parent->leftChild)
				rotateLeft(node->parent);
			else
				rotateRight(node->parent);
		}

		void fixRedBlackPropertiesAfterDelete(Node<T> *node)
		{
																							/*Case 1: Examined node is root, end of recursion */
			if (node == root)
				return;
			Node<T> *sibling = getSibling(node);	
			if (sibling->color == Node<T>::RED)												/* Case 2: Red sibling */
			{
				handleRedSibling(node, sibling);
				sibling = getSibling(node);
				if (sibling == nil_node) return; 
			}	
			if (sibling->color == Node<T>::BLACK && black_nephews(node) == true) 			/*Cases 3+4: Black sibling with two black children */
			{
				sibling->color = Node<T>::RED;	
				if (node->parent->color == Node<T>::RED)									/* Case 3: Black sibling with two black children + red parent */
					node->parent->color = Node<T>::BLACK;
				else																		/* Case 4: Black sibling with two black children + black parent */
					fixRedBlackPropertiesAfterDelete(node->parent);
			}
			else																			/* Case 5+6: Black sibling with at least one red child */
				handleBlackSiblingWithAtLeastOneRedChild(node, sibling);
		}

		Node<T> *deleteNodeWithZeroOrOneChild(Node<T> *node)
		{
			Node <T> *tmp;

			/* Node<T> has ONLY a left child --> replace by its left child */
			if (node->leftChild != nil_node)
			{
				tmp = node->leftChild;
				updateChildrenOfParentNode(node, node->leftChild);
				node->leftChild->setParent(node->parent);
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				return tmp; 
			}
			/* Node<T> has ONLY a right child --> replace by its right child */ 
			else if (node->rightChild != nil_node)
			{
				tmp = node->rightChild;
				updateChildrenOfParentNode(node, node->rightChild);
				node->rightChild->setParent(node->parent);
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				return tmp; 

			}
			/* Node<T> has no children -->
			** * node is red --> just remove it
			** * node is black --> replace it by a temporary NIL node (needed to fix the R-B rules)
			*/
			else
			{
				int color = node->getColor();
				Node<T> *parent_save = node->parent;
				updateChildrenOfParentNode(node, nil_node);
				if (color == Node<T>::BLACK)
					nil_node->setParent(parent_save);
				return nil_node;
			}
		}

		/*
		**		Copy_successor copies data from successor to node.
		**		Had to do this cause you cannot copy pair.first in a regular way
		**		as key is marked const.
		*/
		void copy_successor(Node<T> *node, Node<T> *inOrderSuccessor)
		{
			Node<T> copy(inOrderSuccessor->_data, nil_node);
			Node<T> *tmp = alloc.allocate(1);
			alloc.construct(tmp, copy);
			tmp->leftChild = node->leftChild; 
			tmp->rightChild = node->rightChild;
			tmp->leftChild->parent = tmp;
			tmp->rightChild->parent = tmp;
			tmp->nil_node = node->nil_node;
			tmp->parent = node->parent;
			if (root == node) root = tmp;
			node->is_left_child() ? node->parent->leftChild = tmp : node->parent->rightChild = tmp;
			if (nil_node->rightChild == node) nil_node->rightChild = tmp;
			if (nil_node->leftChild == node) nil_node->leftChild = tmp;
			tmp->color = node->color;
			alloc.destroy(node);
			alloc.deallocate(node, 1);
			node = tmp;
		}

		bool erase_and_balance(T data)
		{
			Node<T> 		*movedUpNode;
			int 			deletedNodeColor;
			Node<T> *node 	= find(data);
			if (node == nil_node)
				return false;
			if (node->leftChild == nil_node || node->rightChild == nil_node)						/* Node<T> has zero or one child */
			{
				deletedNodeColor = node->color;
				movedUpNode = deleteNodeWithZeroOrOneChild(node);
			}
			else																					/* Two children case */
			{
				Node<T> *inOrderSuccessor = getMaxSuccessor(node->leftChild);						
				copy_successor(node, inOrderSuccessor);			
				deletedNodeColor = inOrderSuccessor->getColor();
				movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
			}
			if (deletedNodeColor == Node<T>::BLACK)													/* Have to fix only if black */
				fixRedBlackPropertiesAfterDelete(movedUpNode); 
			return true;
		}

		void display_children(Node<T> *_curr);
		int validity_check(Node<T> *_curr);
		void display(Node<T> *_curr);
		void calculate_height(Node<T> *node);
		int curr_black_height(T data);
		void see_tree();
		void light_display(Node<T> *root);
	};
}
#endif


// class Node;
#ifndef TREE_HPP
#define TREE_HPP
#include <iostream>
#include <iomanip>
#include <cstdarg>

#include "ft_node.hpp"

#define out(x) std::cout << x << std::endl;
namespace ft {

	template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T> >
	class Tree
	{
		template <typename U>
		friend class Node;

		template <typename Key, typename valuetype, typename compfunc, typename alloctype>
		friend class map;

		typedef typename Allocator::size_type 						size_type;


		private:
		Node<T>* root;
		Node<T>* _end;
		Node<T>* nil_node;
		size_type _size; // size of tree 
		Compare    _comp; // objet de comparaison
	
		// pour debug 
		int blacks;
		T array[100][100];
		int height;
		

		public:
		Tree(Compare c)  : _comp(c) // une instance de std::less<Key> par defaut 
		{
			std::cout << "tree constructor" << std::endl;
			nil_node = new Node<T>(T(), NULL);
			nil_node->tree = this;
			root = nil_node;
			nil_node->nil_node = nil_node;
			blacks = 0;
			_size = 0;
		}

		void 		delete_nodes(Node<T> *node)
		{
			if (node != nil_node)
			{
				Node<T> *tmp_right = node->rightChild;
				Node<T> *tmp_left = node->leftChild;
				delete node;
				delete_nodes(tmp_left);
				delete_nodes(tmp_right);
			}
		}

		~Tree() {
			out("tree destructor")
			delete_nodes(root);
			delete nil_node;
		}

		/*
		** Functions;
		*/
		int getRoot()
		{
			return root->_data;
		}

		Node<T>* getRootPtr()
		{
			return root;
		}

		/**************************************************/
		/**	FIND 										  */
		/**************************************************/

		Node<T>* find(T key)
		{
			Node<T>* node = root;
			while (node != nil_node)
			{
				if (!_comp(key, node->_data) && !_comp(node->_data, key))
					return node;
				else if (_comp(key, node->_data) == true) 
					node = node->leftChild;
				else
					node = node->rightChild;
			}
			return nil_node;
		}

		/***************************************************
		**
		**	Insert
		**
		****************************************************/

		template <typename data_type>
		bool	is_in_tree(data_type data)
		{
			return (find(data) != nil_node ? true : false);
		}

		template <typename X, typename Y>
		bool	is_in_tree(ft::pair<X, Y> data)
		{
			return (find(data) != nil_node ? true : false);
		}

		/*
		**	insert
		**	@brief first inserr
		*/
		void insert(const T data)
		{
			Node<T>* node = new Node<T>(data, nil_node);
			node->parent = nil_node;
			node->leftChild = nil_node;
			node->rightChild = nil_node;
			node->tree = this;
			out("To insert : " << data)
				if (is_in_tree(data))
				{
					std::cout << "/!\\ Cannot add twice the same value, " << data << " already present" << std::endl;
					return ; //*this;
				}
			root = insert(root, node);
			recolorAndRotate(node);
			_size += 1;
		//	return *this;
		}

		Node<T>* insert(Node<T>* node, Node<T>* newNode)
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

		template <typename U, typename V>
		Node<T>* insert(Node<T>* node, Node<T>* newNode)
		{
			if (root == nil_node)
			{
				newNode->setColor(Node<T>::BLACK);
				root = newNode;
				return newNode;
			}
			if (node == nil_node)
				return (newNode);
			if (Compare()(newNode->_data, node->_data) == true)
			{
				node->setLeftChild(insert(node->leftChild, newNode));
				node->leftChild->setParent(node);
			}
			if (Compare()(newNode->_data, node->_data) == false)
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
		void recolorAndRotate(Node<T>* node)
		{
			out("Func is :" << __func__ << " on node " << *node);
			Node<T>* parent = node->getParent();
			if (node != root && node->color == Node<T>::RED && parent->color == Node<T>::RED)
			{
				Node<T>* grandParent = node->parent->parent;
				Node<T>* uncle;
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
			out("NODE COLOR IS " << node->color);
			root->setColor(Node<T>::BLACK);
			out("root as black")
		}

		/*
		** updateChildrenOfParentNode
		**	@brief tempNode now replaces node as the left or right child of node->parent
		**	@param node the old child node
		**	@param tempNode the new child of node->parent
		*/
		void updateChildrenOfParentNode(Node<T>* node, Node<T>* tempNode)
		{
			out("Func is :" << __func__ << " on node " << *node);

			if (node->parent == nil_node)
				root = tempNode;
			else if (node->is_left_child())
				node->parent->setLeftChild(tempNode);
			else
				node->parent->setRightChild(tempNode);
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
		void rotateLeft(Node<T>* node)
		{
			// Node<T> is x
			out("Func is :" << __func__ << " on node " << *node);
			Node<T>* rightNode = node->rightChild;
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

			// output changes
			out(*node << " parent is " << *node->parent);
			out(*node << " right child " << *node->rightChild);
			out(*rightNode << " parent is " << *rightNode->parent);
			out(*rightNode << " left child is " << *rightNode->leftChild);
			out("root is " << *root)
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
		void rotateRight(Node<T>* node)
		{
			out("Func is :" << __func__ << " on node " << *node);

			Node<T>* leftNode = node->leftChild;
			out("Left node " << leftNode->_data)
				node->setLeftChild(leftNode->rightChild);
			if (node->leftChild != nil_node)
				node->leftChild->setParent(node);
			leftNode->setRightChild(node);
			leftNode->setParent(node->parent);
			updateChildrenOfParentNode(node, leftNode);
			node->setParent(leftNode);
			out("Node<T> " << node->_data << " and new parent " << node->parent->_data);
		}

		/*
		**	Handle lefts
		**	@brief handles left-situation : left-heavy or left-right situations
		**	@param node,parent,grandParent nodes to be shifted
		*/
		void handle_lefts(Node<T>* node, Node<T>* parent, Node<T>* grandParent)
		{
			out("Func is :" << __func__ << " on node " << *node);
			display_data(3, node, parent, grandParent);
			display(root);
			int LR = 0;
			if (node->is_right_child())
			{
				out("Left-right situation found");
				rotateLeft(parent);
				LR = 1;
			}
			// HERE IS LEFT HEAVY SITUATION
			out("Left-left situation found");
			if (LR == 1)
				node->flipColor(); // PK LE PARENT DANS LE CODE SOURCE ?
			else
				parent->flipColor();
			if (grandParent != nil_node)
				grandParent->flipColor();
			rotateRight(grandParent);
			if (node != root) // EST CE NORMAL ?
				recolorAndRotate(node->is_left_child() ? parent : grandParent);
		}

		/*
		**	Handle rights
		**	@brief handles right situations : right-heavy or right-left situations
		**	@param node,parent,grandParent nodes to be shifted
		*/
		void handle_rights(Node<T>* node, Node<T>* parent, Node<T>* grandParent)
		{
			out("Func is :" << __func__ << " on node " << *node);
			display_data(3, node, parent, grandParent);
			int RL = 0;
			if (node->is_left_child())
			{
				out("Right-left situation found")
					rotateRight(parent);
				RL = 1;
			}
			out("Right-right situation found");
			if (RL == 1)
				node->flipColor();
			else
				parent->flipColor();
			if (grandParent != nil_node)
				grandParent->flipColor();
			rotateLeft(grandParent);
			if (node != root) // EST CE NORMAL ?
				recolorAndRotate(node->is_left_child() ? grandParent : parent);
		}

		void handleRecoloring(Node<T>* parent, Node<T>* uncle, Node<T>* grandParent)
		{
			uncle->flipColor();
			parent->flipColor();
			grandParent->flipColor();
			recolorAndRotate(grandParent);
		}

		/***************************************************
		**
		**	DELETE
		**
		****************************************************/

		void del(int data)
		{
			del(data, root);
			_size -= 1; // a modifier si le del a echoue par exemple
		}

		Node<T>* getMaxSuccessor(Node<T>* node)
		{
			if (node->rightChild != nil_node)
				return getMaxSuccessor(node->rightChild);
			return node;
		}

		Node<T>* getMinSuccessor(Node<T>* node)
		{
			if (node->leftChild != nil_node)
				return getMinSuccessor(node->leftChild);
			return node;
		}

		Node<T>* getSibling(Node<T>* node)
		{
			if (node->is_left_child() && node->parent->rightChild != nil_node)
				return node->parent->rightChild;
			else if (node->is_right_child() && node->parent->leftChild != nil_node)
				return node->parent->leftChild;
			return nil_node;
		}

		bool black_nephews(Node<T>* node)
		{
			if (!(getSibling(node)->leftChild == nil_node || getSibling(node)->leftChild->getColor() == Node<T>::BLACK))
				return false;
			if (!(getSibling(node)->rightChild == nil_node || getSibling(node)->rightChild->getColor() == Node<T>::BLACK)) // le neveu droit
				return false;
			std::cout << "WOWOW TRU" << std::endl;
			return true;
		}

		void handleBlackSiblingWithAtLeastOneRedChild(Node<T>* node, Node<T>* sibling)
		{
			bool nodeIsLeftChild = node->is_left_child();

			// Case 5: Black sibling with at least one red child + "outer nephew" is black
			// --> Recolor sibling and its child, and rotate around sibling
			if (nodeIsLeftChild && (sibling->rightChild == nil_node || sibling->rightChild->color == Node<T>::BLACK))
			{
				sibling->leftChild->color = Node<T>::BLACK;
				sibling->color = Node<T>::RED;
				rotateRight(sibling);
				sibling = getSibling(node);
				// sibling = node->parent->rightChild;
			}
			else if (!nodeIsLeftChild && (sibling->rightChild == nil_node || sibling->leftChild->color == Node<T>::BLACK))
			{
				sibling->rightChild->color = Node<T>::BLACK;
				sibling->color = Node<T>::RED;
				rotateLeft(sibling);
				sibling = getSibling(node);
			}

			// Fall-through to case 6...
			// Case 6: Black sibling with at least one red child + "outer nephew" is red
			// --> Recolor sibling + parent + sibling's child, and rotate around parent
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

		void handleRedSibling(Node<T>* node, Node<T>* sibling)
		{
			// Recolor...
			sibling->setColor(Node<T>::BLACK);
			node->parent->color = Node<T>::RED;

			// ... and rotate
			if (node == node->parent->leftChild)
				rotateLeft(node->parent);
			else
				rotateRight(node->parent);
		}

		void fixRedBlackPropertiesAfterDelete(Node<T>* node)
		{
			out("Func is :" << __func__ << " on node " << *node);
			// Case 1: Examined node is root, end of recursion
			if (node == root || node == nil_node)
			{
				// Uncomment the following line if you want to enforce black roots (rule 2):
				// node.color = BLACK;
				return;
			}
			Node<T>* sibling = getSibling(node);
			out(*sibling) if (sibling == nil_node) return; // TEST
			// Case 2: Red sibling
			if (sibling->color == Node<T>::RED)
			{
				out("CASE 2 : red sibling " << *sibling);
				handleRedSibling(node, sibling);
				sibling = getSibling(node);
				out("NEW SIBLING " << *sibling)		// Get new sibling for fall-through to cases 3-6
					if (sibling == nil_node) return; // TEST
			}
			// Cases 3+4: Black sibling with two black children
			if (sibling->color == Node<T>::BLACK && black_nephews(node) == true)
			{
				sibling->color = Node<T>::RED;
				out("ICI 3 + 4 ")
					// Case 3: Black sibling with two black children + red parent
					if (node->parent->color == Node<T>::RED)
					{
						out("CASE 3   parent is " << *(node->parent));
						node->parent->color = Node<T>::BLACK;
					}
				// Case 4: Black sibling with two black children + black parent
					else
					{
						out("CASE 4");
						fixRedBlackPropertiesAfterDelete(node->parent);
					}
			}
			// Case 5+6: Black sibling with at least one red child
			else
			{
				out("CASE 5 + 6 ");
				handleBlackSiblingWithAtLeastOneRedChild(node, sibling);
			}
		}

		Node<T>* deleteNodeWithZeroOrOneChild(Node<T>* node)
		{
			out("Func is :" << __func__ << " on node " << *node);

			// Node<T> has ONLY a left child --> replace by its left child
			if (node->leftChild != nil_node)
			{
				updateChildrenOfParentNode(node, node->leftChild);
				out("UPDATED NODE *NODE" << *node << "AND PARENT " << *(node->parent))
					node->leftChild->setParent(node->parent);
				return node->leftChild; // moved-up node
			}
			// Node<T> has ONLY a right child --> replace by its right child
			else if (node->rightChild != nil_node)
			{
				updateChildrenOfParentNode(node, node->rightChild);
				node->rightChild->setParent(node->parent);
				return node->rightChild; // moved-up node
			}
			// Node<T> has no children -->
			// * node is red --> just remove it
			// * node is black --> replace it by a temporary NIL node (needed to fix the R-B rules)
			else
			{
				// Node<T> *newChild = nil_node;
				Node<T>* newChild = node->getColor() == Node<T>::BLACK ? nil_node : nil_node;

				// if (newChild != nil_node && newChild->_data == 404)
				//	newChild->setColor(Node<T>::NIL);
				updateChildrenOfParentNode(node, newChild);
				if (newChild != nil_node)
				{
					newChild->setParent(node->parent);
				}
				return newChild;
			}
		}

		void del(int data, Node<T>* root)
		{
			out("Func is :" << __func__ << " on node " << *root);

			Node<T>* node = find(data);
			if (node == nil_node || node == nil_node) // PAS SURE POUR LA DEUXIEME !!
				return;
			// At this point, "node" is the node to be deleted
			// In this variable, we'll store the node at which we're going to start to fix the R-B
			// properties after deleting a node->
			Node<T>* movedUpNode;
			int deletedNodeColor;

			// Node<T> has zero or one child
			if (node->leftChild == nil_node || node->rightChild == nil_node)
			{
				movedUpNode = deleteNodeWithZeroOrOneChild(node);
				deletedNodeColor = node->color;
			}
			// Node<T> has two children
			else
			{
				// Find minimum node of right subtree ("inorder successor" of current node)
				Node<T>* inOrderSuccessor = getMaxSuccessor(node->leftChild);
				// Copy inorder successor's data to current node (keep its color!)
				node->setData(inOrderSuccessor->_data);
				// Delete inorder successor just as we would delete a node with 0 or 1 child
				movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
				deletedNodeColor = inOrderSuccessor->getColor();
			}
			if (deletedNodeColor == Node<T>::BLACK)
			{
				fixRedBlackPropertiesAfterDelete(movedUpNode);
				// Remove the temporary NIL node
				if (movedUpNode == nil_node)
				{
					updateChildrenOfParentNode(movedUpNode, nil_node);
				}
			}
		}

		void display_children(Node<T>* _curr);
		int validity_check(Node<T>* _curr);
		void display(Node<T>* _curr);
		void display_data(int a, ...);
		void calculate_height(Node<T>* node);
		int curr_black_height(T data);
		void see_tree();
		void light_display(Node<T>* root);
	};
}
#endif

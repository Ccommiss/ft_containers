
// class Node;
#ifndef TREE_HPP
#define TREE_HPP
#include <iostream>
#include <iomanip>
#include <cstdarg>

#include "ft_node.hpp"

#define out(x) std::cout << x << std::endl;
namespace ft {

template <typename T>
class Tree
{
	template <typename U>
	friend class Node;

private:
	Node<T> *root;
	Node<T> *_end;
	Node<T> *nil_node;
	int blacks;
	//int iterations;
	T array[100][100];
	int height;

public:
	Tree()
	{
		std::cout << "tree constructor" << std::endl;
		root = nullptr;
		nil_node = nullptr;
		// nil_node = new Node<T>(T());
		// nil_node->color = Node<T>::BLACK;
		blacks = 0;
	}
	~Tree() {}

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

	Node<T> *find(T key)
	{
		Node<T> *node = root;
		while (node != nullptr)
		{
			if (key == node->_data)
				return node;
			else if (key < node->_data)
				node = node->leftChild;
			else
				node = node->rightChild;
		}
		return nullptr;
	}

	/***************************************************
	**
	**	Insert
	**
	****************************************************/

	/*
	**	insert
	**	@brief first inserr
	*/
	Tree insert(T data)
	{
		Node<T> *node = new Node<T>(data);
		if (find(data) != nullptr)
		{
			std::cout << "/!\\ Cannot add twice the same value, " << data << " already present" << std::endl;
			return *this;
		}
		root = insert(root, node);
		recolorAndRotate(node);
		return *this;
	}

	Node<T> *insert(Node<T> *node, Node<T> *newNode)
	{
		if (root == nullptr)
		{
			newNode->setColor(Node<T>::BLACK);
			root = newNode;
			return newNode;
		}
		if (node == nullptr)
			return (newNode);
		if (newNode->_data < node->_data)
		{
			node->setLeftChild(insert(node->leftChild, newNode));
			node->leftChild->setParent(node);
		}
		if (newNode->_data >= node->_data)
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
		out("Func is :" << __func__ << " on node " << *node);
		Node<T> *parent = node->getParent();
		if (node != root && node->color == Node<T>::RED && parent->color == Node<T>::RED)
		{
			Node<T> *grandParent = node->parent->parent;
			Node<T> *uncle;
			if (grandParent == nullptr)
				uncle = nullptr;
			else
				uncle = parent->is_left_child() ? uncle = grandParent->rightChild : uncle = grandParent->leftChild;
			if (uncle != nullptr && uncle->getColor() == Node<T>::RED)
				handleRecoloring(parent, uncle, grandParent);
			else if (parent && parent->is_left_child())
				handle_lefts(node, parent, grandParent);
			else if (parent && !parent->is_left_child())
				handle_rights(node, parent, grandParent);
		}
		out("NODE COLOR IS " << node->color)
			root->setColor(Node<T>::BLACK);
	}

	/*
	** updateChildrenOfParentNode
	**	@brief tempNode now replaces node as the left or right child of node->parent
	**	@param node the old child node
	**	@param tempNode the new child of node->parent
	*/
	void updateChildrenOfParentNode(Node<T> *node, Node<T> *tempNode)
	{
		out("Func is :" << __func__ << " on node " << *node);

		if (node->parent == nullptr)
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
	void rotateLeft(Node<T> *node)
	{
		// Node<T> is x
		out("Func is :" << __func__ << " on node " << *node);
		Node<T> *rightNode = node->rightChild;
		// right node = y
		node->setRightChild(rightNode->leftChild);
		// new child of x is z
		if (node->rightChild != nullptr)
		{
			// new parent of z is x
			node->rightChild->setParent(node);
		}
		// new left child of y is x
		rightNode->setLeftChild(node);
		// new parent of y is ex parent of x (nullptr in this case)
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
	void rotateRight(Node<T> *node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		Node<T> *leftNode = node->leftChild;
		out("Left node " << leftNode->_data)
			node->setLeftChild(leftNode->rightChild);
		if (node->leftChild != nullptr)
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
	void handle_lefts(Node<T> *node, Node<T> *parent, Node<T> *grandParent)
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
		if (grandParent != nullptr)
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
	void handle_rights(Node<T> *node, Node<T> *parent, Node<T> *grandParent)
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
		if (grandParent != nullptr)
			grandParent->flipColor();
		rotateLeft(grandParent);
		if (node != root) // EST CE NORMAL ?
			recolorAndRotate(node->is_left_child() ? grandParent : parent);
	}

	void handleRecoloring(Node<T> *parent, Node<T> *uncle, Node<T> *grandParent)
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
	}

	int getMax(Node<T> *node)
	{
		if (node->rightChild != nullptr)
			return getMax(node->rightChild);
		return node->_data;
	}

	Node<T> *getMaxSuccessor(Node<T> *node)
	{
		if (node->rightChild != nullptr)
			return getMaxSuccessor(node->rightChild);
		return node;
	}

	int getMin(Node<T> *node)
	{
		if (node->leftChild != nullptr)
			return getMin(node->leftChild);
		return node->_data;
	}

	Node<T> *getSibling(Node<T> *node)
	{
		if (node->is_left_child() && node->parent->rightChild != nullptr)
			return node->parent->rightChild;
		else if (node->is_right_child() && node->parent->leftChild != nullptr)
			return node->parent->leftChild;
		return nullptr;
	}

	bool black_nephews(Node<T> *node)
	{
		if (!(getSibling(node)->leftChild == nullptr || getSibling(node)->leftChild->getColor() == Node<T>::BLACK))
			return false;
		if (!(getSibling(node)->rightChild == nullptr || getSibling(node)->rightChild->getColor() == Node<T>::BLACK)) // le neveu droit
			return false;
		std::cout << "WOWOW TRU" << std::endl;
		return true;
	}

	void handleBlackSiblingWithAtLeastOneRedChild(Node<T> *node, Node<T> *sibling)
	{
		bool nodeIsLeftChild = node->is_left_child();

		// Case 5: Black sibling with at least one red child + "outer nephew" is black
		// --> Recolor sibling and its child, and rotate around sibling
		if (nodeIsLeftChild && (sibling->rightChild == nullptr || sibling->rightChild->color == Node<T>::BLACK))
		{
			sibling->leftChild->color = Node<T>::BLACK;
			sibling->color = Node<T>::RED;
			rotateRight(sibling);
			sibling = getSibling(node);
			// sibling = node->parent->rightChild;
		}
		else if (!nodeIsLeftChild && (sibling->rightChild == nullptr || sibling->leftChild->color == Node<T>::BLACK))
		{
			sibling->rightChild->color = Node<T>::BLACK;
			sibling->color = Node<T>::RED;
			rotateLeft(sibling);
			sibling = getSibling(node);
			// sibling = node->parent->leftChild;
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

	void handleRedSibling(Node<T> *node, Node<T> *sibling)
	{
		// Recolor...
		sibling->setColor(Node<T>::BLACK);
		node->parent->color = Node<T>::RED;

		// ... and rotate
		if (node == node->parent->leftChild)
		{
			rotateLeft(node->parent);
		}
		else
		{
			rotateRight(node->parent);
		}
	}

	void fixRedBlackPropertiesAfterDelete(Node<T> *node)
	{
		out("Func is :" << __func__ << " on node " << *node);
		// Case 1: Examined node is root, end of recursion
		if (node == root || node == nullptr)
		{
			// Uncomment the following line if you want to enforce black roots (rule 2):
			// node.color = BLACK;
			return;
		}
		Node<T> *sibling = getSibling(node);
		out(*sibling) if (sibling == nullptr) return; // TEST
		// Case 2: Red sibling
		if (sibling->color == Node<T>::RED)
		{
			out("CASE 2 : red sibling " << *sibling);
			handleRedSibling(node, sibling);
			sibling = getSibling(node);
			out("NEW SIBLING " << *sibling)		// Get new sibling for fall-through to cases 3-6
				if (sibling == nullptr) return; // TEST
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

	Node<T> *deleteNodeWithZeroOrOneChild(Node<T> *node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		// Node<T> has ONLY a left child --> replace by its left child
		if (node->leftChild != nullptr)
		{
			updateChildrenOfParentNode(node, node->leftChild);
			out("UPDATED NODE *NODE" << *node << "AND PARENT " << *(node->parent))
				node->leftChild->setParent(node->parent);
			return node->leftChild; // moved-up node
		}
		// Node<T> has ONLY a right child --> replace by its right child
		else if (node->rightChild != nullptr)
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
			// Node<T> *newChild = nullptr;
			Node<T> *newChild = node->getColor() == Node<T>::BLACK ? nil_node : nullptr;

			// if (newChild != nullptr && newChild->_data == 404)
			//	newChild->setColor(Node<T>::NIL);
			updateChildrenOfParentNode(node, newChild);
			if (newChild != nullptr)
			{
				newChild->setParent(node->parent);
			}
			return newChild;
		}
	}

	void del(int data, Node<T> *root)
	{
		out("Func is :" << __func__ << " on node " << *root);

		Node<T> *node = find(data);
		if (node == nullptr || node == nil_node) // PAS SURE POUR LA DEUXIEME !!
			return;
		// At this point, "node" is the node to be deleted
		// In this variable, we'll store the node at which we're going to start to fix the R-B
		// properties after deleting a node->
		Node<T> *movedUpNode;
		int deletedNodeColor;

		// Node<T> has zero or one child
		if (node->leftChild == nullptr || node->rightChild == nullptr)
		{
			movedUpNode = deleteNodeWithZeroOrOneChild(node);
			deletedNodeColor = node->color;
		}
		// Node<T> has two children
		else
		{
			// Find minimum node of right subtree ("inorder successor" of current node)
			Node<T> *inOrderSuccessor = getMaxSuccessor(node->leftChild);
			// Copy inorder successor's data to current node (keep its color!)
			node->setData(inOrderSuccessor->_data);
			// Delete inorder successor just as we would delete a node with 0 or 1 child
			movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
			deletedNodeColor = inOrderSuccessor->getColor();
		}
		if (deletedNodeColor == Node<T>::BLACK)
		{
			// if (movedUpNode != nil_node) // ON VA VOR
			fixRedBlackPropertiesAfterDelete(movedUpNode);

			// Remove the temporary NIL node
			if (movedUpNode == nil_node)
			{
				updateChildrenOfParentNode(movedUpNode, nullptr);
				// replaceParentsChild(movedUpNode->parent, movedUpNode, nullptr);
			}
		}
	}

	void display_children(Node<T> *_curr);
	int validity_check(Node<T> *_curr);
	void display(Node<T> *_curr);
	void display_data(int a, ...);
	void calculate_height(Node<T> *node);
	int curr_black_height(T data);
	void see_tree();
	void light_display(Node<T> *root);
};
}
#endif

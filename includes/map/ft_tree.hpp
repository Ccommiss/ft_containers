
// class Node;
#include <iostream>
#include <iomanip>
#include <cstdarg>

#define out(x) std::cout << x << std::endl;

class Node
{
	friend class Tree;

public:
	Node(int data)
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

	int getData()
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
	int _data;
	Node *root;
	Node *leftChild;
	Node *rightChild;
	Node *parent;

	int color;
};

std::ostream &operator<<(std::ostream &os, Node &node)
{
	if (&node != nullptr)
	{
		std::string colors;
		node.getColor() == Node::BLACK ? colors = "⚫" : colors = "🔴";
		os << "Node " << node.getData() << " " << colors;
	}
	return os;
}

class Tree
{
	friend class Node;

private:
	Node *root;
	Node *_end;
	Node *nil_node;
	int blacks;
	int total;
	int iterations;
	int array[100][100];
	int height;
	// pour acceder aux elem

public:
	Tree()
	{
		std::cout << "tree constructor" << std::endl;
		root = nullptr;
		nil_node = new Node(40404);
		nil_node->color = Node::BLACK;
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

	Node *getRootPtr()
	{
		return root;
	}

	/**************************************************/
	/**	FIND 										  */
	/**************************************************/

	Node *find(int key)
	{
		Node *node = root;
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
	Tree insert(int data)
	{
		Node *node = new Node(data);
		if (find(data) != nullptr)
		{
			std::cout << "/!\\ Cannot add twice the same value, " << data << " already present" << std::endl;
			return *this;
		}
		root = insert(root, node);
		recolorAndRotate(node);
		return *this;
	}

	Node *insert(Node *node, Node *newNode)
	{
		if (root == nullptr)
		{
			newNode->setColor(Node::BLACK);
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
	void recolorAndRotate(Node *node)
	{
		out("Func is :" << __func__ << " on node " << *node);
		Node *parent = node->getParent();
		if (node != root && node->color == Node::RED && parent->color == Node::RED)
		{
			Node *grandParent = node->parent->parent;
			Node *uncle;
			if (grandParent == nullptr)
				uncle = nullptr;
			else
				uncle = parent->is_left_child() ? uncle = grandParent->rightChild : uncle = grandParent->leftChild;
			if (uncle != nullptr && uncle->getColor() == Node::RED)
				handleRecoloring(parent, uncle, grandParent);
			else if (parent && parent->is_left_child())
				handle_lefts(node, parent, grandParent);
			else if (parent && !parent->is_left_child())
				handle_rights(node, parent, grandParent);
		}
		out ("NODE COLOR IS " << node->color)
		root->setColor(Node::BLACK);
	}

	/*
	** updateChildrenOfParentNode
	**	@brief tempNode now replaces node as the left or right child of node->parent
	**	@param node the old child node
	**	@param tempNode the new child of node->parent
	*/
	void updateChildrenOfParentNode(Node *node, Node *tempNode)
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
	void rotateLeft(Node *node)
	{
		// Node is x
		out("Func is :" << __func__ << " on node " << *node);
		Node *rightNode = node->rightChild;
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
	void rotateRight(Node *node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		Node *leftNode = node->leftChild;
		out("Left node " << leftNode->_data)
			node->setLeftChild(leftNode->rightChild);
		if (node->leftChild != nullptr)
			node->leftChild->setParent(node);
		leftNode->setRightChild(node);
		leftNode->setParent(node->parent);
		updateChildrenOfParentNode(node, leftNode);
		node->setParent(leftNode);
		out("Node " << node->_data << " and new parent " << node->parent->_data);
	}

	/*
	**	Handle lefts
	**	@brief handles left-situation : left-heavy or left-right situations
	**	@param node,parent,grandParent nodes to be shifted
	*/
	void handle_lefts(Node *node, Node *parent, Node *grandParent)
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
	void handle_rights(Node *node, Node *parent, Node *grandParent)
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

	void handleRecoloring(Node *parent, Node *uncle, Node *grandParent)
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

	int getMax(Node *node)
	{
		if (node->rightChild != nullptr)
			return getMax(node->rightChild);
		return node->_data;
	}

	Node *getMaxSuccessor(Node *node)
	{
		if (node->rightChild != nullptr)
			return getMaxSuccessor(node->rightChild);
		return node;
	}

	int getMin(Node *node)
	{
		if (node->leftChild != nullptr)
			return getMin(node->leftChild);
		return node->_data;
	}

	Node *getSibling(Node *node)
	{
		if (node->is_left_child() && node->parent->rightChild != nullptr)
			return node->parent->rightChild;
		else if (node->is_right_child() && node->parent->leftChild != nullptr)
			return node->parent->leftChild;
		return nullptr;
	}

	bool black_nephews(Node *node)
	{
		if (!(getSibling(node)->leftChild == nullptr || getSibling(node)->leftChild->getColor() == Node::BLACK))
			return false;
		if (!(getSibling(node)->rightChild == nullptr || getSibling(node)->rightChild->getColor() == Node::BLACK)) // le neveu droit
			return false;
		std::cout << "WOWOW TRU" << std::endl;
		return true;
	}

	void handleBlackSiblingWithAtLeastOneRedChild(Node *node, Node *sibling)
	{
		bool nodeIsLeftChild = node->is_left_child();

		// Case 5: Black sibling with at least one red child + "outer nephew" is black
		// --> Recolor sibling and its child, and rotate around sibling
		if (nodeIsLeftChild && (sibling->rightChild == nullptr || sibling->rightChild->color == Node::BLACK))
		{
			sibling->leftChild->color = Node::BLACK;
			sibling->color = Node::RED;
			rotateRight(sibling);
			sibling = getSibling(node);
			// sibling = node->parent->rightChild;
		}
		else if (!nodeIsLeftChild && (sibling->rightChild == nullptr || sibling->leftChild->color == Node::BLACK))
		{
			sibling->rightChild->color = Node::BLACK;
			sibling->color = Node::RED;
			rotateLeft(sibling);
			sibling = getSibling(node);
			// sibling = node->parent->leftChild;
		}

		// Fall-through to case 6...
		// Case 6: Black sibling with at least one red child + "outer nephew" is red
		// --> Recolor sibling + parent + sibling's child, and rotate around parent
		sibling->color = node->parent->color;
		node->parent->color = Node::BLACK;
		if (nodeIsLeftChild)
		{
			sibling->rightChild->color = Node::BLACK;
			rotateLeft(node->parent);
		}
		else
		{
			sibling->leftChild->color = Node::BLACK;
			rotateRight(node->parent);
		}
	}

	void handleRedSibling(Node *node, Node *sibling)
	{
		// Recolor...
		sibling->setColor(Node::BLACK);
		node->parent->color = Node::RED;

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

	void fixRedBlackPropertiesAfterDelete(Node *node)
	{
		out("Func is :" << __func__ << " on node " << *node);
		// Case 1: Examined node is root, end of recursion
		if (node == root || node == nullptr)
		{
			// Uncomment the following line if you want to enforce black roots (rule 2):
			// node.color = BLACK;
			return;
		}
		Node *sibling = getSibling(node);
		out(*sibling) if (sibling == nullptr) return; // TEST
		// Case 2: Red sibling
		if (sibling->color == Node::RED)
		{
			out("CASE 2 : red sibling " << *sibling);
			handleRedSibling(node, sibling);
			sibling = getSibling(node);
			out("NEW SIBLING " << *sibling)		// Get new sibling for fall-through to cases 3-6
				if (sibling == nullptr) return; // TEST
		}
		// Cases 3+4: Black sibling with two black children
		if (sibling->color == Node::BLACK && black_nephews(node) == true)
		{
			sibling->color = Node::RED;
			out("ICI 3 + 4 ")
				// Case 3: Black sibling with two black children + red parent
				if (node->parent->color == Node::RED)
			{
				out("CASE 3   parent is " << *(node->parent));
				node->parent->color = Node::BLACK;
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

	Node *deleteNodeWithZeroOrOneChild(Node *node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		// Node has ONLY a left child --> replace by its left child
		if (node->leftChild != nullptr)
		{
			updateChildrenOfParentNode(node, node->leftChild);
			out("UPDATED NODE *NODE" << *node << "AND PARENT " << *(node->parent))
				node->leftChild->setParent(node->parent);
			return node->leftChild; // moved-up node
		}
		// Node has ONLY a right child --> replace by its right child
		else if (node->rightChild != nullptr)
		{
			updateChildrenOfParentNode(node, node->rightChild);
			node->rightChild->setParent(node->parent);
			return node->rightChild; // moved-up node
		}
		// Node has no children -->
		// * node is red --> just remove it
		// * node is black --> replace it by a temporary NIL node (needed to fix the R-B rules)
		else
		{
			// Node *newChild = nullptr;
			Node *newChild = node->getColor() == Node::BLACK ? nil_node : nullptr;

			// if (newChild != nullptr && newChild->_data == 404)
			//	newChild->setColor(Node::NIL);
			updateChildrenOfParentNode(node, newChild);
			if (newChild != nullptr)
			{
				newChild->setParent(node->parent);
			}
			return newChild;
		}
	}

	void del(int data, Node *root)
	{
		out("Func is :" << __func__ << " on node " << *root);

		Node *node = find(data);
		if (node == nullptr || node == nil_node) // PAS SURE POUR LA DEUXIEME !!
			return;
		// At this point, "node" is the node to be deleted
		// In this variable, we'll store the node at which we're going to start to fix the R-B
		// properties after deleting a node->
		Node *movedUpNode;
		int deletedNodeColor;

		// Node has zero or one child
		if (node->leftChild == nullptr || node->rightChild == nullptr)
		{
			movedUpNode = deleteNodeWithZeroOrOneChild(node);
			deletedNodeColor = node->color;
		}
		// Node has two children
		else
		{
			// Find minimum node of right subtree ("inorder successor" of current node)
			Node *inOrderSuccessor = getMaxSuccessor(node->leftChild);
			// Copy inorder successor's data to current node (keep its color!)
			node->setData(inOrderSuccessor->_data);
			// Delete inorder successor just as we would delete a node with 0 or 1 child
			movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
			deletedNodeColor = inOrderSuccessor->getColor();
		}
		if (deletedNodeColor == Node::BLACK)
		{
			//if (movedUpNode != nil_node) // ON VA VOR
				fixRedBlackPropertiesAfterDelete(movedUpNode);

			// Remove the temporary NIL node
			if (movedUpNode == nil_node)
			{
				updateChildrenOfParentNode(movedUpNode, nullptr);
				//replaceParentsChild(movedUpNode->parent, movedUpNode, nullptr);
			}
		}
	}

	/* ---------------------------------------------------------------------------- */
	/*							DEBUG FUNCS											*/
	/* ---------------------------------------------------------------------------- */
	void display_children(Node *_curr)
	{
		std::string colors;
		_curr->getColor() == Node::BLACK ? colors = "⚫" : colors = "🔴";
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

	int validity_check(Node *_curr)
	{
		static int i = 0;
		if (_curr == nullptr || _curr->getColor() == Node::BLACK)
			blacks++;
		if (_curr == nullptr)
		{
			if (iterations == 0)
				out("Number of blacks in most-left path :" << blacks);
			iterations++;
			return 0;
		}

		if (_curr->leftChild != nullptr && _curr->getColor() == Node::RED && _curr->leftChild->getColor() == Node::RED)
		{
			out("🔴 ERROR : " << _curr->_data << " is red and so is its left child " << _curr->leftChild->_data);
			return 1;
		}
		if (_curr->rightChild != nullptr && _curr->getColor() == Node::RED && _curr->rightChild->getColor() == Node::RED)
		{
			out("🔴 ERROR : " << _curr->_data << " is red and so is its righ child " << _curr->rightChild->_data);
			return 1;
		}
		validity_check(_curr->leftChild);
		validity_check(_curr->rightChild);
		return 0;
	}

	void display(Node *_curr)
	{
		if (_curr == nullptr)
			return;
		display_children(_curr);
		std::cout << "\n";
		display(_curr->leftChild);
		display(_curr->rightChild);
	}

	void display_data(int a, ...)
	{
		va_list args;
		va_start(args, a);
		std::string family[3] = {" > Node ", " > Parent ", " > GP "};
		for (int i = 0; i < 3; i++)
		{

			Node *_curr = va_arg(args, Node *);
			if (_curr != nullptr)
			{
				out(family[i] << _curr->_data << " has color " << _curr->getColor());
				// out("Node contains " << _curr->getColor());
			}
			else
			{
				out("Nullptr");
			}
		}
	}

	void calculate_height(Node *node)
	{
		if (node == nullptr)
			return;
		Node *tmp = node;
		int i = 0;
		while (tmp != root)
		{
			tmp = tmp->parent;
			i++;
		}
		int j = 0;
		while (j < 10 && array[i][j] != 0)
			j++;
		array[i][j] = node->_data;
		if (i > height)
			height = i; // on va prendre que les remplis
		if (node->leftChild != nullptr)
			calculate_height(node->leftChild);
		else
		{
			int j = 0;
			while (j < 10 && array[i + 1][j] != 0)
				j++;
			array[i + 1][j] = -1;
			array[i + 2][j * 2] = -1;
			array[i + 2][j * 2 + 1] = -1;
			calculate_height(node->leftChild);
		}
		if (node->rightChild != nullptr)
			calculate_height(node->rightChild);
		else
		{
			int j = 0;
			while (j < 10 && array[i + 1][j] != 0)
				j++;
			array[i + 1][j] = -1;
			array[i + 2][j * 2] = -1;
			array[i + 2][j * 2 + 1] = -1;
			calculate_height(node->rightChild);
		}
	}

	int		curr_black_height(int data)
	{
		Node *node = find(data);
		int i = 0;
		while (node != root)
		{
			if (node->color == Node::BLACK)
				i++;
			node = node->parent;
		}
		return i;
	}
	void see_tree()
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
					color = find(array[i][j])->color == Node::RED ? "🔴 " : "⚫️";
					if (j % 2 == 0)
						std::cout << std::setw(80 / (nb + 1) - i) << (array[i][j]) << color << "--|" << "(" << curr_black_height(array[i][j]) << ")";
					else
						std::cout << std::setw(80 / (nb + 1) - i) << "|--" << (array[i][j]) << color << "(" << curr_black_height(array[i][j]) << ")";
				}
				else if (array[i][j] == -1)
				{
					if (j % 2 == 0)
						std::cout << std::setw(80 / (nb + 1) - i + 2) << "N" << color << "--|";
					else
						std::cout << std::setw(80 / (nb + 1) - i + 2) << "|--" << "N" << color;
				}
				else if (array[i][j] == 0)
					std::cout << std::setw(80 / (nb + 1) - i) << " .  ";
			}
			nb *= 2;
			out("\n")
		}
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
				array[i][j] = 0;
		}
	}

	void
	light_display(Node *root)
	{
		if (root == nullptr)
			return;
		std::cout << root->_data << " ";
		if (root->leftChild != nullptr)
			light_display(root->leftChild);
		if (root->rightChild != nullptr)
			light_display(root->rightChild);
	}
};

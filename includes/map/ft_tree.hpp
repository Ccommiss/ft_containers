
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
	~Node() {};

	Node* getLeftChild()
	{
		return leftChild;
	}
	Node* getRightChild()
	{
		return rightChild;
	}
	Node* getParent()
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
		if (parent->getLeftChild() == nullptr)
			return false;
		if (this == (parent->getLeftChild()))
			return true;
		return false;
	}
	bool is_right_child()
	{
		if (parent == nullptr) // c root
			return false;
		if (this == (parent->getRightChild()))
			return true;
		return false;
	}

	int getData()
	{
		return (this->_data);
	}
	void setData(int data)
	{
		_data = data;
	}

	void setLeftChild(Node* node)
	{
		if (node != nullptr)
			out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
		this->leftChild = node;
	}
	void setRightChild(Node* node)
	{
		if (node != nullptr)
			out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
		this->rightChild = node;
	}
	void setParent(Node* parent)
	{
		if (parent != nullptr)
			out("Func is :" << __func__ << " on this " << _data << " with node " << parent->_data);;
		this->parent = parent;
	}

	enum colors
	{
		RED = 439,
		BLACK = 81435,
		NIL = 404
	};


private:
	int _data;
	Node* root;
	Node* leftChild;
	Node* rightChild;
	Node* parent;
	int color;
};

std::ostream& operator<<(std::ostream& os, Node& node)
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
	Node* root;
	Node* _end;
	int blacks;
	int total;
	int iterations;
	// pour acceder aux elem


public:
	Tree()
	{
		std::cout << "tree constructor" << std::endl;
		root = nullptr;
		_end = new Node(78);
		blacks = 0;
		total = 0;
		iterations = 0;
	}
	~Tree() {}

	/*
	** Functions;
	*/
	int getRoot()
	{
		return root->getData();
	}

	Node* getRootPtr()
	{
		return root;
	}

	Node* insert(Node* node, Node* newNode)
	{
		if (root == nullptr)
		{
			newNode->setColor(Node::BLACK);
			root = newNode;
			return newNode;
		}
		if (node == nullptr)
			return (newNode);
		if (newNode->getData() < node->getData())
		{
			node->setLeftChild(insert(node->getLeftChild(), newNode));
			node->getLeftChild()->setParent(node);
		}
		if (newNode->getData() >= node->getData())
		{
			node->setRightChild(insert(node->getRightChild(), newNode));
			node->getRightChild()->setParent(node);
		}
		return node;
	}

	Tree insert(int data)
	{
		Node* node = new Node(data);
		root = insert(root, node);
		recolorAndRotate(node);
		return *this;
	}

	void updateChildrenOfParentNode(Node* node, Node* tempNode)
	{
		out("Func is :" << __func__ << " on node " << *node);

		if (node->getParent() == nullptr)
		{
			root = tempNode;
		}
		else if (node->is_left_child())
		{
			node->getParent()->setLeftChild(tempNode);
		}
		else
		{
			node->getParent()->setRightChild(tempNode);
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
	void rotateLeft(Node* node)
	{
		// Node is x
		out("Func is :" << __func__ << " on node " << *node);
		Node* rightNode = node->getRightChild();
		// right node = y
		node->setRightChild(rightNode->getLeftChild());
		// new child of x is z
		if (node->getRightChild() != nullptr)
		{
			// new parent of z is x
			node->getRightChild()->setParent(node);
		}
		// new left child of y is x
		rightNode->setLeftChild(node);
		// new parent of y is ex parent of x (nullptr in this case)
		rightNode->setParent(node->getParent());
		updateChildrenOfParentNode(node, rightNode);
		// new parent of x is y
		node->setParent(rightNode);

		// output changes
		out(*node << " parent is " << *node->getParent());
		out(*node << " right child " << *node->getRightChild());
		out(*rightNode << " parent is " << *rightNode->getParent());
		out(*rightNode << " left child is " << *rightNode->getLeftChild());
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
	void rotateRight(Node* node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		Node* leftNode = node->getLeftChild();
		out("Left node " << leftNode->getData())
			node->setLeftChild(leftNode->getRightChild());
		if (node->getLeftChild() != nullptr)
		{
			node->getLeftChild()->setParent(node);
		}
		leftNode->setRightChild(node);
		leftNode->setParent(node->getParent());
		updateChildrenOfParentNode(node, leftNode);
		node->setParent(leftNode);
		out("Node " << node->getData() << " and new parent " << node->getParent()->getData());
	}

	void handle_lefts(Node* node, Node* parent, Node* grandParent)
	{
		out("Func is :" << __func__ << " on node " << *node);
		display_data(3, node, parent, grandParent);
		int LR = 0;
		if (node->is_right_child())
		{
			out("Left-right situation found");
			rotateLeft(parent);
			display(root);
			LR = 1;
		}
		// HERE IS LEFT HEAVY SITUATION
		out("Left-left situation found");

		// if (parent != nullptr)
		// parent->flipColor();
		if (LR == 1)
			node->flipColor(); // PK LE PARENT DANS LE CODE SOURCE ?
		else
			parent->flipColor();
		if (grandParent != nullptr)
			grandParent->flipColor();

		/// OULALA GROS TEST ;
		// explication, on fait ca pour que ca redevienne un left left normal v
		// if (node->getParent() != nullptr)
		// 	node->getParent()
		// 		->flipColor();
		// if (node->getParent()->getParent() != nullptr)
		// 	node->getParent()->getParent()->flipColor();
		// display(root);
		rotateRight(grandParent);
		if (node != root) // EST CE NORMAL ?
			recolorAndRotate(node->is_left_child() ? parent : grandParent);
	}

	void handle_rights(Node* node, Node* parent, Node* grandParent)
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
		// display(root);
		rotateLeft(grandParent);
		display(root);
		if (node != root) // EST CE NORMAL ?
			recolorAndRotate(node->is_left_child() ? grandParent : parent);
	}

	void handleRecoloring(Node* parent, Node* uncle, Node* grandParent)
	{
		uncle->flipColor();
		parent->flipColor();
		grandParent->flipColor();
		recolorAndRotate(grandParent);
	}

	void recolorAndRotate(Node* node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		Node* parent = node->getParent();

		// ajout de la condition Node::RED de moi et pas forcement bonne
		if (node != root && node->getColor() == Node::RED && parent->getColor() == Node::RED)
		{
			Node* grandParent = node->getParent()->getParent();
			// out("GP is :" << grandParent->getData());
			Node* uncle;
			if (grandParent == nullptr)
				uncle = nullptr;
			else
			{
				uncle = parent->is_left_child() ? uncle = grandParent->getRightChild() : uncle = grandParent->getLeftChild();
			}
			if (uncle != nullptr && uncle->getColor() == Node::RED)
			{
				out("Recoloring");
				handleRecoloring(parent, uncle, grandParent);
			}
			else if (parent && parent->is_left_child())
			{
				out("handle left");
				handle_lefts(node, parent, grandParent);
			}
			else if (parent && !parent->is_left_child())
			{
				out("handle right");
				handle_rights(node, parent, grandParent);
			}
		}
		root->setColor(Node::BLACK);
	}

	void del(int data)
	{
		Node* deleted;
		del(data, root);

		//recolor ??? 

	}

	// C le del de l'AVL !!

	int getMax(Node* node)
	{
		if (node->getRightChild() != nullptr)
		{
			return getMax(node->getRightChild());
		}
		return node->getData();
	}

	Node* getMaxSuccessor(Node* node)
	{
		if (node->getRightChild() != nullptr)
		{
			return getMaxSuccessor(node->getRightChild());
		}
		return node;
	}

	int getMin(Node* node)
	{
		if (node->getLeftChild() != nullptr)
		{
			return getMin(node->getLeftChild());
		}
		return node->getData();
	}


	bool	is_leaf(Node* node)
	{
		if (node == nullptr)
			return false;
		if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
			return true;
		else
			return false;
	}


	Node* getSibling(Node* node)
	{
		if (node->is_left_child() && node->getParent()->getRightChild() != nullptr)
			return node->getParent()->getRightChild();
		else if (node->is_right_child() && node->getParent()->getLeftChild() != nullptr)
			return node->getParent()->getLeftChild();
		return nullptr;
	}

	bool    black_nephews(Node* node)
	{
		bool are_black = false;

		if (getSibling(node)->getLeftChild() == nullptr || getSibling(node)->getLeftChild()->getColor() == Node::BLACK)
			are_black = true; // le neveu gauche
		out("ARE BLACK " << are_black);
		if (getSibling(node)->getRightChild() == nullptr || getSibling(node)->getRightChild()->getColor() == Node::BLACK) // le neveu droit
			are_black = true;
		else
			are_black = false;
		out("ARE BLACK " << are_black);
		return are_black;
	}

	Node::colors successor_color(Node* node)
	{
		if (node->getRightChild() != nullptr)
		{
			return successor_color(node->getRightChild());
		}
		out("node data ==" << *node);
		if (node == nullptr || node->getColor() == Node::BLACK)
			return Node::BLACK;
		out("SUCCESSOR COLOR IS RED ")
			return Node::RED;
	}

	void	check_case(Node* node)
	{
		bool double_black = false;
		out("Checking case for :" << *node)
			//Case one
			if (node->getLeftChild() == nullptr && node->getRightChild() != nullptr)
			{
				out("CASE ONE CHILD (right)")
			}
		if (node->getRightChild() == nullptr && node->getLeftChild() != nullptr)
		{
			out("CASE ONE CHILD (Left)")
		}
		if (node->getColor() == Node::RED)//&& is_leaf(node) == true)
			out("CASE ONE FOUND : RED LEAF NO PROBLEM")
			//case two
		else if (node == root)
			out("CASE TWO FOUND : ROOT ")
		else if (node->getColor() == Node::BLACK && (successor_color(node->getLeftChild()) == Node::BLACK) && black_nephews(node) == true)
		{
			out("CASE 3 Double black, black nephews");
			double_black = 1;
			while (double_black == 1 && node != root)
			{
				//	getSibling(node)->flipColor();
				node->getParent()->flipColor();
				node = node->getParent();
			}
		}
	}





	void handleBlackSiblingWithAtLeastOneRedChild(Node *node, Node *sibling)
	{
		bool nodeIsLeftChild = node->is_left_child(); 

		// Case 5: Black sibling with at least one red child + "outer nephew" is black
		// --> Recolor sibling and its child, and rotate around sibling
		if (nodeIsLeftChild && sibling->rightChild->color == Node::BLACK) 
		{
			sibling->leftChild->color = Node::BLACK;
			sibling->color = Node::RED;
			rotateRight(sibling);
			sibling = node->parent->rightChild;
		}
		else if (!nodeIsLeftChild && sibling->leftChild->color == Node::BLACK)
		{
			sibling->rightChild->color = Node::BLACK;
			sibling->color = Node::RED;
			rotateLeft(sibling);
			sibling = node->parent->leftChild;
		}

		// Fall-through to case 6...

		// Case 6: Black sibling with at least one red child + "outer nephew" is red
		// --> Recolor sibling + parent + sibling's child, and rotate around parent
		sibling->color = node->parent->color;
		node->parent->color = Node::BLACK;
		if (nodeIsLeftChild) {
			sibling->rightChild->color = Node::BLACK;
			rotateLeft(node->parent);
		}
		else {
			sibling->leftChild->color = Node::BLACK;
			rotateRight(node->parent);
		}
	}


	void handleRedSibling(Node* node, Node* sibling)
	{
		// Recolor...
		sibling->setColor(Node::BLACK);
		node->parent->color = Node::RED;

		// ... and rotate
		if (node == node->parent->leftChild) {
			rotateLeft(node->parent);
		}
		else {
			rotateRight(node->parent);
		}
	}


	void fixRedBlackPropertiesAfterDelete(Node* node) 
	{
		out("Func is :" << __func__ << " on node " << *node);
		// Case 1: Examined node is root, end of recursion
		if (node == root) {
			// Uncomment the following line if you want to enforce black roots (rule 2):
			// node.color = BLACK;
			return;
		}

		Node* sibling = getSibling(node);

		// Case 2: Red sibling
		if (sibling->color == Node::RED) {
			handleRedSibling(node, sibling);
			sibling = getSibling(node); // Get new sibling for fall-through to cases 3-6
		}

		// Cases 3+4: Black sibling with two black children
		if (sibling->color == Node::BLACK && black_nephews(node))
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
			else {
				out ("CASE 4");
				fixRedBlackPropertiesAfterDelete(node->parent);
			}
		}

		// Case 5+6: Black sibling with at least one red child
		else {
			out ("CASE 5 + 6 ");
			handleBlackSiblingWithAtLeastOneRedChild(node, sibling);
		}
	}

	Node* deleteNodeWithZeroOrOneChild(Node* node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		// Node has ONLY a left child --> replace by its left child
		if (node->getLeftChild() != nullptr)
		{
			if (node->is_left_child())
				node->getParent()->setLeftChild(node->getLeftChild());
			else if (node->is_right_child())
				node->getParent()->setRightChild(node->getLeftChild());
			node->getLeftChild()->setParent(node->getParent());
			return node->getLeftChild(); // moved-up node
		}

		// Node has ONLY a right child --> replace by its right child
		else if (node->getRightChild() != nullptr)
		{
			if (node->is_left_child())
				node->getParent()->setLeftChild(node->getRightChild());
			else if (node->is_right_child())
				node->getParent()->setRightChild(node->getRightChild());

			node->getRightChild()->setParent(node->getParent());
			return node->getRightChild(); // moved-up node
		}
		// Node has no children -->
		// * node is red --> just remove it
		// * node is black --> replace it by a temporary NIL node (needed to fix the R-B rules)
		else {
			Node* newChild = node->getColor() == Node::BLACK ? new Node(404) : nullptr;
			if (newChild != nullptr && newChild->_data== 404)
				newChild->setColor(Node::NIL);

			//replaceParentsChild(node.parent, node, newChild);
			if (node->getParent() == nullptr) {
				root = newChild;
			}
			else if (node->getParent()->getLeftChild() == node) {
				node->getParent()->setLeftChild(newChild);
			}
			else if (node->getParent()->getRightChild() == node) {
				node->getParent()->setRightChild(newChild);
				return newChild;
			}

			if (newChild != nullptr) {
				newChild->setParent(node->getParent());
			}
			return newChild;
		}
	}

	void del(int data, Node* node)
	{
		out("Func is :" << __func__ << " on node " << *node);
		while (node != nullptr && node->getData() != data) {
			// Traverse the tree to the left or right depending on the data
			if (data < node->getData()) {
				node = node->getLeftChild();
			}
			else {
				node = node->getRightChild();
			}
		}
		// Node not found?
		if (node == nullptr) {
			return ;
		}

		// At this point, "node" is the node to be deleted

		// In this variable, we'll store the node at which we're going to start to fix the R-B
		// properties after deleting a node->
		Node* movedUpNode;
		int deletedNodeColor;

		// Node has zero or one child
		if (node->getLeftChild() == nullptr || node->getRightChild() == nullptr) {
			movedUpNode = deleteNodeWithZeroOrOneChild(node);
			deletedNodeColor = node->color;
		}

		// Node has two children
		else {
			// Find minimum node of right subtree ("inorder successor" of current node)
			Node* inOrderSuccessor = getMaxSuccessor(node->getLeftChild());

			// Copy inorder successor's data to current node (keep its color!)
			node->setData(inOrderSuccessor->getData());

			// Delete inorder successor just as we would delete a node with 0 or 1 child
			movedUpNode = deleteNodeWithZeroOrOneChild(inOrderSuccessor);
			deletedNodeColor = inOrderSuccessor->getColor();
		}

		if (deletedNodeColor == Node::BLACK) {
			fixRedBlackPropertiesAfterDelete(movedUpNode);

			// Remove the temporary NIL node
			//if (movedUpnode == nullptr) {
			//	replaceParentsChild(movedUpnode->parent, movedUpNode, nullptr);
			//}
		}
	}


	/* ---------------------------------------------------------------------------- */
	/*							DEBUG FUNCS											*/
	/* ---------------------------------------------------------------------------- */
	void display_children(Node* _curr)
	{
		std::string colors;
		_curr->getColor() == Node::BLACK ? colors = "⚫" : colors = "🔴";
		std::cout << "---------------------------"
			<< "\n";
		std::cout << "|";
		std::cout << std::setw(10) << " NODE " << _curr->getData() << " (" << colors << ")"
			<< "	  |\n";
		std::cout << "---------------------------"
			<< "\n";
		std::cout << "|";
		if (_curr->getLeftChild() != nullptr)
		{
			std::cout << std::setw(10) << _curr->getLeftChild()->getData() << "  ";
		}
		else
			std::cout << std::setw(10) << "(null)"
			<< "  ";
		std::cout << "|";

		if (_curr->getRightChild() != nullptr)
		{
			std::cout << std::setw(10) << _curr->getRightChild()->getData() << "  ";
		}
		else
			std::cout << std::setw(10) << "(null)"
			<< "  ";
		std::cout << "|";
	}

	int validity_check(Node* _curr)
	{
		static int i = 0;
		// out("ITER " << iterations);
		if (_curr == nullptr || _curr->getColor() == Node::BLACK)
		{
			blacks++;
		}
		if (_curr == nullptr)
		{
			if (iterations == 0)
				out("Number of blacks in path :" << blacks);
			iterations++;
			//	out("iter" << iterations);
			// blacks = 0;
			return 0;
		}

		if (_curr->getLeftChild() != nullptr && _curr->getColor() == Node::RED && _curr->getLeftChild()->getColor() == Node::RED)
		{
			out("🔴 ERROR : " << _curr->getData() << " is red and so is its left child " << _curr->getLeftChild()->getData());
			return 1;
		}
		if (_curr->getRightChild() != nullptr && _curr->getColor() == Node::RED && _curr->getRightChild()->getColor() == Node::RED)
		{
			out("🔴 ERROR : " << _curr->getData() << " is red and so is its righ child " << _curr->getRightChild()->getData());
			return 1;
		}
		// out("checking curr " << _curr->getData())
		validity_check(_curr->getLeftChild());
		// blacks -= 1;
		// out("checking curr " << _curr->getData())
		validity_check(_curr->getRightChild());

		// blacks -= 2;
		return 0;
	}
	void display(Node* _curr)
	{
		if (_curr == nullptr)
			return;
		display_children(_curr);
		std::cout << "\n";
		display(_curr->getLeftChild());
		display(_curr->getRightChild());
	}

	void display_data(int a, ...)
	{
		va_list args;
		va_start(args, a);
		std::string family[3] = { " > Node ", " > Parent ", " > GP " };
		for (int i = 0; i < 3; i++)
		{

			Node* _curr = va_arg(args, Node*);
			if (_curr != nullptr)
			{
				out(family[i] << _curr->getData() << " has color " << _curr->getColor());
				// out("Node contains " << _curr->getColor());
			}
			else
			{
				out("Nullptr");
			}
		}
	}

	// void del(int data);
};

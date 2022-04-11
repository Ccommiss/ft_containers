
// class Node;
#include <iostream>
#include <iomanip>
#include <cstdarg>

#define out(x) std::cout << x << std::endl;

class Node
{

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

	void setLeftChild(Node *node)
	{
		if (node != nullptr)
			out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
		this->leftChild = node;
	}
	void setRightChild(Node *node)
	{
		if (node != nullptr)
		out("Func is :" << __func__ << " on this " << _data << " with node " << node->_data);
		this->rightChild = node;
	}
	void setParent(Node *parent)
	{
		if (parent != nullptr)
			out("Func is :" << __func__ << " on this " << _data << " with node " << parent->_data);;
		this->parent = parent;
	}

	enum colors
	{
		RED = 439,
		BLACK = 81435
	};

	std::ostream &operator<<(std::ostream &os)
	{
		std::cout << "YO" << std::endl;
		os << "Node here " << getData();
		return os;
	}

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
		os << "Node here " << node.getData();
	return os;
}

class Tree
{

	friend class Node; // pour acceder aux elem
private:
	Node *root;
	Node *_end;
	int blacks;
	int total;
	int iterations;

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

	Node *getRootPtr()
	{
		return root;
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
		Node *node = new Node(data);
		root = insert(root, node);
		out("Basic insert ");
		display(root);
		recolorAndRotate(node);
		return *this;
	}

	void updateChildrenOfParentNode(Node *node, Node *tempNode)
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
	void rotateLeft(Node *node)
	{
		// Node is x
		out("Func is :" << __func__ << " on node " << *node);
		Node *rightNode = node->getRightChild();
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
		out(*rightNode << " parent is " << *rightNode ->getParent());
		out(*rightNode << " left child is " << *rightNode ->getLeftChild());
		out ("root is " << *root )
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

		Node *leftNode = node->getLeftChild();
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

	void handle_lefts(Node *node, Node *parent, Node *grandParent)
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
		// display(root);
		rotateLeft(grandParent);
		display(root);
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

	void recolorAndRotate(Node *node)
	{
		out("Func is :" << __func__ << " on node " << *node);

		Node *parent = node->getParent();

		// ajout de la condition Node::RED de moi et pas forcement bonne
		if (node != root && node->getColor() == Node::RED && parent->getColor() == Node::RED)
		{
			Node *grandParent = node->getParent()->getParent();
			// out("GP is :" << grandParent->getData());
			Node *uncle;
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
		del(data, root);

	}

	// C le del de l'AVL !!

	int getMax(Node *node)
	{
		if (node->getRightChild() != nullptr)
		{
			return getMax(node->getRightChild());
		}
		return node->getData();
	}
	int getMin(Node *node)
	{
		if (node->getLeftChild() != nullptr)
		{
			return getMin(node->getLeftChild());
		}
		return node->getData();
	}


	bool	is_leaf(Node *node)
	{
		if (node == nullptr)
			return false;
		if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)
			return true;
		else
			return false;
	}


	Node *get_sibling(Node *node)
	{
		if (node->is_left_child() && node->getParent()->getRightChild() != nullptr)
			return node->getParent()->getRightChild();
		else if (node->is_right_child() && node->getParent()->getLeftChild() != nullptr)
			return node->getParent()->getLeftChild();
		return nullptr;
	}

	bool    black_nephews(Node *node)
	{
		bool are_black = false;

		if (get_sibling(node)->getLeftChild() == nullptr || get_sibling(node)->getLeftChild()->getColor() == Node::BLACK)
			are_black = true; // le neveu gauche
		out("ARE BLACK " << are_black);
		if (get_sibling(node)->getRightChild() == nullptr || get_sibling(node)->getRightChild()->getColor() == Node::BLACK) // le neveu droit
			are_black = true;
		else
			are_black = false;
		out("ARE BLACK " << are_black);
		return are_black;
	}

	Node::colors successor_color(Node *node)
	{
		if (node->getRightChild() != nullptr)
		{
			return successor_color(node->getRightChild());
		}
		if (node == nullptr || node->getColor() == Node::BLACK)
			return Node::BLACK;
		out ("SUCCESSOR COLOR IS RED ")
		return Node::RED;
	}

	void	check_case(Node *node)
	{
		bool double_black = false;
		out("Checking case for :" << *node)
		//Case one
		if (node->getColor() == Node::RED)//&& is_leaf(node) == true)
			out ("CASE ONE FOUND : RED LEAF")
		//case two
		else if (node == root)
			out ("CASE TWO FOUND : ROOT ")
		else if (node->getColor() == Node::BLACK && (successor_color(node) == Node::BLACK) && black_nephews(node) == true)
		{
			out("CASE 3 Double black, black nephews");
			double_black = 1;
			while (double_black == 1 && node != root)
			{
				get_sibling(node)->flipColor();
				node->getParent()->flipColor();
				node = node->getParent();
			}
		}
	}

	Node *del(int data, Node *node)
	{
		out("Func is :" << __func__ << " on node " << *node);
		static bool double_black = false;
		if (node == nullptr)
		{
			return nullptr;
		}
		std::cout << *node << std::endl;
		// static int _case = 0;
		// static Node *sibling;
		// if (node != root)
		// 	sibling = node->getParent()->getRightChild();
		// if (node != root && sibling != nullptr &&  node->getParent()->getRightChild()->getColor() == Node::RED)
		// {
		// 	out("YOUPI")
		// 	_case = 2;
		// }

		if (data < node->getData())
		{
			node->setLeftChild(del(data, node->getLeftChild()));
		}
		else if (data > node->getData())
		{
			node->setRightChild(del(data, node->getRightChild()));
		}
		else //on arrive sur le"vrai" truc a supp (avant on a juste copié)
		{
			// One Child or Leaf Node (no children)
			check_case(node);
			if (node->getLeftChild() == nullptr)
			{
				return node->getRightChild();
			}
			else if (node->getRightChild() == nullptr)
			{
				return node->getLeftChild();
			}
			// Two Children
			if (node->getColor() == Node::BLACK && node->getLeftChild()->getColor() == Node::BLACK)
				double_black = true;

			out ("Set data " << *node << " by " << getMax(node->getLeftChild()))
			node->setData(getMax(node->getLeftChild()));
			node->setLeftChild(del(node->getData(), node->getLeftChild()));
		}
		out(" Node to be returned = " << *node);
		return (node);
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

	int validity_check(Node *_curr)
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
	void display(Node *_curr)
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
		std::string family[3] = {" > Node ", " > Parent ", " > GP "};
		for (int i = 0; i < 3; i++)
		{

			Node *_curr = va_arg(args, Node *);
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

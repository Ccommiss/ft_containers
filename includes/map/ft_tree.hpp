
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

	void setLeftChild(Node *node)
	{
		this->leftChild = node;
	}
	void setRightChild(Node *node)
	{
		this->rightChild = node;
	}
	void setParent(Node *parent)
	{
		this->parent = parent;
	}

	enum colors
	{
		RED = 439,
		BLACK = 81435
	};

private:
	int _data;
	Node *root;
	Node *leftChild;
	Node *rightChild;
	Node *parent;
	int color;
};

class Tree
{

	friend class Node; // pour acceder aux elem
private:
	Node *root;
	Node *_end;

public:
	Tree()
	{
		std::cout << "tree constructor" << std::endl;
		root = nullptr;
		_end = new Node(78);
		//	insert(root, 0);
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
			std::cout << "set root" << std::endl;
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
		out("before");
		display(root);
		recolorAndRotate(node);
		out("after");
		display(root);
		return *this;
	}

	void updateChildrenOfParentNode(Node *node, Node *tempNode)
	{
		out("Func is :" << __func__);

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

	void rotateLeft(Node *node)
	{
		out("Func is :" << __func__);
		Node *rightNode = node->getRightChild();
		node->setRightChild(rightNode->getLeftChild());
		if (node->getRightChild() != nullptr)
		{
			node->getRightChild()->setParent(node);
		}
		rightNode->setLeftChild(node);
		rightNode->setParent(node->getParent());
		updateChildrenOfParentNode(node, rightNode);
		node->setParent(rightNode);
	}

	void rotateRight(Node *node)
	{
		out("Func is :" << __func__);

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
		display(root);

		out("Node " << node->getData() << " and new parent " << node->getParent()->getData());
	}

	void handle_lefts(Node *node, Node *parent, Node *grandParent)
	{
		out("Func is :" << __func__);
		display_data(node, parent, grandParent);
		if (node->is_right_child())
		{
			out("Left-right situation found")
				rotateLeft(parent);
			out("DISPLAY NIOW")
				display(root);
		}
		// HERE IS LEFT HEAVY SITUATION
		out("Left-left situation found")
		/// OULALA GROS TEST ;
		// explication, on fait ca pour que ca redevienne un left left normal v
		if (node->getParent() != nullptr)
			node->getParent()->flipColor();
		if (node->getParent()->getParent() != nullptr)
			node->getParent()->getParent()->flipColor();
		display(root);
		rotateRight(grandParent);
		if (node != root) // EST CE NORMAL ?
			recolorAndRotate(node->is_left_child() ? node->getParent() : node->getParent()->getParent());
	}

	void handle_rights(Node *node, Node *parent, Node *grandParent)
	{
		out("Func is :" << __func__);

		if (node->is_left_child())
		{
			out("Right-left situation found")
				rotateRight(parent);
		}
		// if (parent != nullptr)
		// 	parent->flipColor();
		// if (grandParent != nullptr)
		// 	grandParent->flipColor();
		// rotateLeft(grandParent);
		// if (node != root) // EST CE NORMAL ?
		// 	recolorAndRotate(node->is_left_child() ? grandParent : parent);

			if (node->getParent() != nullptr)
			node->getParent()->flipColor();
		if (node->getParent()->getParent() != nullptr)
			node->getParent()->getParent()->flipColor();
		display(root);
		rotateLeft(grandParent);
		if (node != root) // EST CE NORMAL ?
			recolorAndRotate(node->is_left_child() ? node->getParent()->getParent() : node->getParent());
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
		out("Func is :" << __func__)
			out("Node is :" << node->getData())
				Node *parent = node->getParent();
		if (node != root && parent->getColor() == Node::RED)
		{
			Node *grandParent = node->getParent()->getParent();
			//out("GP is :" << grandParent->getData());
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
	void display(Node *_curr)
	{
		if (_curr == nullptr)
			return;
		display_children(_curr);
		std::cout << "\n";
		display(_curr->getLeftChild());
		display(_curr->getRightChild());
	}

	void display_data(Node *a, ...)
	{
		va_list args;
    	va_start(args, a);
		for (int i = 0; i < 3; i++)
		{
			Node *_curr = va_arg(args, Node *);
			if (_curr != nullptr)
			{
				out("Node contains " << _curr->getData() << "has color " << _curr->getColor());
				//out("Node contains " << _curr->getColor());
			}
			else
			{
				out("Nullptr");
			}
		}
	}

	// void delete(int data);
};

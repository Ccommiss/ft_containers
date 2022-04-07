
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

		color == RED? color = BLACK : color = RED;
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
		out("Basic insert ");
		display(root);
		recolorAndRotate(node);
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
		out("Node " << node->getData() << " and new parent " << node->getParent()->getData());
	}

	void handle_lefts(Node *node, Node *parent, Node *grandParent)
	{
		out("Func is :" << __func__);
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

		//if (parent != nullptr)
		//parent->flipColor();
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
		out("Func is :" << __func__ << "with node " << node->getData());
		display_data(3, node, parent, grandParent);
		int RL = 0;
		if (node->is_left_child())
		{
			out("Right-left situation found")
			rotateRight(parent);
			RL = 1;
		}
		out("Right-right situation found");

		//if (parent != nullptr)
		//parent->flipColor();
		if (RL == 1)
			node->flipColor();
		else
			parent->flipColor();
		if (grandParent != nullptr)
			grandParent->flipColor();
		//rotateLeft(grandParent);
		// if (node != root) // EST CE NORMAL ?
		// 	recolorAndRotate(node->is_left_child() ? grandParent : parent);

		// if (node->getParent() != nullptr)
		// 	node->getParent()->flipColor();
		// if (node->getParent()->getParent() != nullptr)
		// 	node->getParent()->getParent()->flipColor();


		// display(root);
		rotateLeft(grandParent);
		display(root);
		if (node != root) // EST CE NORMAL ?
			recolorAndRotate(node->is_left_child() ? grandParent: parent);
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
		out("Func is :" << __func__);
		out("Node is :" << node->getData());
		Node *parent = node->getParent();

		//ajout de la condition Node::RED de moi et pas forcement bonne
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
		root = del(data, root);
	}

	// C le del de l'AVL !!
	Node *del(int data, Node *node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (data < node->getData())
		{
			node->setLeftChild(del(data, node->getLeftChild()));
		}
		else if (data > node->getData())
		{
			node->setRightChild(del(data, node->getRightChild()));
		}
		else
		{
			// One Child or Leaf Node (no children)
			if (node->getLeftChild() == nullptr)
			{
				return node->getRightChild();
			}
			else if (node->getRightChild() == nullptr)
			{
				return node->getLeftChild();
			}
			// Two Children
			// node.setData(getMax(node.getLeftChild()));
			// node.setLeftChild(del (node.getData(), node.getLeftChild()));
			node->setData(node->getLeftChild()->getData());
			node->setLeftChild(del(node->getData(), node->getLeftChild()));
		}
		return (node);
		// updateHeight(node);
		// return applyRotation(node);
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
		if (_curr == nullptr){
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
		validity_check(_curr->getLeftChild());
		validity_check(_curr->getRightChild());
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

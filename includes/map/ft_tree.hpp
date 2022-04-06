
//class Node; 
#include <iostream>
#include  <iomanip>


class Node {

	public:
	Node(int data)
	{
		std::cout << "Creating new Node value : " << data << std::endl;
		root = nullptr;
		leftChild = nullptr;
		rightChild = nullptr;
		parent = nullptr;
		_data = data;
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


	/*
** If addresses are the same, then this is a left child
*/
	bool is_left_child()
	{
		if (this == (parent->getLeftChild()))
			return true;
		return false;
	}
	bool is_right_child()
	{
		if (this == (parent->getRightChild()))
			return true;
		return false;
	}

	int		getData()
	{
		return (this->_data);
	}

	void 		setLeftChild(Node* node)
	{
		this->leftChild = node;
	}
	void 		setRightChild(Node* node)
	{
		this->rightChild = node;
	}
	void 		setParent(Node* parent)
	{
		this->parent = parent;
	}

	private:
	int		_data;
	Node* root;

	Node* leftChild;
	Node* rightChild;
	Node* parent;

	enum colors {
		RED,
		BLACK
	};
	int 	color;
};

class Tree {

	friend class Node; // pour acceder aux elem 
	private:
	Node* root;
	Node* _end;

	public:

	Tree() {
		std::cout << "tree constructor" << std::endl;
		root = nullptr;
		_end = new Node(78);
		//	insert(root, 0);
	}
	// Tree(int data) {
	// 	root = nullptr;
	// 	insert(data);
	// }

	~Tree() {}
	/*
	** Functions;
	*/
	int		getRoot()
	{
		return root->getData();
	}

	Node*		getRootPtr()
	{
		return root;
	}

	Node* insert(Node* node, Node* newNode)
	{
		if (root == nullptr) {
			root = newNode;
			std::cout << "set root" << std::endl;
			return newNode;
		}
		if (node == nullptr)
			return (newNode);
		if (newNode->getData() < node->getData())
		{
			std::cout << "insert left " << std::endl;
			node->setLeftChild(insert(node->getLeftChild(), newNode));
			node->getLeftChild()->setParent(node);
		}
		if (newNode->getData() >= node->getData())
		{
			std::cout << "insert right " << std::endl;
			node->setRightChild(insert(node->getRightChild(), newNode));
			node->getRightChild()->setParent(node);
		}
		return node;
	}

	Tree insert(int data)
	{
		Node* node = new Node(data);
		root = insert(root, node);
		//  recolorAndRotate(node);
		return *this;
	}



	void display_children(Node* _curr)
	{
		std::cout << "---------------------------" << "\n";
		std::cout << "|";
		std::cout <<std::setw(15) << " NODE " << _curr->getData() << "	  |\n";
		std::cout << "---------------------------" << "\n";
		std::cout << "|";
		if (_curr->getLeftChild() != nullptr)
		{
			std::cout << std::setw(10) << _curr->getLeftChild()->getData() << "  ";
		}
		else
			std::cout << std::setw(10) << "(null)" << "  ";
				std::cout << "|";

		if (_curr->getRightChild() != nullptr)
		{
			std::cout << std::setw(10) << _curr->getRightChild()->getData() << "  ";
		}
		else
			std::cout << std::setw(10) <<  "(null)" << "  ";
		std::cout << "|";
	}
	void display(Node* _curr)
	{
		if (_curr == nullptr)
			return ;

		display_children(_curr);
		std::cout << "\n";	
		display(_curr->getLeftChild());
		display(_curr->getRightChild());

	}
	
	//void delete(int data);
};

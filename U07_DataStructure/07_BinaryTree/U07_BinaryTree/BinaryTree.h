#pragma once

template<typename T>
class BinaryTree
{
public:
	struct Node;

public:
	BinaryTree() {};

	~BinaryTree()
	{
		Destroy(root);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->Left = node->Right = nullptr;

		return node;
	}

	void DestroyNode(Node* node)
	{
		delete node;
		node = nullptr;
	}

	void Root(Node* node) { root = node; }

private:
	void Destroy(Node* node)
	{
		if (node == nullptr) return;

		Destroy(node->Left);
		Destroy(node->Right);

		DestroyNode(node);
	}

public:
	void PreOrder(Node* node) //rLR
	{
		if (node == nullptr) return;

		cout << node->Data << ", "; //r
		PreOrder(node->Left); //L
		PreOrder(node->Right); //R
	}

	void InOrder(Node* node) //LrR
	{
		if (node == nullptr) return;

		InOrder(node->Left); //L
		cout << node->Data << ", "; //r
		InOrder(node->Right); //R
	}

	void PostOrder(Node* node) //LRr
	{
		if (node == nullptr) return;

		PostOrder(node->Left); //L
		PostOrder(node->Right); //R
		cout << node->Data << ", "; //r
	}


private:
	struct Node
	{
		T Data;
		Node* Left;
		Node* Right;
	};

private:
	Node* root;

};
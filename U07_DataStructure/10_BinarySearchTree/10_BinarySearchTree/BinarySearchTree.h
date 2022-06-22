#pragma once

template<typename T>
class BinarySearchTree
{
public:
	struct Node;

public:
	BinarySearchTree() {}

	~BinarySearchTree()
	{
		Destroy(root);
	}

	void Insert(Node** parent, Node* child)
	{
		if ((*parent)->Data < child->Data)
		{
			if ((*parent)->Right == nullptr)
				(*parent)->Right = child;
			else
				Insert(&(*parent)->Right, child);
		}
		else if ((*parent)->Data > child->Data)
		{
			if ((*parent)->Left == nullptr)
				(*parent)->Left = child;
			else
				Insert(&(*parent)->Left, child);
		}
	}

public:
	void Root(Node* node) { root = node; }

private:
	void Destroy(Node* node)
	{
		if (node == nullptr) return;

		Destory(node->Left);
		Destory(node->Right);
		DestroyNode(node);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->Left = node->Right = nullptr;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		delete node;
		node = nullptr;
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
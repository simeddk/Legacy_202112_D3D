#pragma once

#include <iostream>
using namespace std;

template<typename T>
class Tree
{
public:
	struct Node;

	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;

		node->Child = node->Sibling = nullptr;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		delete node;
		node = nullptr;
	}

	void AddChild(Node* parent, Node* child)
	{
		if (parent->Child == nullptr)
			parent->Child = child;
		else
		{
			Node* node = parent->Child;

			while (node->Sibling != nullptr)
				node = node->Sibling;

			node->Sibling = child;
		}
	}

	void Print(Node* node, int depth)
	{
		for (int i = 0; i < depth; i++)
			cout << "¤¤";

		cout << node->Data << endl;

		if (node->Child != nullptr)
			Print(node->Child, depth + 1);

		if (node->Sibling != nullptr)
			Print(node->Sibling, depth);
	}


private:
	struct Node
	{
		T Data;

		Node* Child;
		Node* Sibling;
	};
};
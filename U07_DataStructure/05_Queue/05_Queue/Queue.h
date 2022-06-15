#pragma once

template<typename T>
class Queue
{
public:
	struct Node;

public:
	~Queue()
	{

	}

	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->Next = nullptr;

		return node;
	}

private:
	struct Node
	{
		T Data;
		Node* Next;
	};

private:
	Node* front = nullptr;
	Node* rear = nullptr;
	int size = 0;
};
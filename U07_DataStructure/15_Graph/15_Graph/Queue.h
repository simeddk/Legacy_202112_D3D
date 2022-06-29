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

	static void DestoryNode(Node* node)
	{
		delete node;
		node = nullptr;
	}

	void Enqueue(Node* node)
	{
		if (front == nullptr)
		{
			front = node;
			rear = node;
			size++;

			return;
		}

		rear->Next = node;
		rear = node;
		size++;
	}

	Node* Dequeue()
	{
		Node* node = front;

		if (front->Next == nullptr)
			front = rear = nullptr;
		else
			front = front->Next;

		return node;
	}

	bool IsEmpty() { return front == nullptr; }
	int Size() { return size; }

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
#pragma once

template<typename T>
class PQueue
{
public:
	struct Node;

public:
	PQueue(int capacity = 10)
		: capacity(capacity)
		, size(0)
	{
		nodes = new Node[this->capacity];
	}

	~PQueue()
	{
		delete[] nodes;
		nodes = nullptr;
	}

	int Parent(int index)
	{
		return (int)((index - 1) / 2);
	}

	int LeftChild(int index)
	{
		return index * 2 + 1;
	}

	void SwapNode(int index1, int index2)
	{
		Node temp;
		temp = nodes[index1];
		nodes[index1] = nodes[index2];
		nodes[index2] = temp;
	}

	void Enqueue(Node data)
	{
		int curr = size;
		int  parent = Parent(curr);

		if (size == capacity)
		{
			Node* temp = new Node[capacity * 2];
			memcpy(temp, nodes, sizeof(Node) * capacity);

			delete[] nodes;
			nodes = temp;

			capacity *= 2;
		}

		nodes[curr] = data;

		while (curr > 0 && nodes[curr].Priority < nodes[parent].Priority)
		{
			SwapNode(curr, parent);

			curr = parent;
			parent = Parent(curr);
		}

		size++;
	}

	Node Dequeue()
	{
		int parent = 0;
		int left = 0;
		int right = 0;

		Node result = nodes[0];

		size--;
		SwapNode(0, size);

		left = LeftChild(0);
		right = left + 1;

		while (true)
		{
			int selected = 0;

			if (left >= size)
				break;

			if (right >= size)
				selected = left;
			else
			{
				if (nodes[left].Priority > nodes[right].Priority)
					selected = right;
				else
					selected = left;
			}

			if (nodes[selected].Priority < nodes[parent].Priority)
			{
				SwapNode(parent, selected);

				parent = selected;
			}
			else
				break;

			left = LeftChild(parent);
			right = left + 1;
		}

		return result;
	}

	void Print()
	{
		for (int i = 0; i < size; i++)
			printf("%d ", nodes[i].Data);

		printf("\n");
	}

private:
	struct Node
	{
		T Data;
		int Priority;

		Node()
		{

		}

		Node(int priority, T data)
			: Priority(priority)
			, Data(data)
		{

		}
	};

public:
	int Size() { return size; }
	Node* Nodes() { return nodes; }

private:
	Node* nodes;

	int capacity;
	int size;
};
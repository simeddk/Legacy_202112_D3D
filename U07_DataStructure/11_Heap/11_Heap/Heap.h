#pragma once

template<typename T>
class Heap
{
public:
	struct Node;

public:
	Heap(int capacity)
		: capacity(capacity)
		, size(0)
	{
		nodes = new Node[this->capacity];
	}

	~Heap()
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
		Node* temp = new Node();

		memcpy(temp, &nodes[index1], sizeof(Node));
		memcpy(&nodes[index1], &nodes[index2], sizeof(Node));
		memcpy(&nodes[index2], temp, sizeof(Node));
		
		delete temp;
	}

	void Insert(Node data)
	{
		int curr = size;
		int  parent = Parent(curr);
		
		if (size == capacity)
		{
			Node* temp = new Node[capacity * 2];
			memcpy(temp, nodes, sizeof(Node) * size);

			delete[] nodes;
			nodes = temp;

			capacity *= 2;
		}

		nodes[curr] = data;

		while (curr > 0 && nodes[curr].Data < nodes[parent].Data)
		{
			SwapNode(curr, parent);

			curr = parent;
			parent = Parent(curr);
		}

		size++;
	}

	Node RemoveMin()
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
				if (nodes[left].Data > nodes[right].Data)
					selected = right;
				else
					selected = left;
			}

			if (nodes[selected].Data < nodes[parent].Data)
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

		Node()
		{

		}

		Node(T data)
			: Data(data)
		{

		}
	};

	int Size() { return size; }

private:
	Node* nodes;

	int capacity;
	int size;
};
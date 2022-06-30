#pragma once

#include "PQueue.h"

template<typename T>
class Graph
{
public:
	struct Edge;
	struct Node;

public:
	Graph() = default;
	~Graph() = default;

	void AddNode(Node* node)
	{
		Node* nodeList = nodes;
		if (nodeList != nullptr)
		{
			while (nodeList->Next != nullptr)
				nodeList = nodeList->Next;

			nodeList->Next = node;
		}
		else
			nodes = node;

		node->Index = count++;
	}

	void AddEdge(Node* node, Edge* edge)
	{
		if (node->Edge != nullptr)
		{
			Edge* edgeList = node->Edge;

			while (edgeList->Next != nullptr)
				edgeList = edgeList->Next;

			edgeList->Next = edge;
		}
		else
			node->Edge = edge;
	}

public:
	void Prim(Node* startNode, Graph<T>* graph)
	{
		PQueue<Node*> queue(10);
		PQueue<Node*> startQNode = PQueue<Node*>::Node(0, startNode);

		Node* currNode = nullptr;
		Edge* currEdge = nullptr;

		int* weights = new int[count];
		Node** mstNodes = new Node*[count];
		Node** visited = new Node*[count];
		Node** precedences = new Node*[count];

		int i = 0;
		currNode = nodes;
		while (currNode != nullptr)
		{
			//TODO. 위에 있는 배열 4개를 ZeroMemory..는 내일

			currNode = currNode->Next;
			i++;
		}
	}


public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		return node;
	}

	static void DestroyNode(Node* node)
	{
		while (node->Edge != nullptr)
		{
			Edge* edge = node->Edge->Next;
			DestroyEdge(node->Edge);
			node->Edge = edge;
		}
	}

	void DestroyEdge(Edge* edge)
	{
		delete edge;
		edge = nullptr;
	}

	static Edge* CreateEdge(Node* start, Node* target, float weight = 0.0f)
	{
		Edge* edge = new Edge();
		edge->Start = start;
		edge->Target = target;
		edge->Next = nullptr;
		edge->Weight = weight;

		return edge;
	}

private:
	struct Edge
	{
		float Weight = 0.0f;
		Node* Start = nullptr;
		Node* Target = nullptr;
		Edge* Next = nullptr;
	};

	struct Node
	{
		T Data;
		bool Visited = false;
		int Index = -1;

		Node* Next = nullptr;
		Edge* Edge = nullptr;
	};

public:
	std::list<Node*> GetList() { return linkedList; }

private:
	Node* nodes = nullptr;
	int count = 0;


};
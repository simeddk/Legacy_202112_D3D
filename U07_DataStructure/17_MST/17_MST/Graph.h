#pragma once

#include "PQueue.h"
#include "DisjointSet.h"

#define MAX_GRAPH_WEIGHT 1e+6f

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

	void Print()
	{
		Node* node = nullptr;
		Edge* edge = nullptr;

		if ((node = nodes) == nullptr)
			return;

		while (node != nullptr)
		{
			printf("from %c -> ", node->Data);

			if ((edge = node->Edge) == nullptr)
			{
				node = node->Next;
				printf("\n");

				continue;
			}

			while (edge != nullptr)
			{
				printf("to %c (%3d), ", edge->Target->Data, (int)edge->Weight);
				edge = edge->Next;
			}

			printf("\n");

			node = node->Next;
		}

		printf("\n");
	}

public:
	void Prim(Node* startNode, Graph<T>* graph)
	{
		PQueue<Node*> queue(10);
		PQueue<Node*>::Node startQNode = PQueue<Node*>::Node(0, startNode);

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
			Graph<T>::Node* newNode = CreateNode(currNode->Data);
			graph->AddNode(newNode);

			visited[i] = nullptr;
			precedences[i] = nullptr;
			mstNodes[i] = newNode;
			weights[i] = MAX_GRAPH_WEIGHT;

			currNode = currNode->Next;
			i++;
		}

		queue.Enqueue(startQNode);
		weights[startNode->Index] = 0;

		while (queue.IsEmpty() == false)
		{
			PQueue<Node*>::Node poped = queue.Dequeue();

			currNode = poped.Data;
			visited[currNode->Index] = currNode;

			currEdge = currNode->Edge;
			while (currEdge != nullptr)
			{
				Node* targetNode = currEdge->Target;

				if (visited[targetNode->Index] == nullptr &&
					currEdge->Weight < weights[targetNode->Index])
				{
					PQueue<Node*>::Node newNode = PQueue<Node*>::Node((int)currEdge->Weight, targetNode);
					queue.Enqueue(newNode);

					precedences[targetNode->Index] = currEdge->Start;
					weights[targetNode->Index] = currEdge->Weight;
				}

				currEdge = currEdge->Next;
			}
		}

		for (int i = 0; i < count; i++)
		{
			int start, target;

			if (precedences[i] == nullptr)
				continue;

			start = precedences[i]->Index;
			target = i;

			graph->AddEdge(mstNodes[start], Graph<T>::CreateEdge(mstNodes[start], mstNodes[target], weights[i]));
			graph->AddEdge(mstNodes[target], Graph<T>::CreateEdge(mstNodes[target], mstNodes[start], weights[i]));

			printf("%c -> %c, %3d\n", mstNodes[start]->Data, mstNodes[target]->Data, weights[i]);
		}
		printf("\n");

		delete[] visited;
		delete[] precedences;
		delete[] mstNodes;
		delete[] weights;

	}
	void Kruskal(Graph<T>* graph)
	{
		Node** mstNodes = new Node*[count];
		DisjointSet<Node*>::Set** sets = new DisjointSet<Node*>::Set*[count];

		PQueue<Edge*> queue;

		int i = 0;
		Node* currNode = nodes;
		Edge* currEdge = nullptr;

		while (currNode != nullptr)
		{
			sets[i] = DisjointSet<Node*>::CreateSet(currNode);
			mstNodes[i] = CreateNode(currNode->Data);
			graph->AddNode(mstNodes[i]);

			currEdge = currNode->Edge;
			while (currEdge != nullptr)
			{
				PQueue<Edge*>::Node newNode = PQueue<Edge*>::Node(currEdge->Weight, currEdge);
				queue.Enqueue(newNode);

				currEdge = currEdge->Next;
			}

			currNode = currNode->Next;
			i++;
		}

		while (queue.IsEmpty() == false)
		{
			PQueue<Edge*>::Node poped = queue.Dequeue();
			currEdge = poped.Data;

			int start = currEdge->Start->Index;
			int target = currEdge->Target->Index;

			if (DisjointSet<Node*>::IsSameGroup(sets[start], sets[target]) == false)
			{
				graph->AddEdge(mstNodes[start], Graph<char>::CreateEdge(mstNodes[start], mstNodes[target], currEdge->Weight));
				graph->AddEdge(mstNodes[target], Graph<char>::CreateEdge(mstNodes[target], mstNodes[start], currEdge->Weight));

				DisjointSet<Node*>::UinionSet(sets[start], sets[target]);
			}
		}

		delete[] sets;
		delete[] mstNodes;
	}
	void Dijkstra(Node* startNode, Graph<T>* graph)
	{
		PQueue<Node*> queue(10);
		PQueue<Node*>::Node startQNode = PQueue<Node*>::Node(0, startNode);

		int* weights = new int[count];
		Node** ways = new Node * [count];
		Node** visited = new Node * [count];
		Node** precedences = new Node * [count];

		Node* currNode = nodes;
		Edge* currEdge = nullptr;

		for (int i = 0; currNode != nullptr; i++)
		{
			Node* newNode = CreateNode(currNode->Data);
			graph->AddNode(newNode);

			weights[i] = MAX_GRAPH_WEIGHT;
			ways[i] = newNode;
			visited[i] = nullptr;
			precedences[i] = nullptr;

			currNode = currNode->Next;
		}

		queue.Enqueue(startQNode);
		weights[startNode->Index] = 0;

		while (queue.IsEmpty() == false)
		{
			PQueue<Node*>::Node poped = queue.Dequeue();

			currNode = poped.Data;
			visited[currNode->Index] = currNode;

			currEdge = currNode->Edge;
			while (currEdge != nullptr)
			{
				Node* targetNode = currEdge->Target;

				bool b = true;
				b &= visited[targetNode->Index] == nullptr;
				b &= weights[currNode->Index] + currEdge->Weight < weights[targetNode->Index];

				if (b == true)
				{
					PQueue<Node*>::Node newNode = PQueue<Node*>::Node((int)currEdge->Weight, targetNode);
					queue.Enqueue(newNode);

					precedences[targetNode->Index] = currEdge->Start;
					weights[targetNode->Index] = weights[currNode->Index] + currEdge->Weight;
				}

				currEdge = currEdge->Next;
			}
		}

		for (int i = 0; i < count; i++)
		{
			int start, target;

			if (precedences[i] == nullptr)
				continue;

			start = precedences[i]->Index;
			target = i;

			graph->AddEdge(ways[start], Graph<T>::CreateEdge(ways[start], ways[target], weights[i]));

			printf("%c -> %c, %3d\n", ways[start]->Data, ways[target]->Data, weights[i]);
		}
		printf("\n");

		delete[] visited;
		delete[] precedences;
		delete[] ways;
		delete[] weights;
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


private:
	Node* nodes = nullptr;
	int count = 0;


};
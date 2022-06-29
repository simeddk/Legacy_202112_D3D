#include <stdio.h>
#include <Windows.h>

#include "Graph.h"

int main()
{
	Graph<char> graph;
	Graph<char>::Node* A = Graph<char>::CreateNode('A');
	Graph<char>::Node* B = Graph<char>::CreateNode('B');
	Graph<char>::Node* C = Graph<char>::CreateNode('C');
	Graph<char>::Node* D = Graph<char>::CreateNode('D');
	Graph<char>::Node* E = Graph<char>::CreateNode('E');

	graph.AddNode(A);
	graph.AddNode(B);
	graph.AddNode(C);
	graph.AddNode(D);
	graph.AddNode(E);

	graph.AddEdge(A, Graph<char>::CreateEdge(A, B));
	graph.AddEdge(A, Graph<char>::CreateEdge(A, C));
	graph.AddEdge(A, Graph<char>::CreateEdge(A, D));
	graph.AddEdge(A, Graph<char>::CreateEdge(A, E));

	graph.AddEdge(B, Graph<char>::CreateEdge(B, A));
	graph.AddEdge(B, Graph<char>::CreateEdge(B, C));
	graph.AddEdge(B, Graph<char>::CreateEdge(B, E));

	graph.AddEdge(C, Graph<char>::CreateEdge(C, A));
	graph.AddEdge(C, Graph<char>::CreateEdge(C, B));

	graph.AddEdge(D, Graph<char>::CreateEdge(D, A));
	graph.AddEdge(D, Graph<char>::CreateEdge(D, E));

	graph.AddEdge(E, Graph<char>::CreateEdge(E, A));
	graph.AddEdge(E, Graph<char>::CreateEdge(E, B));
	graph.AddEdge(E, Graph<char>::CreateEdge(E, D));

	graph.Print();

	graph.DFS(A);
	printf("\n");

	A->Visited = B->Visited = C->Visited = D->Visited = E->Visited = false;
	graph.BFS(A);
	printf("\n");

	system("pause");
	return 0;
}
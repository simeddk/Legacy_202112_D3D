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
	Graph<char>::Node* F = Graph<char>::CreateNode('F');
	Graph<char>::Node* G = Graph<char>::CreateNode('G');
	Graph<char>::Node* H = Graph<char>::CreateNode('H');

	graph.AddNode(A);
	graph.AddNode(B);
	graph.AddNode(C);
	graph.AddNode(D);
	graph.AddNode(E);
	graph.AddNode(F);
	graph.AddNode(G);
	graph.AddNode(H);

	graph.AddEdge(A, Graph<char>::CreateEdge(A, C));
	graph.AddEdge(A, Graph<char>::CreateEdge(A, D));

	graph.AddEdge(B, Graph<char>::CreateEdge(B, C));
	graph.AddEdge(B, Graph<char>::CreateEdge(B, E));

	graph.AddEdge(C, Graph<char>::CreateEdge(C, F));

	graph.AddEdge(D, Graph<char>::CreateEdge(D, F));
	graph.AddEdge(D, Graph<char>::CreateEdge(D, G));

	graph.AddEdge(E, Graph<char>::CreateEdge(E, G));

	graph.AddEdge(F, Graph<char>::CreateEdge(F, H));

	graph.AddEdge(G, Graph<char>::CreateEdge(G, H));

	graph.TopologySort(A);
	printf("\n");

	auto list = graph.GetList();
	
	while (list.empty() == false)
	{
		Graph<char>::Node* node = list.front();
		
		auto it = list.begin();
		printf("%c ", (*it)->Data);

		list.pop_front();
	}
	printf("\n");

	system("pause");
	return 0;
}
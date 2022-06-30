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
	Graph<char>::Node* I = Graph<char>::CreateNode('I');
	
	graph.AddNode(A);
	graph.AddNode(B);
	graph.AddNode(C);
	graph.AddNode(D);
	graph.AddNode(E);
	graph.AddNode(F);
	graph.AddNode(G);
	graph.AddNode(H);
	graph.AddNode(I);

	graph.AddEdge(A, Graph<char>::CreateEdge(A, B, 35));
	graph.AddEdge(A, Graph<char>::CreateEdge(A, E, 247));

	graph.AddEdge(B, Graph<char>::CreateEdge(B, A, 35));
	graph.AddEdge(B, Graph<char>::CreateEdge(B, C, 126));
	graph.AddEdge(B, Graph<char>::CreateEdge(B, F, 150));

	graph.AddEdge(C, Graph<char>::CreateEdge(C, B, 126));
	graph.AddEdge(C, Graph<char>::CreateEdge(C, D, 117));
	graph.AddEdge(C, Graph<char>::CreateEdge(C, F, 162));
	graph.AddEdge(C, Graph<char>::CreateEdge(C, G, 220));

	graph.AddEdge(D, Graph<char>::CreateEdge(D, C, 117));

	graph.AddEdge(E, Graph<char>::CreateEdge(E, A, 247));
	graph.AddEdge(E, Graph<char>::CreateEdge(E, F, 82));
	graph.AddEdge(E, Graph<char>::CreateEdge(E, H, 98));

	graph.AddEdge(F, Graph<char>::CreateEdge(F, B, 150));
	graph.AddEdge(F, Graph<char>::CreateEdge(F, C, 162));
	graph.AddEdge(F, Graph<char>::CreateEdge(F, E, 82));
	graph.AddEdge(F, Graph<char>::CreateEdge(F, G, 154));
	graph.AddEdge(F, Graph<char>::CreateEdge(F, H, 120));

	graph.AddEdge(G, Graph<char>::CreateEdge(G, C, 220));
	graph.AddEdge(G, Graph<char>::CreateEdge(G, F, 154));
	graph.AddEdge(G, Graph<char>::CreateEdge(G, I, 106));

	graph.AddEdge(H, Graph<char>::CreateEdge(H, E, 98));
	graph.AddEdge(H, Graph<char>::CreateEdge(H, F, 120));

	graph.AddEdge(I, Graph<char>::CreateEdge(I, G, 106));

	system("pause");
	return 0;
}
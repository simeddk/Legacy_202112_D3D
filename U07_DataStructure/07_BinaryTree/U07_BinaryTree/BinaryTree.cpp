#include <iostream>
#include <Windows.h>
using namespace std;

#include "BinaryTree.h"

int main()
{
	BinaryTree<char> tree;
	BinaryTree<char>::Node* A = tree.CreateNode('A');
	BinaryTree<char>::Node* B = tree.CreateNode('B');
	BinaryTree<char>::Node* C = tree.CreateNode('C');
	BinaryTree<char>::Node* D = tree.CreateNode('D');
	BinaryTree<char>::Node* E = tree.CreateNode('E');
	BinaryTree<char>::Node* F = tree.CreateNode('F');
	BinaryTree<char>::Node* G = tree.CreateNode('G');

	tree.Root(A);

	A->Left = B;

	B->Left = C;
	B->Right = D;

	A->Right = E;
	E->Left = F;
	E->Right = G;

	cout << "PreOrder : ";
	tree.PreOrder(A);
	cout << endl << endl;

	cout << "InOrder : ";
	tree.InOrder(A);
	cout << endl << endl;

	cout << "PostOrder : ";
	tree.PostOrder(A);
	cout << endl << endl;

	system("pause");
	return 0;
}
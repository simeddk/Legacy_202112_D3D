#include <stdio.h>
#include <string>
#include <Windows.h>
using namespace std;

#include "RBTree.h"

int main()
{
	RBTree<int> tree;
	RBTree<int>::Node* root = nullptr;

	tree.Insert(&root, RBTree<int>::CreateNode(1));
	tree.Insert(&root, RBTree<int>::CreateNode(2));
	tree.Insert(&root, RBTree<int>::CreateNode(3));
	tree.Insert(&root, RBTree<int>::CreateNode(4));
	tree.Insert(&root, RBTree<int>::CreateNode(5));
	tree.Insert(&root, RBTree<int>::CreateNode(6));
	tree.Insert(&root, RBTree<int>::CreateNode(7));
	tree.Insert(&root, RBTree<int>::CreateNode(8));
	tree.Insert(&root, RBTree<int>::CreateNode(9));
	tree.Print(root, 0);


	/*printf("\n\n");
	RBTree<int>::Node* node = tree.Search(root, 8);
	tree.RotateRight(&root, node);
	tree.Print(root, 0);

	printf("\n\n");
	node = tree.Search(root, 5);
	tree.RotateLeft(&root, node);
	tree.Print(root, 0);*/

	system("pause");
	return 0;
}
#include <stdio.h>
#include <Windows.h>

#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> tree;
	BinarySearchTree<int>::Node* root = BinarySearchTree<int>::CreateNode(123);
	
	tree.Root(root);
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(22));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(999));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(424));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(17));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(3));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(98));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(34));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(759));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(320));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(1));

	tree.InOrder(root, 0);
	printf("\n");

	int depth = 0;
	BinarySearchTree<int>::Node* node = tree.Search(root, 98, depth);
	printf("%d번만에 찾음 -> 찾은 값 : %d\n", depth, node->Data);

	node = tree.Remove(root, nullptr, 22);
	BinarySearchTree<int>::DestroyNode(node);
	tree.InOrder(root, 0);
	printf("\n");

	printf("-----------------\n");
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(19));
	tree.Insert(&root, BinarySearchTree<int>::CreateNode(18));

	node = tree.Remove(root, nullptr, 17);
	BinarySearchTree<int>::DestroyNode(node);

	node = tree.Remove(root, nullptr, 999);
	BinarySearchTree<int>::DestroyNode(node);

	tree.InOrder(root, 0);
	printf("\n");

	system("pause");
	return 0;
}
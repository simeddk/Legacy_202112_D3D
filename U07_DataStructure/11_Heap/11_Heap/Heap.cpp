#include <stdio.h>
#include <Windows.h>

#include "Heap.h"

int main()
{
	Heap<int> heap(3);
	heap.Insert(12);
	heap.Insert(87);
	heap.Insert(111);
	heap.Insert(34);
	heap.Insert(16);
	heap.Insert(75);
	heap.Print();

	printf("Pop : %d\n", heap.RemoveMin().Data); //-> 12
	heap.Print();

	printf("Pop : %d\n", heap.RemoveMin().Data); //-> 16
	heap.Print();

	printf("Pop : %d\n", heap.RemoveMin().Data); //-> 34
	heap.Print();

	printf("Pop : %d\n", heap.RemoveMin().Data); //-> 75
	heap.Print();

	printf("Pop : %d\n", heap.RemoveMin().Data); //-> 87
	heap.Print();

	printf("Pop : %d\n", heap.RemoveMin().Data); //-> 111
	heap.Print();

	system("pause");
	return 0;
}
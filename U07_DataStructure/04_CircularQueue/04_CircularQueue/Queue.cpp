#include <stdio.h>
#include <Windows.h>
#include "Queue.h"

int main()
{
	Queue<int> queue(10);
	queue.Enqueue(1);
	queue.Enqueue(2);
	queue.Enqueue(3);
	queue.Enqueue(4);

	printf("%d/%d\n", queue.Size(), queue.Capacity());
	printf("Front : %d, Rear : %d\n", queue.Front(), queue.Rear());

	printf("-------------------\n");
	for (int i = 0; i < 3; i++)
	{
		printf("poped : %d, ", queue.Dequeue());
		printf("front : %d, rear : %d\n", queue.Front(), queue.Rear());
	}
	printf("%d/%d\n", queue.Size(), queue.Capacity());

	printf("\n\n-----------------\n");
	queue.Enqueue(91);
	queue.Enqueue(92);
	queue.Enqueue(93);
	queue.Enqueue(94);
	queue.Enqueue(95);
	printf("front : %d, rear : %d\n", queue.Front(), queue.Rear());

	printf("\n\n-----------------\n");
	int count = 100;

	while (queue.IsFull() == false)
		queue.Enqueue(count++);

	printf("front : %d, rear : %d\n", queue.Front(), queue.Rear());

	while (queue.IsEmpty() == false)
	{
		printf("poped : %d, ", queue.Dequeue());
		printf("front : %d, rear : %d\n", queue.Front(), queue.Rear());
	}

	system("pause");
	return 0;
}
#include <stdio.h>
#include <Windows.h>
#include "Queue.h"

int main()
{
	Queue<int> queue;
	queue.Enqueue(Queue<int>::CreateNode(10));
	queue.Enqueue(Queue<int>::CreateNode(1));
	queue.Enqueue(Queue<int>::CreateNode(20));
	queue.Enqueue(Queue<int>::CreateNode(30));
	queue.Enqueue(Queue<int>::CreateNode(40));
	queue.Enqueue(Queue<int>::CreateNode(50));
	queue.Enqueue(Queue<int>::CreateNode(60));

	printf("Size : %d\n", queue.Size());

	while (queue.IsEmpty() == false)
	{
		Queue<int>::Node* poped = queue.Dequeue();
		printf("poped : %d\n", poped->Data);

		Queue<int>::DestoryNode(poped);
	}

	system("pause");
	return 0;
}
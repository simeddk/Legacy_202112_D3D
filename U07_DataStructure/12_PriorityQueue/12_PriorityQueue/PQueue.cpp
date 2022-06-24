#include <stdio.h>
#include <Windows.h>
#include <string>
using namespace std;

#include "PQueue.h"

void Print(PQueue<string>::Node* nodes, int size)
{
	for (int i = 0; i < size; i++)
	printf("우선순위(%d) : %s\n", nodes[i].Priority, nodes[i].Data.c_str());
}

int main()
{
	PQueue<string> queue(16);
	queue.Enqueue(PQueue<string>::Node(66, "롤 한판 하기"));
	queue.Enqueue(PQueue<string>::Node(34, "포트폴리오 완성하기"));
	queue.Enqueue(PQueue<string>::Node(12, "알고리즘 문제풀기"));
	queue.Enqueue(PQueue<string>::Node(45, "방 청소하기"));
	queue.Enqueue(PQueue<string>::Node(35, "컴공 지식 공부하기"));
	queue.Enqueue(PQueue<string>::Node(87, "잠자기"));
	Print(queue.Nodes(), queue.Size());

	PQueue<string>::Node node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	system("pause");
	return 0;
}
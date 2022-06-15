#include <stdio.h>
#include <Windows.h>
#include <vector>
using namespace std;

typedef int DataType;

struct Node
{
	DataType Data;
	
	Node* Next;
	Node* Prev;
};

Node* CreateNode(DataType data)
{
	Node* node = new Node();
	node->Data = data;
	node->Next = nullptr;
	node->Prev = nullptr;

	return node;
}

void DestroyNode(Node* node)
{
	delete node;
	node = nullptr;
}


void Push(Node** head, Node* node)
{	
	if (*head == nullptr)
	{
		*head = new Node();
		(*head)->Data = node->Data;
	}
	else
	{
		Node* tail = *head;

		while (tail->Next != nullptr)
			tail = tail->Next;

		tail->Next = node;
		node->Prev = tail;
	}
}

Node* GetNode(Node* head, int location)
{
	Node* current = head;

	while (current != nullptr && (--location) >= 0)
		current = current->Next;

	return current;
}

void Insert(Node* current, Node* newNode)
{
	newNode->Next = current->Next;
	newNode->Prev = current;

	if (current->Next != nullptr)
		current->Next->Prev = newNode;

	current->Next = newNode;


}

void InsertHead(Node** list, Node* newHead)
{
	if (*list == nullptr)
		*list = newHead;
	else
	{
		newHead->Next = *list;
		(*list)->Prev = newHead;
		*list = newHead;
	}
}

void Remove(Node** list, Node* remove)
{
	if (*list == remove)
	{
		*list = remove->Next;

		if (*list != nullptr)
			(*list)->Prev = nullptr;

		remove->Prev = nullptr;
		remove->Next = nullptr;
	}
	else
	{
		Node* current = remove;

		remove->Prev->Next = current->Next;

		if (remove->Next != nullptr)
			remove->Next->Prev = current->Prev;

		remove->Prev = nullptr;
		remove->Next = nullptr;
	}
}

int Size(Node* list)
{
	int count = 0;
	Node* current = list;
	while (current != nullptr)
	{
		current = current->Next;
		count++;
	}

	return count;
}


int main()
{
	Node* list = nullptr;

	//Push
	for (int i = 0; i < 5; i++)
	{
		Node* node = CreateNode((i + 1) * 100);
		Push(&list, node);
	}

	//Push 결과 출력
	for (int i = 0; i < Size(list); i++)
		printf("[%d] : %d\n", i, GetNode(list, i)->Data);

	//InsertHead 테스트
	Node* newNode = nullptr;

	newNode = CreateNode(-1);
	InsertHead(&list, newNode);
	InsertHead(&list, CreateNode(-2));

	printf("----------\n");
	for (int i = 0; i < Size(list); i++)
		printf("[%d] : %d\n", i, GetNode(list, i)->Data);

	//Insert 테스트
	newNode = CreateNode(999);
	Node* current = GetNode(list, 4);
	Insert(current, newNode);

	printf("----------\n");
	for (int i = 0; i < Size(list); i++)
		printf("[%d] : %d\n", i, GetNode(list, i)->Data);

	//Remove 테스트
	int count = Size(list);
	for (int i = 0; i < count; i++)
	{
		Node* current = GetNode(list, 0);

		Remove(&list, current);
		DestroyNode(current);
	}

	printf("----------\n");
	for (int i = 0; i < Size(list); i++)
		printf("[%d] : %d\n", i, GetNode(list, i)->Data);

	system("pause");
	return 0;
}
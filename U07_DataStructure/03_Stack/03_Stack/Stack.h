#pragma once

#include <string>
using namespace std;

struct Node
{
	string Data;

	Node* Next;
};

class Stack
{
public:
	Stack() = default;
	~Stack();

	void Push(Node* node);
	Node* Pop();

	Node* Top() { return top; }
	int Size();
	bool IsEmpty() { return list == nullptr; }

	static Node* CreateNode(string data);
	static void DestroyNode(Node* node);

private:
	Node* list = nullptr;
	Node* top = nullptr;
};
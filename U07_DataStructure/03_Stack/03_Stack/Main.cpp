#include <stdio.h>
#include <Windows.h>

#include "Stack.h"

int main()
{
	Stack stack;
	stack.Push(Stack::CreateNode("ABC"));
	stack.Push(Stack::CreateNode("DEF"));
	stack.Push(Stack::CreateNode("GHI"));
	stack.Push(Stack::CreateNode("JKL"));

	printf("Size : %d\n", stack.Size());

	int count = stack.Size();
	for (int i = 0; i < count; i++)
	{
		if (stack.IsEmpty() == true)
			break;

		Node* poped = stack.Pop();
		printf("Poped : %s\n", poped->Data.c_str());
		Stack::DestroyNode(poped);
	}

	system("pause");
	return 0;
}
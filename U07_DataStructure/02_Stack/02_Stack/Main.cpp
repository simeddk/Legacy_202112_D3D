#include <iostream>
using namespace std;
#include "Stack.h"

int main()
{
	Stack<int> stack;

	stack.Push(100);
	stack.Push(80);

	cout << "Pop : " <<  stack.Pop() << endl;

	stack.Push(12);
	stack.Push(20);
	stack.Pop();
	stack.Push(4);

	cout << "Front : " << stack.Front() << endl;
	cout << "Back : " << stack.Back() << endl;

	cout << "----------" << endl;
	while (stack.Empty() == false)
		cout << "Pop : " << stack.Pop() << endl;

	stack.Pop();

	system("pause");
	return 0;
}
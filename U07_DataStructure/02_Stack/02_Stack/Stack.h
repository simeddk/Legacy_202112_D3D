#pragma once

#include <assert.h>
#include <Windows.h>

#define MAX_STACK_COUNT 5

template<typename T>
class Stack
{
public:
	Stack()
	{
		memset(values, 0, sizeof(T) * MAX_STACK_COUNT);
	}

	void Push(T val)
	{
		assert(top + 1 < MAX_STACK_COUNT);

		values[++top] = val;
	}

	T Pop()
	{
		bool b = Empty();
		assert(b == false);

		T val = values[top];
		top--;

		return val;
	}

	T Front()
	{
		return values[top];
	}

	T Back()
	{
		assert(top > -1);

		return values[0];
	}

	bool Empty()
	{
		return top < 0;
	}

private:
	int top = -1;

	T values[MAX_STACK_COUNT];
};


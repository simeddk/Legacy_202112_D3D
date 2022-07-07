#include <stdio.h>
#include <Windows.h>
#include "Timer.h"
#include "Fibonacci_DevideConquer.h"

ULONGLONG Fibonacci_DynamicPlanning(int n)
{
	if (n == 0 || n == 1)
		return n;

	ULONGLONG* table = new ULONGLONG[n + 1];

	table[0] = 0;
	table[1] = 1;

	for (int i = 2; i <= n; i++)
		table[i] = table[i - 1] + table[i - 2];

	ULONGLONG result = table[n];
	delete[] table;

	return result;
}

int main()
{
	ULONGLONG result = 0;

	Timer timer;
	timer.Start();
	{
		result = Fibonacci_DevideConquer(1000000);
	}
	timer.End();
	printf("소요시간 : %f\n", timer.RunningTime());
	printf("\n");

	timer.Start();
	{
		result = Fibonacci_DynamicPlanning(1000000);
	}
	timer.End();
	printf("소요시간 : %f\n", timer.RunningTime());


	system("pause");
	return 0;
}
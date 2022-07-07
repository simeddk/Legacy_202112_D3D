#include <stdio.h>
#include <Windows.h>
#include "Timer.h"

struct Matrix
{
	ULONGLONG Data[2][2];
};

Matrix Mul(Matrix a, Matrix b)
{
	Matrix r;

	r.Data[0][0] = a.Data[0][0] * b.Data[0][0] + a.Data[0][1] * b.Data[1][0];
	r.Data[0][1] = a.Data[0][0] * b.Data[0][1] + a.Data[0][1] * b.Data[1][1];

	r.Data[1][0] = a.Data[1][0] * b.Data[0][0] + a.Data[1][1] * b.Data[1][0];
	r.Data[1][1] = a.Data[1][0] * b.Data[0][1] + a.Data[1][1] * b.Data[1][1];

	return r;
}

Matrix Power(Matrix m, int n)
{
	if (n > 1)
	{
		m = Power(m, n / 2);
		m = Mul(m, m);

		if (n & 1)
		{
			Matrix b;
			b.Data[0][0] = 1; b.Data[0][1] = 1;
			b.Data[1][0] = 1; b.Data[1][1] = 0;

			m = Mul(m, b);
		}
	}

	return m;
}

ULONGLONG Fibonacci(int n)
{
	Matrix m;
	m.Data[0][0] = 1; m.Data[0][1] = 1;
	m.Data[1][0] = 1; m.Data[1][1] = 0;

	m = Power(m, n);

	return m.Data[0][1];
}

int main()
{
	int Fn;
	printf("Fn : ");
	scanf_s("%d", &Fn);

	ULONGLONG result = 0;

	Timer timer;
	timer.Start();
	{
		result = Fibonacci(Fn);
	}
	timer.End();
	printf("소요시간 : %f\n", timer.RunningTime());
	printf("Fibonacci() : %llu\n", result);

	
	int left = 1;
	int right = 1;
	int temp = 0;
	
	timer.Start();
	{
		for (int i = 3; i <= Fn; i++)
		{
			temp = left + right;
			left = right;
			right = temp;
		}
	}
	timer.End();
	printf("소요시간 : %f\n", timer.RunningTime());
	printf("for : %llu\n", (ULONGLONG)temp);


	system("pause");
	return 0;
} 
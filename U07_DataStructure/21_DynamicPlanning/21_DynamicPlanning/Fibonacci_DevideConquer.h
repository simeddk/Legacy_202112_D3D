#pragma once

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

ULONGLONG Fibonacci_DevideConquer(int n)
{
	Matrix m;
	m.Data[0][0] = 1; m.Data[0][1] = 1;
	m.Data[1][0] = 1; m.Data[1][1] = 0;

	m = Power(m, n);

	return m.Data[0][1];
}

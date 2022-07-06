#include <stdio.h>
#include <Windows.h>

ULONGLONG Power(int base, int exponent)
{
	if (exponent == 1)
		return base;
	else if (exponent == 0)
		return 1;

	if (exponent % 2 == 0)
	{
		ULONGLONG value = Power(base, exponent / 2);
		return value * value;
	}
	else
	{
		ULONGLONG value = Power(base, (exponent - 1) / 2);
		return value * value * base;
	}
}

int main()
{
	int base;
	int exponent;

	while (true)
	{
		printf("Base : ");
		scanf_s("%d", &base);

		printf("Exponent : ");
		scanf_s("%d", &exponent);

		unsigned long long result = Power(base, exponent);
		printf("%llu\n", result);
	}

	system("pause");
	return 0;
}

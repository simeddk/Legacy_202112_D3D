#include <stdio.h>
#include <Windows.h>

bool IsThreatened(int cols[], int newRow)
{
	int currRow = 0;
	bool bCheck = false;

	while (currRow < newRow)
	{
		if (cols[newRow] == cols[currRow] ||
			abs(cols[newRow] - cols[currRow]) == abs(newRow - currRow))
		{
			bCheck = true;
			break;
		}

		currRow++;
	}

	return bCheck;
}

void Print(int cols[], int count)
{
	for (int y = 0; y < count; y++)
	{
		for (int x = 0; x < count; x++)
		{
			if (cols[y] == x)
				printf(" Q");
				//printf(" %d", cols[y]);
			else
				printf(" +");
				//printf(" %d", cols[y]);
		}
		printf("\n");
	}
}

void FindSolution(int cols[], int row, int count, int* solution)
{
	if (IsThreatened(cols, row) == true)
		return;

	if (count - 1 == row)
	{
		printf("\nSolution #%d \n", ++(*solution));

		Print(cols, count);
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			cols[row + 1] = i;
			FindSolution(cols, row + 1, count, solution);
		}
	}
}

int main()
{
	int count = 0;
	printf("Ä­¼ö ÀÔ·Â : ");
	scanf_s("%d", &count);

	int* cols = new int[count];

	int solution = 0;
	for (int y = 0; y < count; y++)
	{
		cols[0] = y;

		FindSolution(cols, 0, count, &solution);
	}

	delete[] cols;

	system("pause");
	return 0;
}
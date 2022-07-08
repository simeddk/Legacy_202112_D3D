#include <stdio.h>
#include <Windows.h>

struct Table
{
	int** Data;
};

int LCS(char* str1, char* str2, int str1Length, int str2Length, Table* table)
{
	for (int i = 0; i <= str1Length; i++)
		table->Data[i][0] = 0;

	for (int i = 0; i <= str2Length; i++)
		table->Data[0][i] = 0;

	for (int row = 1; row <= str1Length; row++)
	{
		for (int col = 1; col <= str2Length; col++)
		{
			if (str1[row - 1] != str2[col - 1])
				table->Data[row][col] = max(table->Data[row-1][col], table->Data[row][col-1]);
			else
				table->Data[row][col] = table->Data[row - 1][col - 1] + 1;
		}
	}

	return table->Data[str1Length][str2Length];
}

void BackTrack(char* x, char* y, int m, int n, Table* table, char* outList)
{
	if (m == 0 || n == 0)
		return;

	//조건1. 내가 주변보다 크다 -> 리스트 추가 -> 좌상고
	bool a = true;
	a &= table->Data[m][n] > table->Data[m][n - 1];
	a &= table->Data[m][n] > table->Data[m - 1][n];
	a &= table->Data[m][n] > table->Data[m - 1][n - 1];

	//조건2. 좌와 같고, 상보다 크다 -> 좌고
	bool b = true;
	b &= table->Data[m][n] == table->Data[m][n - 1];
	b &= table->Data[m][n] > table->Data[m - 1][n];

	//조건1에 걸린 경우
	if (a)
	{
		char buff[100];
		strcpy(buff, outList);

		sprintf(outList, "%c%s", x[m - 1], buff);

		BackTrack(x, y, m - 1, n - 1, table, outList);
	}

	//조건2에 걸린 경우
	else if (b)
		BackTrack(x, y, m, n - 1, table, outList);

	//조건3에 걸린 경우
	else
		BackTrack(x, y, m - 1, n, table, outList);

}

int main()
{
	char* a = (char*)"GOOD MORNING";
	char* b = (char*)"GUTEN MORGEN";

	//char* a = (char*)"AXYC";
	//char* b = (char*)"ABCD";

	int lenA = strlen(a);
	int lenB = strlen(b);

	Table table;
	table.Data = new int* [lenA + 1];

	for (int i = 0; i < lenA + 1; i++)
	{
		table.Data[i] = new int[lenB + 1];
		memset(table.Data[i], 0, sizeof(int) * (lenB + 1));
	}

	int reuslt = LCS(a, b, lenA, lenB, &table);

	//테이블 출력
	printf("\n%-04s", " ");

	for (int i = 0; i <= lenB; i++)
		printf("%c ", b[i]);
	printf("\n");

	for (int i = 0; i <= lenA; i++)
	{
		printf("%c ", a[i - 1]);

		for (int j = 0; j <= lenB; j++)
			printf("%d ", table.Data[i][j]);

		printf("\n");
	}

	printf("\n\n중복 글자 수 : %d\n", reuslt);
	
	printf("\n\n역탐색 : ");
	char* lcs = (char*)malloc(sizeof(table.Data[lenA][lenB] + 1));
	sprintf(lcs, "");

	BackTrack(a, b, lenA, lenB, &table, lcs);

	printf("%s\n", lcs);

	system("pause");
	return 0;
}
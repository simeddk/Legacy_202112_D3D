#include <Windows.h>
#include <stdio.h>

int main()
{
	srand((UINT)GetTickCount64());

	FILE* file = nullptr;
	
	fopen_s(&file, "../Data.csv", "w");

	for (UINT i = 0; i < USHRT_MAX; i++)
		fprintf(file, "%d,%d\n", i, rand());

	fclose(file);

	printf("파일이 생성되었다\n");


	system("pause");
	return 0;
}
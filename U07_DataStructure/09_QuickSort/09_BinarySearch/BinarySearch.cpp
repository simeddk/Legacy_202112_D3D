#include <stdio.h>
#include <Windows.h>

struct Data
{
	UINT Index;
	UINT Value;
};

void ReadData(Data* datas)
{
	FILE* file = nullptr;
	fopen_s(&file, "../Result.csv", "r");
	
	for (UINT i = 0; i < USHRT_MAX; i++)
		fscanf_s(file, "%d,%d", &datas[i].Index, &datas[i].Value);

	fclose(file);
}

Data* SequenceSearch(Data* datas,  UINT size, UINT target, OUT int& count)
{
	Data* result = nullptr;

	for (UINT i = 0; i < size; i++)
	{
		count++;

		if (datas[i].Value == target)
		{
			result = &datas[i];

			break;
		}
	}

	return result;
}

Data* BinarySearch(Data* datas, UINT size, UINT target, OUT int& count)
{
	int left = 0;
	int right = size - 1;

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (datas[middle].Value == target)
			return &datas[middle];
		else if (datas[middle].Value < target)
			left = middle + 1;
		else if (datas[middle].Value > target)
			right = middle - 1;

		count++;
	}

	return nullptr;
}

int main()
{
	Data datas[USHRT_MAX];
	ReadData(datas);

	int target = 32765;
	int count = 0;

	Data* result = SequenceSearch(datas, USHRT_MAX, target, count);
	printf("찾는 값 : %d, %d 번만에 찾음\n", result->Value, count);

	count = 0;
	result = BinarySearch(datas, USHRT_MAX, target, count);
	printf("찾는 값 : %d, %d 번만에 찾음\n", result->Value, count);

	system("pause");
	return 0;
}
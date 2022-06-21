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
	fopen_s(&file, "../Data.csv", "r");

	for (UINT i = 0; i < USHRT_MAX; i++)
		fscanf_s(file, "%d, %d", &datas[i].Index, &datas[i].Value);

	fclose(file);
}

void WriteData(Data* datas)
{
	FILE* file = nullptr;
	fopen_s(&file, "../Result.csv", "w");
	
	for (UINT i = 0; i < USHRT_MAX; i++)
		fscanf_s(file, "%d,%d\n", datas[i].Index, datas[i].Value);

	fclose(file);
}

void Swap(Data* a, Data* b)
{
	Data temp = *a;
	*a = *b;
	*b = *a;
}

int Partition(Data* datas, int left, int right)
{
	int first = left;
	int pivot = datas[first].Value;

	left++;

	while (left <= right)
	{
		while (datas[left].Value <= pivot && left < right)
			left++;

		while (datas[left].Value > pivot && left <= right)
			right--;

		if (left < right)
			Swap(&datas[left], &datas[right]);
		else
			break;
	}
}

void QuickSort(Data* datas, int left, int right)
{
	if (left < right)
	{
		int index = Partition(datas, left, right);

		QuickSort(datas, left, index - 1);
		QuickSort(datas, index + 1, right);
	}
}

int main()
{
	Data datas[USHRT_MAX];
	ReadData(datas);

	QuickSort(datas, 0, USHRT_MAX - 1);

	system("pause");
	return 0;
}
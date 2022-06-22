#include <stdio.h>
#include <Windows.h>
#include <algorithm>
#include "Timer.h"

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
		fprintf(file, "%d,%d\n", datas[i].Index, datas[i].Value);

	fclose(file);
}

void Swap(Data* a, Data* b)
{
	Data temp = *a;
	*a = *b;
	*b = temp;
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

		while (datas[right].Value > pivot && left <= right)
			right--;

		if (left < right)
			Swap(&datas[left], &datas[right]);
		else
			break;
	}

	Swap(&datas[first], &datas[right]);

	return right;
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

int Compare(const void* val1, const void* val2)
{
	Data* data1 = (Data*)val1;
	Data* data2 = (Data*)val2;

	//크다 1, 작다 -1, 같다 0
	if (data1->Value > data2->Value)
		return 1;
	else if (data1->Value < data2->Value)
		return -1;
	else
		return 0;
}

bool Compare2(const Data& val1, const Data& val2)
{
	return val1.Value < val2.Value; //>내림차순, <오름차순
}

int main()
{
	Data datas[USHRT_MAX];
	ReadData(datas);

	Timer timer;

	timer.Start();
	QuickSort(datas, 0, USHRT_MAX - 1);
	timer.End();
	printf("우리가 만든 qsort : %f\n", timer.RunningTime());

	WriteData(datas);

	timer.Start();
	qsort(datas, USHRT_MAX, sizeof(Data), Compare); //C
	timer.End();
	printf("C에서 제공하는 qsort : %f\n", timer.RunningTime());

	timer.Start();
	std::sort(datas, datas + USHRT_MAX, Compare2); //C++
	timer.End();
	printf("C++에서 제공하는 sort : %f\n", timer.RunningTime());

	system("pause");
	return 0;
}
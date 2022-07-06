#include <stdio.h>
#include <Windows.h>
#include <algorithm>
#include "Timer.h"

void Conquer(int data[], int start, int mid, int end)
{
	int left = start;
	int right = mid + 1;

	int destIndex = 0;
	int* dest = new int[end - start + 1];

	while (left <= mid && right <= end)
	{
		if (data[left] < data[right])
		{
			dest[destIndex] = data[left];
			left++;
		}
		else
		{
			dest[destIndex] = data[right];
			right++;
		}

		destIndex++;
	}

	while (left <= mid)
		dest[destIndex++] = data[left++];

	while (right <= end)
		dest[destIndex++] = data[right++];

	destIndex = 0;
	for (int i = start; i <= end; i++)
		data[i] = dest[destIndex++];

	delete[] dest;
}

void Devide(int data[], int start, int end)
{
	if (end - start < 1) return;

	int mid = (start + end) / 2;

	Devide(data, start, mid);
	Devide(data, mid + 1, end);

	Conquer(data, start, mid, end);
}

int main()
{
	int data[] = { 9, 5, 8, 7, 4, 3, 1, 2, 6 };
	int count = sizeof(data) / sizeof(data[0]);

	Timer timer;
	timer.Start();
	{
		Devide(data, 0, count - 1);
	}
	timer.End();
	printf("소요시간 : %f\n", timer.RunningTime());

	int data2[] = { 9, 5, 8, 7, 4, 3, 1, 2, 6 };

	timer.Start();
	{
		std::sort(data2, data2 + count);
	}
	timer.End();
	printf("소요시간 : %f\n", timer.RunningTime());

	/*for (int i = 0; i < count; i++)
		printf("%d ", data[i]);
	printf("\n");*/

	system("pause");
	return 0;
}
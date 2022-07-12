#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void Sum(vector<int>::iterator start, vector<int>::iterator end, int* result)
{
	int sum = 0;
	for (auto it = start; it < end; ++it)
		sum += *it;

	*result = sum;

	thread::id id = this_thread::get_id();
	printf("Thread(%x)에서 %d ~ %d까지 계산한 결과 : %d\n", id, *start, *end - 1, sum);
}

int main()
{
	//0~100 Data
	vector<int> data;
	for (int i = 0; i <= 100; i++)
		data.push_back(i);

	vector<int> results(4);

	//Thread 구성
	vector<thread> threads;
	for (int i = 0; i < 4; i++)
	{
		threads.push_back(thread
		(
			Sum,
			data.begin() + i * 25,
			data.begin() + ((i + 1) * 25),
			&results[i]
		));
	}

	//Thread 종료
	for (int i = 0; i < 4; i++)
		threads[i].join();


	//최종합산
	int sum = 0;
	for (int i = 0; i < 4; i++)
		sum += results[i];

	printf("%d\n", sum);

	system("pause");
	return 0;
}
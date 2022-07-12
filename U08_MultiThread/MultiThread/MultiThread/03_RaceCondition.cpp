#include <iostream>
#include <thread>
#include <vector>
#include <functional>
using namespace std;

class RaceConditionExample
{
public:
	void Thread(int& count)
	{
		for (int i = 0; i < 1e+4; i++)
			count++;
	}

	void RaceCondition()
	{
		int count = 0;
		vector<thread> threads;

		for (int i = 0; i < 4; i++)
		{
			function<void(int&)> delegate_oneParam = bind(&RaceConditionExample::Thread, this, placeholders::_1);
			threads.push_back(thread(delegate_oneParam, ref(count)));
		}

		for (int i = 0; i < 4; i++)
			threads[i].join();

		printf("count : %d\n", count);
	}

};

int main()
{
	RaceConditionExample ob;
	ob.RaceCondition();


	system("pause");
	return 0;
}
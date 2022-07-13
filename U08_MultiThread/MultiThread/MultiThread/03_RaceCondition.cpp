#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include "Timer.h"
using namespace std;

class RaceConditionExample
{
public:
	void Thread(int& count)
	{
		//m.lock();
		lock_guard<mutex> lock(m);
		{
			for (int i = 0; i < 1e+6; i++)
				count++;
		}
		//m.unlock();
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

private:
	mutex m;
};

int main()
{
	//RaceConditionExample ob;
	//ob.RaceCondition();

	Timer timer1;
	timer1.SetTimer([]()
	{
		printf("난 2초마다 2번 콜이 되지\n");
	}, 2000, 2);

	Timer tiemr2;
	tiemr2.SetTimer([]()
	{
		printf("난 1초마다 매번 콜이 되지\n");
	}, 1000);

	system("pause");
	return 0;
}
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

void Thread1(mutex& m1, mutex& m2)
{
	for (int i = 0; i < 1e+4; i++)
	{
		lock_guard<mutex> lock1(m1);
		lock_guard<mutex> lock2(m2);
		printf("Thread1\n");
	}
}

void Thread2(mutex& m1, mutex& m2)
{
	for (int i = 0; i < 1e+4; i++)
	{
		while (true)
		{
			m2.lock();

			if (m1.try_lock() == false)
			{
				m2.unlock();
				continue;
			}

			printf("Thread2\n");
			m1.unlock();
			m2.unlock();
			break;
		}
	}
}

int main()
{
	mutex m1, m2;
	thread t1(Thread1, ref(m1), ref(m2));
	thread t2(Thread2, ref(m1), ref(m2));
	t1.join();
	t2.join();

	printf("메인 루틴 끝\n");

	system("pause");
	return 0;
}
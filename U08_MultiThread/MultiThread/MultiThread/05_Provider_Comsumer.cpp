#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include <vector>
using namespace std;

//---------------------------------------------------------
//Data
//---------------------------------------------------------
class AName
{
public:
	static string* Names() { return URLs; }

private:
	static string URLs[5];
};

string AName::URLs[5] =
{
	"https://naver.com",
	"https://daum.net",
	"https://youtube.com",
	"https://facebook.com",
	"https://instagram.com"
};

//---------------------------------------------------------
//Provider -> 큐에 값을 넣어서 제공
//---------------------------------------------------------
void Provider(queue<string>* receives, mutex* m, int index)
{
	string* names = AName::Names();

	for (int i = 0; i < 5; i++)
	{
		this_thread::sleep_for(chrono::microseconds(100 * index));
		string content = "Thread(" + to_string(index) + "), Value : " + names[i];

		m->lock();
		receives->push(content);
		m->unlock();
	}

}
//---------------------------------------------------------
//Consumer -> 큐에 값이 있으면 꺼내오기
//---------------------------------------------------------
void Consumer(queue<string>* receives, mutex* m, int* count)
{
	while (*count < 25)
	{
		m->lock();

		if (receives->empty())
		{
			m->unlock();

			this_thread::sleep_for(chrono::milliseconds(10));
			continue;
		}

		string poped = receives->front();
		receives->pop();
		(*count)++;
		m->unlock();

		printf("Poped : %2d, %s\n", *count, poped.c_str());
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}

int main()
{
	queue<string> receives;
	mutex m;

	//5개의 공급자 스레드 돌리기
	vector<thread> providers;
	for (int i = 0; i < 5; i++)
		providers.push_back(thread(Provider, &receives, &m, i + 1));

	//소비자 스레드
	int count = 0;
	thread consumer(Consumer, &receives, &m, &count);

	//스레드 해제
	for (int i = 0; i < 5; i++)
		providers[i].join();
	consumer.join();

	//메인루틴 종료
	printf("메인루틴 종료\n");

	system("pause");
	return 0;
}
#include <iostream>
#include <thread>
#include <functional>
using namespace std;

class Test
{
public:
	void Func1()
	{
		for (int i = 0; i < 10; i++)
			cout << "Thread1" << endl;
	}

	void Func2()
	{
		for (int i = 0; i < 10; i++)
			cout << "Thread2" << endl;
	}

	void Func3()
	{
		for (int i = 0; i < 10; i++)
			cout << "Thread3" << endl;
	}

	void Func4(int a)
	{
		thread::id id = this_thread::get_id();

		for (int i = 0; i < a; i++)
			//cout << id << " : ("  << i  << ")" << endl;
			printf("%d : (%d)\n", id, i);
	}
};

int main()
{
	Test ob;

	//thread t1(bind(&Test::Func1, ob));
	//thread t2(bind(&Test::Func2, ob));
	//thread t3(bind(&Test::Func3, ob));
	
	//t1.detach();
	//printf("t1 종료\n");
	//t2.detach();
	//printf("t2 종료\n");
	//t3.detach();
	//printf("t3 종료\n");

	thread t4(bind(&Test::Func4, ob, placeholders::_1), 10);
	thread t5(bind(&Test::Func4, ob, placeholders::_1), 10);
	thread t6(bind(&Test::Func4, ob, placeholders::_1), 10);
	t4.detach();
	t5.detach();
	t6.detach();

	system("pause");
	return 0;
}
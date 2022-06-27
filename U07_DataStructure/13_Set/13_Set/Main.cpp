#include <stdio.h>
#include <Windows.h>
#include <set>
#include <string>
using namespace std;

struct Compare
{
	template<typename T>
	bool operator()(const T& left, const T& right)
	{
		if (left.first == right.first) //fist가 같은 경우 second 기준으로 정렬할 수 있음
			return left.second > right.second; // < 오름차순, > 내림차순 

		return left.first > right.first; // < 오름차순, > 내림차순 
	}
};

int main()
{
	set<int> s = {5, 2, 4, 6, 1, 2};
	for (int i : s)
		printf("%d, ", i);
	printf("\n");

	set<pair<string, int>, Compare> s2 =
	{
		{"B", 4},  {"E", 2}, {"A", 5}, {"D", 1}, {"B", 5}
	};
	for (pair<string, int> i : s2)
		printf("%s, %d\n", i.first.c_str(), i.second);


	system("pause");
	return 0;
}
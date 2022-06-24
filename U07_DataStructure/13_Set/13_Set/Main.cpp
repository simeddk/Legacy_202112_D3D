#include <stdio.h>
#include <Windows.h>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

int main()
{
	//unordered
	map<string, int> m;
	m["나의 가치"] = 100; //insert? create? push???
	m["너의 가치"] = 0;
	m["우리의 가치"] = 999;
	m["너희의 가치"] = -999;
	m["너희의 가치"] = 77777777;

	for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it)
		printf("%s, %d\n", it->first.c_str(), it->second);

	system("pause");
	return 0;
}
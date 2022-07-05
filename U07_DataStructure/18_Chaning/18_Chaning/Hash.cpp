#include <stdio.h>
#include <string>
#include <Windows.h>
using namespace std;

#include "Chaining.h"

unsigned int GetHash(string key, unsigned int tableSize)
{
	unsigned int value = 0;
	
	for (unsigned int i = 0; i < key.size(); i++)
		value = (value << 3) + (unsigned int)key[i]; //ÀÚ¸´¼ö Á¢±â

	return value % tableSize; //³ª´°¼À¹ý
}

int main()
{
	/*string key = "BA";

	unsigned int index = GetHash(key, 12289);
	printf("%s : %d\n", key.c_str(), index);

	key = "AI";
	index = GetHash(key, 12289);
	printf("%s : %d\n", key.c_str(), index);*/

	Chaining<int> hash(12289);
	hash.Set("AI", 2000);
	hash.Set("JA", 1999);
	hash.Set("BA", 2001);
	hash.Set("EE", 2002);

	printf("--------------\n");
	printf("%d\n", hash.Get("AI")); //2000
	printf("%d\n", hash.Get("JA")); //1999
	printf("%d\n", hash.Get("BA")); //2001
	printf("%d\n", hash.Get("EE")); //2002

	system("pause");
	return 0;
}
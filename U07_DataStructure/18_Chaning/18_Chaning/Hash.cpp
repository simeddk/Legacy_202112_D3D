#include <stdio.h>
#include <string>
using namespace std;

unsigned int GetHash(string key, unsigned int tableSize)
{
	unsigned int value = 0;
	
	for (unsigned int i = 0; i < key.size(); i++)
		value = (value << 3) + (unsigned int)key[i]; //ÀÚ¸´¼ö Á¢±â

	return value % tableSize; //³ª´°¼À¹ý
}

int main()
{
	string key = "BA";

	unsigned int index = GetHash(key, 12289);
	printf("%s : %d\n", key.c_str(), index);

	key = "AI";
	index = GetHash(key, 12289);
	printf("%s : %d\n", key.c_str(), index);

	system("pause");
	return 0;
}
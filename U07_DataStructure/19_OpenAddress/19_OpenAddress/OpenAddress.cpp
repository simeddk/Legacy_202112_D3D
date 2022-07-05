#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#include "OpenAddress.h"

int main()
{
	OpenAddress<const char*> hash(10);
	hash.Set("GCP", 3, "GCP");
	hash.Set("REDH", 4, "Redhat");
	hash.Set("APAC", 4, "Apache");
	hash.Set("ZYMZ", 4, "Unisys");
	hash.Set("MSFT", 4, "MicroSoft");
	hash.Set("IBM", 3, "IBM");
	hash.Set("ORCL", 4, "Oracle");
	hash.Set("GOOG", 4, "Google");
	hash.Set("YHOO", 4, "Yahoo");
	hash.Set("NOVL", 4, "Novell");

	string value = hash.Get("GCP", 3);
	printf("GCP : %s\n", value.c_str()); 

	value = hash.Get("YHOO", 4);
	printf("????? : %s\n", value.c_str());

	system("pause");
	return 0;
}
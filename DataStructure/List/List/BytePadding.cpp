#include <stdio.h>
#include <Windows.h>

int main()
{
	struct Tag1
	{
		int A;		//4
		short B;	//2
		char C;		//1
		double D;	//8
	};
	printf("%d Bytes\n", sizeof(Tag1));
	Tag1 t;

	struct Tag2
	{
		short B;	//2
		int A;		//4
		char C;		//1
		double D;	//8
	};
	printf("%d Bytes\n", sizeof(Tag2));

	struct Tag3
	{
		int A;		//4
		short B;	//2
		char C;		//1
		
		Tag3* tag;	//4
	};
	printf("%d Bytes\n", sizeof(Tag3));


	system("pause");
	return 0;
}
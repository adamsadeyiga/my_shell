#include <stdio.h>

int main()
{

	int a = 10;
	int b = 30;
	int x = 0;

	x |= a;
	x |= b;

	if(x & a){
		printf("a \n");
	}
	if (x & b)
	{
		printf("b \n");
	}
	if (x & 0)
	{
		printf("other \n");
	}

	return (0);
}

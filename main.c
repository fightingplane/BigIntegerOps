#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigIntegerOps.h"

int main(void)
{

	char a[1] = {'1'};
	char b[1] = {'2'};
	int resultLen = 0;
	char* res = bigIntAdd(a, 1, b, 1, &resultLen); 
	if(res && resultLen > 0)
	{
		printf("%s", res);
		free(res);
	}
	else
	{
		printf("failed to process operation\n");
	}
	return 0;
}

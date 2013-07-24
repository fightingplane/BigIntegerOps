#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigIntegerOps.h"

int main(void)
{

	char a[3] = {'1','2','3'};
	char b[1] = {'2'};
	char c[5] = {'-', '1', '2', '3', '4'};
	char d[3] = {'+', '1', '2'};

	int resultLen = 0;

	if(isInteger(a, 3) == 0) 
		printf("a[%s] is an integer\n", a);
	else
		printf("sanity check failed");

	if(isInteger(c, 5) == 0)
		printf("c[%s] is an integer\n", c);
	else
		printf("c[%s] sanity check failed", c);

	if(isInteger(d, 3) == 0)
		printf("d[%s] is an integer\n", d);
	else
		printf("d failed to sanity check");

	if(isZero(a, 3) != 0)
		printf("a is not zero\n");

	if(isZero(c, 5) != 0)
		printf("c is not a zero number\n");
	if(isZero(d, 3) != 0)
		printf("d is not a zero number\n");

	if(isPossitive(a, 3) == 0)
		printf("a is a possitive value\n");
	else
		printf("a should be a possitive value\n");

	if(isPossitive(d, 3) == 0)
		printf("d is a possitive value\n");
	else
		printf("d should be a possitive value\n");


	int res1 = 0;
	char* absA = bigIntAbs(a, 3, &res1);
	if(absA == NULL || res1 == 0)
		printf("unable to get A's abs\n");
	else
		printf("a's abs == %s\n", absA);

	char* res = bigIntAdd(a, 3, b, 1, &resultLen); 
	if(res && resultLen > 0)
	{
		printf("test result %s + %s == %s\n", a, b, res);
		free(res);
		res = NULL;
	}
	else
		printf("failed to process operation\n");

	res = bigIntAdd(a, 3, d, 3, &resultLen); 
	if(res && resultLen > 0)
	{
		printf("test result %s + %s == %s\n", a, d, res);
		free(res);
		res = NULL;
	}
	else
		printf("failed to process operation\n");

	res = bigIntAdd(c, 5, d, 3, &resultLen); 
	if(res && resultLen > 0)
	{
		printf("test result %s + %s == %s\n", c, d, res);
		free(res);
		res = NULL;
	}
	else
		printf("failed to process operation\n");

	return 0;
}

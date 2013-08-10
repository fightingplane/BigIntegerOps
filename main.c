#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigIntegerOps.h"

int main(void)
{

	char* a = "123";// {'1','2','3', '\0'};
	char* b = "2"; // {'2', '\0'};
	char* c = "-1234"; //{'-', '1', '2', '3', '4', '\0'};
	char* d = "+12"; //{'+', '1', '2', '\0'};

	int resultLen = 0;

	bigIntMutiTenPow(a, strlen(a), 2, &resultLen);

	bigIntMultiple(a, strlen(a), d, strlen(d), &resultLen);
	char* e = "12";
	bigIntMultipleN(e, strlen(e), 9, &resultLen);
	if(isInteger(a, strlen(a)) == 0) 
		printf("a[%s] is an integer\n", a);
	else
		printf("sanity check failed");

	if(isInteger(c, strlen(c)) == 0)
		printf("c[%s] is an integer\n", c);
	else
		printf("c[%s] sanity check failed", c);

	if(isInteger(d, strlen(d)) == 0)
		printf("d[%s] is an integer\n", d);
	else
		printf("d failed to sanity check");

	if(isZero(a, strlen(a)) != 0)
		printf("a is not zero\n");

	if(isZero(c, strlen(c)) != 0)
		printf("c is not a zero number\n");
	if(isZero(d, strlen(d)) != 0)
		printf("d is not a zero number\n");

	if(isPossitive(a, strlen(a)) == 0)
		printf("a is a possitive value\n");
	else
		printf("a should be a possitive value\n");

	if(isPossitive(d, strlen(d)) == 0)
		printf("d is a possitive value\n");
	else
		printf("d should be a possitive value\n");


	int res1 = 0;
	char* absA = bigIntAbs(a, strlen(a), &res1);
	if(absA == NULL || res1 == 0)
		printf("unable to get A's abs\n");
	else
		printf("a's abs == %s\n", absA);

	char* res = bigIntAdd(a, strlen(a), b, strlen(b), &resultLen); 
	if(res && resultLen > 0)
	{
		printf("test result %s + %s == %s\n", a, b, res);
		free(res);
		res = NULL;
	}
	else
		printf("failed to process operation\n");

	res = bigIntAdd(a, strlen(a), d, strlen(d), &resultLen); 
	if(res && resultLen > 0)
	{
		printf("test result %s + %s == %s\n", a, d, res);
		free(res);
		res = NULL;
	}
	else
		printf("failed to process operation\n");

	res = bigIntAdd(c, strlen(c), d, strlen(d), &resultLen); 
	if(res && resultLen > 0)
	{
		printf("test result %s + %s == %s\n", c, d, res);
		free(res);
		res = NULL;
	}
	else
		printf("failed to process operation\n");

	char* divideLhs = "12345";
	char* divideRhs = "12";
	char* mod = NULL;
	int divideResLen = 0;
	int modLen = 0;
	bigIntDevide(divideLhs, strlen(divideLhs), divideRhs, strlen(divideRhs), &divideResLen, &mod, &modLen);

	return 0;
}

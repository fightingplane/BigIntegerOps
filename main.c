#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "BigIntegerOps.h"

void doCalc(const char* const lhs, const unsigned int lhsLen, const char* rhs, const unsigned int rhsLen, char op);

int main(void)
{
	char lhs[400] = {0};
	char rhs[400] = {0};
	char op;

	while(scanf("%s", lhs) != EOF)
	{
		getchar();
		op = getchar();
		scanf("%s", rhs);
		getchar();
		doCalc(lhs, strlen(lhs), rhs, strlen(rhs), op);
		memset(lhs, 0, 400);
		memset(rhs, 0, 400);
	}
	return 0;
}

void doCalc(const char* const lhs, const unsigned int lhsLen, const char* rhs, const unsigned int rhsLen, char op)
{
	int res = 0;
	char* result = NULL;
	int resLen = 0;
	char* modRes = NULL;
	int modResLen = 0;

	/*
	printf("lhs= %s\n",lhs);
	printf("rhs=%s\n", rhs);
	printf("op=%c\n",op);
	*/
	clock_t t = clock();
	do
	{
		if(lhs == NULL || rhs == NULL)
			break;
		if(isInteger(lhs, lhsLen) != 0 || isInteger(rhs, rhsLen) != 0)
			break;
		if(op != '+' && op != '-' && op != '*' && op != '/')
			break;

		switch(op)
		{
			case '+':
				{
					result = bigIntAdd(lhs, lhsLen, rhs, rhsLen, &resLen);
					break;
				}
			case '-':
				{
					result = bigIntSub(lhs, lhsLen, rhs, rhsLen, &resLen);
					break;
				}
			case '*':
				{
					result = bigIntMultiple(lhs, lhsLen, rhs, rhsLen, &resLen);
					break;
				}
			case '/':
				{
					result = bigIntDevide(lhs, lhsLen, rhs, rhsLen, &resLen, &modRes, &modResLen);
					break;
				}
		}

		if(result == NULL || resLen == 0)
			break;

		res = 1;

	}while(0);

	t = clock() - t;
	printf("Run Time:%f(seconds)\n", (float)t/CLOCKS_PER_SEC);
	if(res == 0)//false;
	{	
		printf("Operation Failed\n");
	}
	if(res == 1)//success
	{
		printf("Result:%s\n\n", result);
		ROCKY_SAFE_DELETE(result);
		ROCKY_SAFE_DELETE(modRes);
	}
}


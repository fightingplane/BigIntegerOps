#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include "BigIntegerOps.h"

#define SIZE_MAX 65535
int isInteger(const char* const bigInt, const int length)
{
	//-1234
	//+1234
	//0001234
	//^[0]+ [-|+][0-9]
	
	if(NULL == bigInt || 0 >= length) return -1;
	//get the first non-zero position
	int i = 0;
	for(; i < length; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i >= length) return 0; ///zero
	
	if(bigInt[i] == '-' || bigInt[i] == '+') ++i;
	if(i >= length) return 0; ///- || + treat as zero
	for(; i< length; ++i)
	{
		if(bigInt[i] < '0' || bigInt[i] > '9')
			return -1;
	}
	return 0;
}

int isZero(const char* const bigInt, const int length)
{
	if(NULL == bigInt || 0 >= length) return -1;
	//get the first non-zero position
	int i = 0;
	for( ; i < length; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i >= length) return 0; ///zero
	
	if(bigInt[i] == '-' || bigInt[i] == '+') ++i;

	if(i >= length) return 0; 
	////0000[-+]00000
	for( ; i < length; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i < length)
	   	return -1;
	else
	   	return 0;
}
	
char* bigIntAbs(const char* const bigInt, const int length, int* targetLength)
{
	if(0 != isInteger(bigInt, length)) 
	{
		*targetLength = 0;
		return NULL;
	}
	//return the pure integer part
	int i = 0;
	for(; i < length; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i >= length)
	{
		char* ret = (char*) malloc(1);
		if(ret == NULL)
		{
			printf("unable to allocate more memory");
			return NULL;
		}
		ret[0] = '0';
		*targetLength = 1;
		return ret;
	} ///zero
	
	if(bigInt[i] == '-' || bigInt[i] == '+') ++i;
	if(i >= length) 
	{
		char* ret = (char*) malloc(1);
		if(NULL == ret)
		{
			printf("unable to allocate more memory");
			return NULL;
		}
		ret[0] = '0';
		*targetLength = 1;
		return ret;
	} ///- || + treat as zero;

	//since we have checked the sanity, just copy the numbers;
	char* ret = (char*) malloc(length - i + 1);
	memset(ret, 0, length - i + 1);
	memcpy(ret, bigInt + i, length - i + 1);
	return ret;
}

int bigIntCompare(const char* const lhs, const int lhsLength, const char* const rhs, int rhsLength)
{
	int possitiveA = isPossitive(lhs, lhsLength);
	int possitiveB = isPossitive(rhs, rhsLength);
	
	if(0 == possitiveA && 0 != possitiveB) return 1;

	if(0 != possitiveA && 0 == possitiveB) return -1;

	int retVal = 0;
	char* newLhs = NULL;
   	char* newRhs = NULL;
	int newLhsLength = 0, newRhsLength = 0;
	newLhs = bigIntAbs(lhs, lhsLength, &newLhsLength);
	newRhs = bigIntAbs(rhs, rhsLength, &newRhsLength);	

	do
	{
		if(!newLhs || 0 == newLhsLength)
		{
			retVal = -1;
			break;
		}

		if(!newRhs || 0 == newRhsLength )
		{
			retVal = 1;
			break;
		}

		if(0 == possitiveA && 0 == possitiveB)
			retVal = strcmp(newLhs, newRhs);
		else if(!possitiveA && !possitiveB)
			retVal = strcmp(newRhs, newLhs);
	}while(0);

	if(newLhs) free(newLhs);
	if(newRhs) free(newRhs);

	return retVal;
}

int isPossitive(const char* const bigInt, const int length)
{
	if(NULL == bigInt || length <= 0) return 0;

	if(bigInt[0] == '+')
		return 0;
	
	if(bigInt[0] == '0')
	{
		int i;
		for(i = 1; i < length; ++i)
		{
			if(bigInt[i] != '0')
				break;
		}

		if(bigInt[i] == '+' || (bigInt[i] >= '1' && bigInt[i] <= '9'))
			return 0;
	}

	return -1;
}

char* bigIntAdd(const char* const lhs, const int lhsLength, const char* const rhs, const int rhsLength, int* resultLen)
{
	char res[SIZE_MAX] = {0};
	if(!isInteger(lhs, lhsLength) || !isInteger(rhs, rhsLength))
	{
		*resultLen = 0;
		return NULL;
	}

	int possitiveLhs = isPossitive(lhs, lhsLength);
	int possitiveRhs = isPossitive(rhs, rhsLength);

	int newLhsLen = 0;
	char* newLhs = bigIntAbs(lhs, lhsLength, &newLhsLen);
	if(!newLhs || 0 == newLhsLen) return NULL;
	
	int newRhsLen = 0;
	char* newRhs = bigIntAbs(rhs, rhsLength, &newRhsLen);
	if(!newRhs || 0 == newRhsLen)
	{
		free(newLhs);
		return NULL;
	}

	int index = SIZE_MAX - 1;
	int carry = 0, bitNum = 0;
	int op = ((possitiveRhs == 0 && possitiveLhs == -1) || (possitiveLhs == 0 && possitiveRhs == -1)) ? -1 : 0;//-1 means minus, and 0 mean add

	--newLhsLen;
	--newRhsLen;
	while(index > 0 && newLhsLen > 0 && newRhsLen > 0)
	{
		if(0 == op)
			res[index] = carry + newLhs[newLhsLen] + newRhs[newRhsLen] - '0';
		else
			res[index] = carry + newLhs[newLhsLen] - newRhs[newRhsLen] - '0';
		bitNum = res[index] - '0';
		if(bitNum >= 0)
		{
			if((carry = bitNum >= 10 ? 1 : 0) == 1) 
				bitNum -= 10;
		}
		else
		{
			if((carry = bitNum <= -10 ? -1 : 0) == -1)
				bitNum += 10;
		}
		res[index] = '0' + bitNum;
		
		--index;
		--newLhsLen;
		--newRhsLen;
	}

	if(newLhsLen > 0)
	{///merge rhs 
		while(newRhsLen > 0)
		{
			res[index] = carry + rhs[newRhsLen];
			bitNum = res[index] - '0';
			if(bitNum >= 0)
			{
				if((carry = bitNum >= 10 ? 1 : 0) == 1)
					bitNum -= 10;
			}else
			{
				if((carry = bitNum <= -10 ? -1 : 0) == -1)
					bitNum += 10;
			}
			res[index] = '0' + bitNum;

			--index;
			--newRhsLen;
		}
	}
	else
	{///merge lhs
		while(newLhsLen > 0)
		{
			res[index] = carry + lhs[newLhsLen];
			bitNum = res[index] - '0';
			if(bitNum >= 0)
			{
				if((carry = bitNum >= 10 ? 1 : 0) == 1)
					bitNum -= 10;
			}else
			{
				if((carry = bitNum <= -10 ? -1 : 0) == -1)
					bitNum += 10;
			}
			res[index] = '0' + bitNum;

			--index;
			--newLhsLen;
		}
	}

	res[index] = '0' + abs(carry);//add carry
	int resultSymbol = 0;
	if(possitiveLhs == -1 && possitiveRhs == -1)
		resultSymbol = -1;
	else if(possitiveRhs == 0 && possitiveRhs == 0)
		resultSymbol = 0;
	else
	{
		if(carry >= 0) resultSymbol = 0;
		else resultSymbol = -1;
	}

	*resultLen = SIZE_MAX - index + (resultSymbol == 0 ? 0 : 1);
	char* result = (char*) malloc(*resultLen);
	if(!result) 
	{
		printf("unable to mallocate memory");
		free(newLhs);
		free(newRhs);
		return NULL;
	}
	memset(result, 0, *resultLen);	
	if(resultSymbol == -1)
		result[0] = '-';
	memcpy(result + 1, res + index, *resultLen);
	return result;
}

char* bigIntSub(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen)
{

	return NULL;
}

char* bigIntMultiple(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen)
{
	return NULL;

}

char* bigIntDevide(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen)
{

	return NULL;
}

char* bigIntMod(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen)
{
	return NULL;

}



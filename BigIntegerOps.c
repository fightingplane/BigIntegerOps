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
	//^[0]+ [-|+][0-9]+
	if(NULL == bigInt || length <= 0) return -1;
	//get the first non-zero position
	int intLen = bigInt[length - 1] == '\0' ? length - 1 : length;//only tailing '\0' is allowed

	int i = 0;
	for(; i < intLen; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i >= intLen) return 0; ///zero
	
	if(bigInt[i] == '-' || bigInt[i] == '+') ++i;
	if(i >= intLen) return 0; ///- || + treat as zero
	for(; i< intLen; ++i)
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
	int intLen = bigInt[length - 1] == '\0' ? length - 1 : length;//only tailing '\0' is allowed

	int i = 0;
	for( ; i < intLen; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i >= intLen) return 0; ///zero
	
	if(bigInt[i] == '-' || bigInt[i] == '+') ++i;

	if(i >= intLen) return 0; 
	////0000[-+]00000
	for( ; i < intLen; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i < intLen)
	   	return -1;
	else
	   	return 0;
}
	
char* bigIntAbs(const char* const bigInt, const int length, int* targetLength)
{
	//if bigInt is not tailing with '\0', manually add it
	if(0 != isInteger(bigInt, length)) 
	{
		*targetLength = 0;
		return NULL;
	}
	//return the pure integer part
	int intLen = bigInt[length - 1] == '\0' ? length - 1 : length;

	int i = 0;
	for(; i < intLen; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i >= intLen)
	{
		char* ret = (char*) malloc(2);
		if(ret == NULL)
		{
			printf("unable to allocate more memory");
			*targetLength = 0;
			return NULL;
		}
		ret[0] = '0';
		ret[1] = '\0';
		*targetLength = 2;
		return ret;
	} ///zero
	
	if(bigInt[i] == '-' || bigInt[i] == '+') ++i;
	if(i >= intLen) 
	{
		char* ret = (char*) malloc(2);
		if(NULL == ret)
		{
			printf("unable to allocate more memory");
			return NULL;
		}
		ret[0] = '0';
		ret[1] = '\0';
		*targetLength = 2;
		return ret;
	} ///- || + treat as zero;

	//since we have checked the sanity, just copy the numbers;
	*targetLength = intLen - i + 1;
	char* ret = (char*) malloc(*targetLength);
	memset(ret, 0, *targetLength);
	memcpy(ret, bigInt + i, *targetLength - 1);
	ret[*targetLength - 1] = '\0';//cool
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
	
	if(bigInt[0] != '-')
	{
		int i;
		int intLen = bigInt[length - 1] == '\0' ? length - 1 : length;
		
		for(i = 0; i < intLen; ++i)
		{
			if(bigInt[i] != '0')
				break;
		}

		if(bigInt[i] == '+' || (bigInt[i] >= '1' && bigInt[i] <= '9'))
			return 0;
	}

	return -1;
}

char* getOppositeNumber(const char* const bigInt, const int length, int* resultLen)
{
	if(isZero(bigInt, length) == 0)
	{
		char* result = (char*) malloc(2);
		if(result == NULL)
		{
			printf("unable to alloc more memory");
			*resultLen = 0;
			return NULL;
		}
		*resultLen = 2;
		result[0] = '0';
		result[1] = '\0';
	}

	int possitive = isPossitive(bigInt, length);
	int absLen = 0;
	char* absInt = bigIntAbs(bigInt, length, &absLen);
	if(possitive == 0)
	{
		char* result = (char*) malloc(absLen + 1);
		if(result == NULL)
		{	
			printf("unable to alloc more memory");
			*resultLen = 0;
			return NULL;
		}
		*resultLen = absLen + 1;
		result[0] = '-';
		memcpy(result + 1, bigInt, absLen);
		free(absInt);
		return result;
	}else
	{
		return absInt;
	}
}

char* bigIntAdd(const char* const lhs, const int lhsLength, const char* const rhs, const int rhsLength, int* resultLen)
{
	char res[SIZE_MAX] = {0};
	if(0 != isInteger(lhs, lhsLength) || 0 != isInteger(rhs, rhsLength))
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
		*resultLen = 0;
		return NULL;
	}

	int index = SIZE_MAX - 1;
	int carry = 0, bitNum = 0;
	int op = ((possitiveRhs == 0 && possitiveLhs == -1) || (possitiveLhs == 0 && possitiveRhs == -1)) ? -1 : 0;//-1 means minus, and 0 mean add

	newLhsLen -= 2;///considering tailing '\0'
	newRhsLen -= 2;

	while(index >= 0 && newLhsLen >= 0 && newRhsLen >= 0)
	{
		if(0 == op)
			res[index] = carry + newLhs[newLhsLen] + newRhs[newRhsLen] - '0';
		else
			res[index] = carry + newLhs[newLhsLen] - newRhs[newRhsLen] + '0';
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

	if(newRhsLen >= 0)
	{///merge rhs 
		while(newRhsLen >= 0)
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
		while(newLhsLen >= 0)
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

	*resultLen = SIZE_MAX - index + 1 + (resultSymbol == 0 ? 0 : 1);
	char* result = (char*) malloc(*resultLen);
	if(!result) 
	{
		printf("unable to mallocate memory");
		free(newLhs);
		free(newRhs);
		*resultLen = 0;
		return NULL;
	}
	memset(result, 0, *resultLen);	
	if(resultSymbol == -1)
	{
		result[0] = '-';
		memcpy(result + 1, res + index + 1, *resultLen - 1);
	}else
		memcpy(result, res + index + 1, *resultLen);
	result[*resultLen - 1] = '\0';
	return result;
}

char* bigIntSub(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen)
{
	if(0 != isInteger(lhs, lhsLength) || 0 != isInteger(rhs, rhsLength))
	{
		*resultLen = 0;
		return NULL;
	}

	int oppositeRhsLen = 0;
	char* oppositeRhs = getOppositeNumber(rhs, rhsLength, &oppositeRhsLen);
	if(NULL == oppositeRhs)
	{
		printf("failed to get opposite number of rhs[%s]", rhs);
		*resultLen = 0;
		return NULL;
	}

	char* result = bigIntAdd(lhs, lhsLength, oppositeRhs, oppositeRhsLen, resultLen);
	free(oppositeRhs);

	return result;
}

char* bigIntMutiTenPow(const char* const bigInt, const int length, int powN, int* resultLen)
{
	//assume the integer is ended with '\0'
	int targetLen = length + powN;
	char* result = (char*) malloc(targetLen);
	if(result == NULL)
	{
		printf("failed to allocate more memory");
		*resultLen = 0;
		return 0;
	}
	if(targetLen == length)//powN == 0
		memcpy(result, bigInt, length);
	else
	{
		memcpy(result, bigInt, length - 1);
		memset(result + length -1, '0', targetLen - length);
	    result[targetLen - 1] = '\0';	
	}
	
	*resultLen = targetLen;
	return result;
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



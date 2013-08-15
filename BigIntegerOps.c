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
	
char* getIntZero()
{
	char* ret = (char*) malloc(2);
	if(ret == NULL)
		return NULL;
	ret[0] = '0';
	ret[1] = '\0';
	return ret;
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

	int i = 0;
	for(; i < length; ++i)
	{
		if(bigInt[i] != '0')
			break;
	}

	if(i >= length)
	{
		*targetLength = 1;
		return getIntZero();
	} ///zero
	
	if(bigInt[i] == '-' || bigInt[i] == '+') ++i;
	if(i >= length) 
	{
		*targetLength = 1;
		return getIntZero();
	} ///- || + treat as zero;

	//since we have checked the sanity, just copy the numbers;
	*targetLength = length - i;
	char* ret = (char*) malloc(*targetLength + 1);//add an extra space for '\0'
	memset(ret, 0, *targetLength);
	memcpy(ret, bigInt + i, *targetLength);
	ret[*targetLength] = '\0';//cool
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
		{
			if(newLhsLength < newRhsLength)
				retVal = -1;
			else if(newLhsLength > newRhsLength)
				retVal = 1;
			else	
				retVal = strcmp(newLhs, newRhs);
		}
		else if(!possitiveA && !possitiveB)
		{
			if(newLhsLength < newRhsLength)
				retVal = 1;
			else if(newLhsLength > newRhsLength)
				retVal = -1;
			retVal = strcmp(newRhs, newLhs);
		}
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
		
		for(i = 0; i < length; ++i)
		{
			if(bigInt[i] != '0')
				break;
		}

		if(i >= length)
			return 0;//zero

		if(bigInt[i] == '+' || (bigInt[i] >= '1' && bigInt[i] <= '9'))
			return 0;
	}

	return -1;
}

char* bigIntCopy(const char* const bigInt, const int length, int* resultLen)
{
	*resultLen = 0;
	if(bigInt == NULL || length == 0) 
	{
		return NULL;
	}
	char* res = (char*) malloc(length +1);
	if(res == NULL)
	{
		return NULL;
	}
	memcpy(res, bigInt, length);
	res[length] = '\0';
	*resultLen = length;
	return res;
}

char* getOppositeNumber(const char* const bigInt, const int length, int* resultLen)
{
	if(isZero(bigInt, length) == 0)
	{
		*resultLen = 1;
		return getIntZero();
	}

	int possitive = isPossitive(bigInt, length);
	int absLen = 0;
	char* absInt = bigIntAbs(bigInt, length, &absLen);
	if(possitive == 0)
	{
		char* result = (char*) malloc(absLen + 2);
		if(result == NULL)
		{	
			printf("unable to alloc more memory");
			*resultLen = 0;
			return NULL;
		}
		*resultLen = absLen + 1;
		result[0] = '-';
		memcpy(result + 1, absInt, absLen);
		result[*resultLen] = '\0';
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

	--newLhsLen;
	--newRhsLen;

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
			if((carry = bitNum <= 0 ? -1 : 0) == -1)
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
			res[index] = carry + newRhs[newRhsLen];
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
			res[index] = carry + newLhs[newLhsLen];
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

	if(carry != 0)
		res[index--] = '0' + abs(carry);//add carry

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

	//find the first unzero index, trim the leading zeros
	while(index < SIZE_MAX -1 && (res[index] == '0' || res[index] == '\0'))
		++index;

	*resultLen = SIZE_MAX - index + (resultSymbol == 0 ? 0 : 1);//index catch up
	char* result = (char*) malloc(*resultLen + 1);
	if(!result) 
	{
		printf("unable to mallocate memory");
		free(newLhs);
		free(newRhs);
		*resultLen = 0;
		return NULL;
	}
	memset(result, 0, *resultLen + 1);	
	if(resultSymbol == -1)
	{
		result[0] = '-';
		memcpy(result + 1, res + index, *resultLen - 1);
	}else
		memcpy(result, res + index, *resultLen);
	result[*resultLen] = '\0';
	return result;
}

char* bigIntSub(const char* const lhs, const int lhsLength, const char* const rhs, const int rhsLength, int* resultLen)
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
	char* result = (char*) malloc(targetLen + 1);
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
		memcpy(result, bigInt, length);
		memset(result + length, '0', targetLen - length);
	}
	
	result[targetLen] = '\0';	
	*resultLen = targetLen;
	return result;
}

char* bigIntDevideTen(const char* const bigInt, const int length, int* resultLen)
{
	if(isZero(bigInt, length) == 0 || length <= 1)
	{
		*resultLen = 1;
		return getIntZero();
	}

	*resultLen = length - 1;
	char* result = (char*) malloc(*resultLen + 1);
	if(result == NULL)
	{
		*resultLen = 1;
		return NULL;
	}
	memcpy(result, bigInt, *resultLen);
	result[*resultLen] = '\0';
	return result;
}

char* bigIntMultipleN(const char* const bigInt, const int length, const int n, int* resultLen)
{
	if(n < 0 || n > 10)
	{
		*resultLen = 0;
	   	return NULL;
	}

	if(isZero(bigInt, length) == 0 || n == 0)
	{
		*resultLen = 1;
		return getIntZero();
	}
	
	char tmp[SIZE_MAX] = {0};
	int i = SIZE_MAX - 1;
	int index = length -1;
	int carry = 0;
	int test = 0;
	while(index >= 0 && i >= 0)
	{
		test = (bigInt[index] - '0') * n + carry;
		carry = test / 10;
		tmp[i] = '0' + test%10;

		--index;
		--i;
	}

	if(carry > 0)
		tmp[i--] = '0' + carry;

	*resultLen = SIZE_MAX - i - 1;
	char* result = (char*) malloc(*resultLen + 1);
	if(result == NULL)
	{
		*resultLen = 0;
		return NULL;
	}
	memcpy(result, tmp + i + 1, *resultLen);
	result[*resultLen] = '\0';
	return result;
}

char* bigIntMultiple(const char* const lhs, const int lhsLength, const char* const rhs, const int rhsLength, int* resultLen)
{
	if(isZero(lhs, lhsLength) == 0 || isZero(rhs, rhsLength) == 0)
	{
		*resultLen = 1;
		return getIntZero();
	}

	int possitiveLhs = isPossitive(lhs, lhsLength);
	int possitiveRhs = isPossitive(rhs, rhsLength);
	int resultPossitive = (possitiveLhs == 0 && possitiveRhs == 0) || (possitiveLhs == -1 && possitiveRhs == -1) ? 0 : -1; 

	int newLhsLen = 0;
	int newRhsLen = 0;
	char* absLhs = bigIntAbs(lhs, lhsLength, &newLhsLen);
	if(absLhs == NULL)
	{
		*resultLen = 0;
		return NULL;
	}
	char* absRhs = bigIntAbs(rhs, rhsLength, &newRhsLen);
	if(absRhs == NULL)
	{
		free(absLhs);
		*resultLen = 0;
		return NULL;
	}

	char* result = getIntZero();
	if(!result)
	{
		*resultLen = 0;
		return NULL;
	}
	*resultLen = 1;
	char* record[10];
	//int record
	int i = 0;
	for(; i<10; ++i)
		record[i] = NULL;

	int n = 0;
	int j = newRhsLen - 1;
	int retCode = 0;
	while(j >= 0)
	{
		n = absRhs[j] - '0';
		if(n >= 0 && n <= 9)
		{
			if(record[n] == NULL)
			{
				int tmpLength = 0;
				char* recordTmp = bigIntMultipleN(absLhs, newLhsLen, n, &tmpLength);
				if(recordTmp != NULL)
					record[n] = recordTmp;
				else
				{
					retCode = -1;
					break;//failed
				}
			}

			int length = 0;
			char* tmp = bigIntMutiTenPow(record[n], strlen(record[n]), newRhsLen - j - 1, &length);
			if(tmp != NULL)
			{
				char* tmpRes = bigIntAdd(result, *resultLen, tmp, length, resultLen);
				if(tmpRes != NULL)
				{
					free(result);
					result = tmpRes;
				}
				else
				{
					retCode = -1;
					break;
				}
			}
			else
			{
				retCode = -1;
				break;
			}

		}else
		{
			retCode = -1;
			break;
		}
		--j;
	}

	for(i = 0; i<10; ++i)
	{
		if(record[i] != NULL)
			free(record[i]);
	}
	if(retCode != 0)
	{
		if(result) free(result);
		result = NULL;
		*resultLen = 0;
	}

	
	if(result != NULL && resultPossitive == -1)
	{
		char* resultOpposite = getOppositeNumber(result, *resultLen, resultLen);
		if(resultOpposite)
		{
			free(result);
			result = resultOpposite;
		}else
		{
			free(result);
			*resultLen = 0;
			result = NULL;
		}
	}
	return result;
}

char* bigIntDevide(const char* const lhs, const int lhsLength, const char* const rhs, const int rhsLength, int* resultLen, char** modRes, int* modResLen)
{
	if(isZero(rhs, rhsLength) == 0)
	{
		//error, devide by zero
		*resultLen = 0;
		*modRes = NULL;
		*modResLen = 0;
		return NULL;
	}

	if(isZero(lhs, lhsLength) == 0)
	{
		*resultLen = 1;
		*modRes = getIntZero();
		*modResLen = 1;
		return getIntZero();
	}

	int possitiveLhs = isPossitive(lhs, lhsLength);
	int possitiveRhs = isPossitive(rhs, rhsLength);
	int resultPossitive = (possitiveLhs == 0 && possitiveRhs == 0) || (possitiveLhs == -1 && possitiveRhs == -1) ? 0 : -1; 
	int newLhsLen = 0;
	char* newLhs = bigIntAbs(lhs, lhsLength, &newLhsLen);
	
	if(newLhs == NULL || newLhsLen == 0)
	{
		ROCKY_SAFE_DELETE(newLhs);
		*resultLen = 0;
		*modRes = NULL;
		*modResLen = 0;
		return NULL;
	}
	
	int newRhsLen = 0;
	char* newRhs = bigIntAbs(rhs, rhsLength, &newRhsLen);
	if(newRhs == NULL || newRhsLen == 0)
	{
		ROCKY_SAFE_DELETE(newLhs);
		ROCKY_SAFE_DELETE(newRhs);
		*resultLen = 0;
		*modRes = NULL;
		*modResLen = 0;
		return NULL;
	}

	char* one = "1";
	if(bigIntCompare(newRhs, newRhsLen, one, strlen(one)) == 0)
	{
		*modResLen = 1;
		*modRes = getIntZero();
		//devid by 1, return lhs
		if(resultPossitive == 0)//possitive
			return bigIntCopy(newLhs, newLhsLen, resultLen);
		else
			return getOppositeNumber(newLhs, newLhsLen, resultLen);
	}

	//compare
	int compare = bigIntCompare(newLhs, newLhsLen, newRhs, newRhsLen);
	if(compare == 0)
	{
		*modResLen = 1;
		*modRes = getIntZero();
		char* tmp = (char*) malloc(2);
		tmp[0] = '1';
		tmp[1] = '\0';
		*resultLen = 1;
		if(resultPossitive == -1)
		{
			char* tmp2 = getOppositeNumber(tmp, strlen(tmp), resultLen);
			if(tmp2 != NULL)
			{
				ROCKY_SAFE_DELETE(tmp);
				tmp = tmp2;
			}
		}
		return tmp;
	}else if(compare < 0)
	{
		*modRes = bigIntCopy(newLhs, newLhsLen, modResLen);
		if(*modRes == NULL)
		{
			//TODO error
		}	
		*resultLen = 1;
		return getIntZero();
	}else
	{
		/* main process
		 * 12345/12 = 1000 + 20 + 8 ...9
		 * = 1028 ...9
		 *which can extract to 
		 *  12345 - 1000*12 = 345
		 *  345 - 10*12*2 = 105
		 *  105 - 12*8 = 9
		 * ***/

		int tmpLen = 0;
		char* tmp = bigIntMutiTenPow(newRhs, newRhsLen, 1, &tmpLen);
		int count = 1;
		while(tmp!= NULL && bigIntCompare(newLhs, newLhsLen, tmp, tmpLen) >= 0)
		{
			char* tmp2 = bigIntMutiTenPow(tmp, tmpLen, 1, &tmpLen);
			ROCKY_SAFE_DELETE(tmp);
			tmp = tmp2;
			++count;
		}
		
		char* result = getIntZero();//save the result of division
		*resultLen = 1;//save the result length
		int tmpResLen = 0;//base result unit
		char* tmpRes = bigIntMutiTenPow("1", 1, count, &tmpResLen);
		while(--count >= 0)
		{
			char* tmp2 = bigIntDevideTen(tmp, tmpLen, &tmpLen);
			if(tmp2 == NULL)
				break;
			ROCKY_SAFE_DELETE(tmp);
			tmp = tmp2;

			char* tmpRes2 = bigIntDevideTen(tmpRes, tmpResLen, &tmpResLen);
			if(tmpRes2 == NULL)
				break;
			ROCKY_SAFE_DELETE(tmpRes);
			tmpRes = tmpRes2;
			
			while(bigIntCompare(newLhs, newLhsLen, tmp, tmpLen) > 0)
			{
				int tmpNewLhsLen = 0;
				char* tmpNewLhs = bigIntSub(newLhs, newLhsLen, tmp, tmpLen, &tmpNewLhsLen);
				if(tmpNewLhs == NULL)
					break;
				ROCKY_SAFE_DELETE(newLhs);
				newLhs = tmpNewLhs;
				newLhsLen = tmpNewLhsLen;
				
				int tmpResultLen = 0;
				char* tmpResult = bigIntAdd(result, *resultLen, tmpRes, tmpResLen, &tmpResultLen);
				if(tmpResult == NULL)
					break;
				ROCKY_SAFE_DELETE(result);
				result = tmpResult;
				*resultLen = tmpResultLen;
			}
		}
		if(count >= 0)//error occurred
		{
			*resultLen = 0;
			*modResLen = 0;
			*modRes = NULL;
			return NULL;
		}else
		{
			if(isZero(newLhs, newLhsLen) == 0)
			{
				*modResLen = 1;
				*modRes = getIntZero();
			}else
			{
				*modRes = bigIntCopy(newLhs, newLhsLen, modResLen);
			}
		}
		if(resultPossitive == -1)
		{
			char* tmp = getOppositeNumber(result, *resultLen, resultLen);
			ROCKY_SAFE_DELETE(result);
			result = tmp;
		}
		return result;
	}

	return NULL;
}





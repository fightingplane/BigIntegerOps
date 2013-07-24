#ifndef __BIG_INTEGER_OPERATIONS_H__
#define __BIG_INTEGER_OPERATIONS_H__
/**Author: Wang XiaoYuan*/
#define max(a,b) (a) >= (b) ? (a) : (b)
/**check if the predected integer is a integer or not*/
int isInteger(const char* const bigInt, const int length);

/**return if the big integer is a nagtive or possitive*/
int isPossitive(const char* const bigInt, const int length);

/**check if the big integer is zero*/
int isZero(const char* const bigInt, const int length);

/**return the pure integer without -/+ */
char* bigIntAbs(const char* const bigInt, const int length, int* targetLength);

/**compares two big integers, and return the result
 * < -1
 * = 0
 * > 1
 * */
int bigIntCompare(const char* const lhs, const int lhsLength, const char* const rhs, const int rhsLength);

/**
 * return two big integers' add result, and put result length into resultLen
 * */
char* bigIntAdd(const char* const lhs, const int lhsLength, const char* const rhs, const int rhsLength, int* resultLen);

/**
 * return two big integers' substraction result, and put result length into resultLen
 * */
char* bigIntSub(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen);

/**
 * return two big integers' multiple result, and put result length into resultLen
 * */
char* bigIntMultiple(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen);

/**
 * return two big integers' devision result, and put result length into resultLen
 * */
char* bigIntDevide(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen);

/**
 * return two big integers' mod result, and put result length into resultLen
 * */
char* bigIntMod(char* lhs, int lhsLength, char* rhs, int rhsLength, int* resultLen);

#endif

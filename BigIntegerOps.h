#ifndef __BIG_INTEGER_OPERATIONS_H__
#define __BIG_INTEGER_OPERATIONS_H__
/**Author: Wang XiaoYuan*/
#define max(a,b) (a) >= (b) ? (a) : (b)
/**check if the predicted string is a integer or not*/
int isInteger(const char* const bigInt, const int length);

/**return if the big integer is a nagtive or possitive
 * @warn the input should be a valid integer*/
int isPossitive(const char* const bigInt, const int length);

/**check if the big integer is zero*/
int isZero(const char* const bigInt, const int length);

/**Get opposite number of an integer, e.g. 1 -> -1
 * @warn the number should be valid*/
char* getOppositeNumber(const char* const bigInt, const int length, int* targetLength);

/**return the pure integer without -/+ 
 * @warn assume the input integer should be a valid integer*/
char* bigIntAbs(const char* const bigInt, const int length, int* targetLength);

/**retrun the integer * 10^n
 * @warn assume the input integer is valid*/
char* bigIntMutiTenPow(const char* const bigInt, const int length, int powN, int* resultLen);
/**compares two big integers, and return the result
 * < -1
 * = 0
 * > 1
 *
 * @warn assume the two operators are valid */
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

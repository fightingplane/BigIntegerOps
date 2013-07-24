cmake_minimum_required (VERSION 2.8)
project (BigInteger)

#The version number
set (BigInteger_VERSION_MAJOR 0)
set (BigInteger_VERSION_MINOR 9)

SET (BigIntegerSrc main.c BigIntegerOps.c)
add_executable(BigInteger ${BigIntegerSrc})




BigIntegerOps
=============

big integer's operations, such as add, sub, mult, divid

Software requirement:
	CMake--a make tool instead for make
	CHECK--test frame work
	Git---clone repo from github

Build:
	cd $PROJDIR
	mkdir build
	cd build
	cmake ../
	make

For Test:
	Go into build dir, and run ./TestBigInteger
You can add test cases in the $PROJECT/test dir

For real data test:
	run ./BigInteger after build
input 3 lines:
	operator1
	op
	operator2
E.G
	1
	+
	1
and out put 2 line:
	time calculated in seconds
	result
e.g.
	Run Time:0.000000(seconds)
    Result:2

You can write your test data in a "input.txt"
and run 
./BigInteger <input.txt >out.txt
and check the result in out.txt

For more info, please contact juster.wang@gmail.com


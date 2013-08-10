#include <stdlib.h>
#include <check.h>
#include "../BigIntegerOps.h"

void setup(void)
{}

void teardown(void)
{
}

START_TEST(test_isInteger)
{
	char* a = "12";
	char* b = "+1";
	char* c = "00";
	char* d = "-1";
	fail_unless(isInteger(a, 2) == 0, "12 should be an interger");
	fail_unless(isInteger(b, 2) == 0, "+1 should be an interger");
	fail_unless(isInteger(c, 2) == 0, "00 should be an interger");
	fail_unless(isInteger(d, 2) == 0, "-1 should be an interger");
}
END_TEST

START_TEST(test_integerMutiTenPow)
{
	char* a = "12";
	char* b = "-1";

	int len = 0;
	char* res1 = bigIntMutiTenPow(a, strlen(a), 2, &len);
	fail_unless(res1 != NULL, "result should not null");
	fail_unless(strcmp(res1, "1200") == 0, "result should == 1200");
	free(res1);

	char* res2 = bigIntMutiTenPow(b, strlen(b), 2, &len);
	fail_unless(res2 != NULL, "result should == -100");
	fail_unless(strcmp(res2, "-100") == 0, "result should == -100");
	free(res2);

	char* res3 = bigIntMutiTenPow(a, strlen(b), 0, &len);
	fail_unless(res3 != NULL, "result should == 12");
	fail_unless(strcmp(res3, "12") == 0, "result should == 12");
	free(res3);
}
END_TEST

START_TEST(test_integerMutiN)
{
	char *a = "12";
	int len = 0;
	char* res1 = bigIntMultipleN(a, strlen(a), 9, &len);
	fail_unless(res1 != NULL, "result should not null");
	fail_unless(strcmp(res1, "108") == 0, "result should == 108");
	free(res1);
	
	char* res2 = bigIntMultipleN(a, strlen(a), 0, &len);
	fail_unless(res2 != NULL, "result should not null");
	fail_unless(strcmp(res2, "0") == 0, "result should == 0");
	free(res2);

}
END_TEST

START_TEST(test_integerMuti)
{
	char* a = "12";
	char* b = "12";
	char* c = "0";
	int len = 0;
	char* res1 = bigIntMultiple(a, strlen(a), b, strlen(b), &len);
	fail_unless(res1 != NULL, "result should not null");
	fail_unless(strcmp(res1, "144") == 0, "result should == 144");
	free(res1);
	
	char* res2 = bigIntMultiple(a, strlen(a), c, strlen(c), &len);
	fail_unless(res2 != NULL, "result should not null");
	fail_unless(strcmp(res2, "0") == 0, "result should == 0");
	free(res2);
}
END_TEST

START_TEST(test_integerDivide)
{
	char* a = "12345";
	char* b = "12";
	char* c = NULL;
	int len = 0;
	int modLen = 0;
	char* res1 = bigIntDevide(a, strlen(a), b, strlen(b), &len, &c, &modLen);
	fail_unless(res1 != NULL, "result should not null");
	fail_unless(strcmp(res1, "1028") == 0, "result should == 1028");
	fail_unless(c != NULL, "mod result should not null");
	fail_unless(strcmp(c, "9")== 0, "mod result should == 9");
	free(res1);
	free(c);
}
END_TEST

Suite* bigInteger_suit(void)
{
	Suite *s = suite_create("Test_BigInteger");

	/* core test cases*/
	TCase *tc_core = tcase_create("Core");
	tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_isInteger);

	TCase *tc_calc = tcase_create("Calc");
	tcase_add_test(tc_calc, test_integerMutiTenPow);
	tcase_add_test(tc_calc, test_integerMutiN);
	tcase_add_test(tc_calc, test_integerMuti);
	tcase_add_test(tc_calc, test_integerDivide);

	suite_add_tcase(s, tc_core);
	suite_add_tcase(s, tc_calc);

	return s;
}

int main(void)
{
	int number_failed = 0;
	Suite*s = bigInteger_suit();
	SRunner* sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr); 
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}



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
	char a[2] = {'1','2'};
	char b[2] = {'+','1'};
	char c[2] = {'0','0'};
	char d[2] = {'-', '1'};
	fail_unless(isInteger(a, 2) == 0, "12 should be an interger");
	fail_unless(isInteger(b, 2) == 0, "+1 should be an interger");
	fail_unless(isInteger(c, 2) == 0, "00 should be an interger");
	fail_unless(isInteger(d, 2) == 0, "-1 should be an interger");
}
END_TEST

Suite* bigInteger_suit(void)
{
	Suite *s = suite_create("Test_BigInteger");

	/* core test cases*/
	TCase *tc_core = tcase_create("Core");
	tcase_add_checked_fixture(tc_core, setup, teardown);
	tcase_add_test(tc_core, test_isInteger);

	suite_add_tcase(s, tc_core);

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



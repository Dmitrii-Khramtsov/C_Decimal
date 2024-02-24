#include "s21_decimal_tests.h"

START_TEST(int2dec_1) {
  // Maximum negative number
  int input = -2147483647;
  s21_decimal decimalNum = {{0, 0, 0, 0}};
  int status = s21_from_int_to_decimal(input, &decimalNum);
  ck_assert_int_eq(status, CONVERSION_OK);
  ck_assert_int_eq(decimalNum.bits[0], 0x7FFFFFFF);
  ck_assert_int_eq(decimalNum.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(int2dec_2) {
  // Maximum positive number
  int input = 0x7FFFFFFF;
  s21_decimal decimalNum = {{0, 0, 0, 0}};
  int status = s21_from_int_to_decimal(input, &decimalNum);
  ck_assert_int_eq(status, CONVERSION_OK);
  ck_assert_int_eq(decimalNum.bits[0], 0x7FFFFFFF);
  ck_assert_int_eq(decimalNum.bits[3], 0);
}
END_TEST

START_TEST(int2dec_3) {
  // Maximum positive number with a NULL pointer for decimalNum
  int input = 0x7FFFFFFF;
  s21_decimal *decimalNum = NULL;
  int status = s21_from_int_to_decimal(input, decimalNum);
  ck_assert_int_eq(status, CONVERSION_ERROR);
}
END_TEST

Suite *test_int2dec() {
  Suite *test_set = suite_create("s21_int2dec");
  TCase *test_group = tcase_create("s21_int2dec_test_group");

  tcase_add_test(test_group, int2dec_1);
  tcase_add_test(test_group, int2dec_2);
  tcase_add_test(test_group, int2dec_3);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

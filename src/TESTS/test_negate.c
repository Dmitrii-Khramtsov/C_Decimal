#include "s21_decimal_tests.h"

START_TEST(negate_1) {
  // Checking a negative number
  s21_decimal value1 = {{1, 0, 0, SIGN_MASK}};
  s21_decimal result1;
  int status1 = s21_negate(value1, &result1);
  ck_assert_int_eq(status1, 0);
  ck_assert_int_eq(result1.bits[0], 1);
  ck_assert_int_eq(result1.bits[1], 0);
  ck_assert_int_eq(result1.bits[2], 0);
  ck_assert_int_eq(result1.bits[3], 0);
}
END_TEST

START_TEST(negate_2) {
  // Checking a positive number
  s21_decimal value2 = {{1, 0, 0, 0}};
  s21_decimal result2;
  int status2 = s21_negate(value2, &result2);
  ck_assert_int_eq(status2, 0);
  ck_assert_int_eq(result2.bits[0], 1);
  ck_assert_int_eq(result2.bits[1], 0);
  ck_assert_int_eq(result2.bits[2], 0);
  ck_assert_int_eq(result2.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(negate_3) {
  // result = NULL
  s21_decimal value = {{0, 123456789, 0, 0x000A0000}};
  s21_decimal *result = NULL;
  int status = s21_negate(value, result);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

Suite *test_negate() {
  Suite *test_set = suite_create("s21_negate");
  TCase *test_group = tcase_create("s21_negate_test_group");

  tcase_add_test(test_group, negate_1);
  tcase_add_test(test_group, negate_2);
  tcase_add_test(test_group, negate_3);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

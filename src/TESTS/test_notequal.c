#include "s21_decimal_tests.h"

START_TEST(is_not_equal1) {
  // Both numbers are the same; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_not_equal2) {
  // The first number is greater than the second; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal3) {
  // The first number is less than the second; positive
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal4) {
  // The first number is less than the second by mantissa; negative; the first
  // is zero
  s21_decimal first = {{0, 0, 0, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal5) {
  // The first number is greater than the second number by mantissa; negative;
  // the second number is zero
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0, 0, SIGN_MASK}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal6) {
  // The first number is less than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal7) {
  // The first number is greater than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal8) {
  // The first number is less than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal9) {
  // The first number is greater than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_not_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_not_equal10) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_not_equal11) {
  s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_not_equal12) {
  s21_decimal value_1 = {{0, 0, 0, 80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *test_notequal() {
  Suite *test_set = suite_create("s21_notequal");
  TCase *test_group = tcase_create("s21_notequal_test_group");

  tcase_add_test(test_group, is_not_equal1);
  tcase_add_test(test_group, is_not_equal2);
  tcase_add_test(test_group, is_not_equal3);
  tcase_add_test(test_group, is_not_equal4);
  tcase_add_test(test_group, is_not_equal5);
  tcase_add_test(test_group, is_not_equal6);
  tcase_add_test(test_group, is_not_equal7);
  tcase_add_test(test_group, is_not_equal8);
  tcase_add_test(test_group, is_not_equal9);
  tcase_add_test(test_group, is_not_equal10);
  tcase_add_test(test_group, is_not_equal11);
  tcase_add_test(test_group, is_not_equal12);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

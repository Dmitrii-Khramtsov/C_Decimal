#include "s21_decimal_tests.h"

START_TEST(is_equal1) {
  // Both numbers are equal; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_equal2) {
  // First number is greater than the second; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal3) {
  // First number is less than the second; positive
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal4) {
  // First number is less than the second by mantissa; negative; first is zero
  s21_decimal first = {{0, 0, 0, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal5) {
  // First number is greater than the second by mantissa; negative; second is
  // zero
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0, 0, SIGN_MASK}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal6) {
  // First number is less than the second by mantissa; negative
  s21_decimal first = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal7) {
  // First number is greater than the second by mantissa; negative
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal8) {
  // First number is less than the second by mantissa; negative
  s21_decimal first = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal9) {
  // First number is greater than the second by mantissa; negative
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal10) {
  // First number is 1.2345, second number is 1.23
  s21_decimal first = {{0, 0, 0x00003039, 0x04 >> 16}};
  s21_decimal second = {{0, 0, 0x0000007B, 0x02 >> 16}};
  int status = s21_is_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_equal11) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_equal12) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0x00010000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *test_equal() {
  Suite *test_set = suite_create("s21_equal");
  TCase *test_group = tcase_create("s21_equal_test_group");

  tcase_add_test(test_group, is_equal1);
  tcase_add_test(test_group, is_equal2);
  tcase_add_test(test_group, is_equal3);
  tcase_add_test(test_group, is_equal4);
  tcase_add_test(test_group, is_equal5);
  tcase_add_test(test_group, is_equal6);
  tcase_add_test(test_group, is_equal7);
  tcase_add_test(test_group, is_equal8);
  tcase_add_test(test_group, is_equal9);
  tcase_add_test(test_group, is_equal10);
  tcase_add_test(test_group, is_equal11);
  tcase_add_test(test_group, is_equal12);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

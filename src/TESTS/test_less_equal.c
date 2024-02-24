#include "s21_decimal_tests.h"

START_TEST(is_less_or_equal1) {
  // Both numbers are equal; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less_or_equal2) {
  // First number is greater than the second; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less_or_equal3) {
  // First number is less than the second; positive
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less_or_equal4) {
  // First number is less than the second by mantissa; negative; first is zero
  s21_decimal first = {{0, 0, 0, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less_or_equal5) {
  // First number is greater than the second by mantissa; negative; second is
  // zero
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0, 0, SIGN_MASK}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less_or_equal6) {
  // First number is less than the second by mantissa; negative
  s21_decimal first = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less_or_equal7) {
  // First number is greater than the second by mantissa; negative
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less_or_equal8) {
  // First number is less than the second by mantissa; negative
  s21_decimal first = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less_or_equal9) {
  // First number is greater than the second by mantissa; negative
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_less_or_equal(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less_or_equal10) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less_or_equal11) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_less_or_equal12) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less_or_equal13) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less_or_equal14) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x00020000}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less_or_equal15) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *test_less_equal() {
  Suite *test_set = suite_create("s21_less_equal");
  TCase *test_group = tcase_create("s21_less_equal_test_group");

  tcase_add_test(test_group, is_less_or_equal1);
  tcase_add_test(test_group, is_less_or_equal2);
  tcase_add_test(test_group, is_less_or_equal3);
  tcase_add_test(test_group, is_less_or_equal4);
  tcase_add_test(test_group, is_less_or_equal5);
  tcase_add_test(test_group, is_less_or_equal6);
  tcase_add_test(test_group, is_less_or_equal7);
  tcase_add_test(test_group, is_less_or_equal8);
  tcase_add_test(test_group, is_less_or_equal9);
  tcase_add_test(test_group, is_less_or_equal10);
  tcase_add_test(test_group, is_less_or_equal11);
  tcase_add_test(test_group, is_less_or_equal12);
  tcase_add_test(test_group, is_less_or_equal13);
  tcase_add_test(test_group, is_less_or_equal14);
  tcase_add_test(test_group, is_less_or_equal15);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

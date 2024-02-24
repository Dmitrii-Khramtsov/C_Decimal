#include "s21_decimal_tests.h"

START_TEST(is_less1) {
  // Both numbers are the same; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less2) {
  // Первое число больше второго; положительные
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less3) {
  // The first number is greater than the second; positive
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less4) {
  // The first number is less than the second by mantissa; negative; the first
  // is zero
  s21_decimal first = {{0, 0, 0, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less5) {
  // The first number is greater than the second number by mantissa; negative;
  // the second number is zero
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0, 0, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less6) {
  // The first number is less than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less7) {
  // The first number is less than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less8) {
  // The first number is less than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less9) {
  // The first number is less than the second number by mantissa; negative
  // numbers
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less10) {
  // The first number is greater in sign than the second
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less11) {
  // The first number is less than the second by sign
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less12) {
  // The first number is exponentially smaller than the second
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less13) {
  // The first number is exponentially larger than the second
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less14) {
  // First number is greater - second bite is empty
  s21_decimal first = {{123, 0, 123, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less15) {
  // First number is greater - only third bite is not empty
  s21_decimal first = {{0, 0, 123, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less16) {
  // First number is greater - only second bite is not empty
  s21_decimal first = {{0, 0xE3FF83B3, 0, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less17) {
  // First number is greater - first bite is empty
  s21_decimal first = {{0, 0xE3FF83B3, 0x97, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less18) {
  // -5124 < -5123 = true
  s21_decimal first = {{0x1404, 0, 0, SIGN_MASK}};
  s21_decimal second = {{0x1403, 0, 0, SIGN_MASK}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less19) {
  // 0 < 5123 = true
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0x1403, 0, 0, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_less20) {
  // 5123 < 5123 = false
  s21_decimal first = {{0x1403, 0, 0, 0}};
  s21_decimal second = {{0x1403, 0, 0, 0}};
  int status = s21_is_less(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_less21) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less22) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_less23) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less24) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, SIGN_MASK}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less25) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_less26) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x00020000}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *test_less() {
  Suite *test_set = suite_create("s21_less");
  TCase *test_group = tcase_create("s21_less_test_group");

  tcase_add_test(test_group, is_less1);
  tcase_add_test(test_group, is_less2);
  tcase_add_test(test_group, is_less3);
  tcase_add_test(test_group, is_less4);
  tcase_add_test(test_group, is_less5);
  tcase_add_test(test_group, is_less6);
  tcase_add_test(test_group, is_less7);
  tcase_add_test(test_group, is_less8);
  tcase_add_test(test_group, is_less9);
  tcase_add_test(test_group, is_less10);
  tcase_add_test(test_group, is_less11);
  tcase_add_test(test_group, is_less12);
  tcase_add_test(test_group, is_less13);
  tcase_add_test(test_group, is_less14);
  tcase_add_test(test_group, is_less15);
  tcase_add_test(test_group, is_less16);
  tcase_add_test(test_group, is_less17);
  tcase_add_test(test_group, is_less18);
  tcase_add_test(test_group, is_less19);
  tcase_add_test(test_group, is_less20);
  tcase_add_test(test_group, is_less21);
  tcase_add_test(test_group, is_less22);
  tcase_add_test(test_group, is_less23);
  tcase_add_test(test_group, is_less24);
  tcase_add_test(test_group, is_less25);
  tcase_add_test(test_group, is_less26);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

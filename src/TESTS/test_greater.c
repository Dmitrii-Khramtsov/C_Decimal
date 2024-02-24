#include "s21_decimal_tests.h"

START_TEST(is_greater1) {
  // Both numbers are equal; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_greater2) {
  // First number is greater than the second; positive
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater3) {
  // First number is less than the second; positive
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_greater4) {
  // First number is less than the second by mantissa; negative; first is zero
  s21_decimal first = {{0, 0, 0, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater5) {
  // First number is greater than the second by mantissa; negative; second is
  // zero
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0, 0, SIGN_MASK}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_greater6) {
  // First number is less than the second by mantissa; negative
  s21_decimal first = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater7) {
  // First number is greater than the second by mantissa; negative
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_greater8) {
  // First number is less than the second by mantissa; negative
  s21_decimal first = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater9) {
  // First number is greater than the second by mantissa; negative
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0xAAAAAAAA, 0xAAAAAAAA, SIGN_MASK}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_greater10) {
  // First number is greater than the second by sign
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater11) {
  // First number is less than the second by sign
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_greater12) {
  // First number is less than the second by exponent
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater13) {
  // First number is greater than the second by exponent
  s21_decimal first = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal second = {{0, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, FALSE);
}
END_TEST

START_TEST(is_greater14) {
  // First number is greater - second bite is empty
  s21_decimal first = {{123, 0, 123, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater15) {
  // First number is greater - only third bite is not empty
  s21_decimal first = {{0, 0, 123, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater16) {
  // First number is greater - only second bite is not empty
  s21_decimal first = {{0, 0xE3FF83B3, 0, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater17) {
  // First number is greater - first bite is empty
  s21_decimal first = {{0, 0xE3FF83B3, 0x97, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater18) {
  // First number is greater - first bite in first num is smaller
  s21_decimal first = {{0x97, 0xE3FF83B3, 0x97, 0}};
  s21_decimal second = {{0xE3FF83B3, 0x97, 0, 0}};
  int status = s21_is_greater(first, second);
  ck_assert_int_eq(status, TRUE);
}
END_TEST

START_TEST(is_greater19) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater20) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater21) {
  int num1 = -3;
  int num2 = 3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater22) {
  float num1 = -3.232446546;
  float num2 = -3.2;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater23) {
  float num1 = -345.232446546;
  float num2 = -3.2;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_greater25) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal second_decimal = {{0, 0, 0, 0}};
  int A = 5123;
  int B = -5123;
  s21_from_int_to_decimal(A, &decimal);
  s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(0, s21_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater26) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal second_decimal = {{0, 0, 0, 0}};
  int A = -5123;
  int B = 5123;
  s21_from_int_to_decimal(A, &decimal);
  s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(1, s21_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater27) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_decimal second_decimal = {{0, 0, 0, 0}};
  int A = 0;
  int B = 5123;
  s21_from_int_to_decimal(A, &decimal);
  s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(0, s21_is_greater(decimal, second_decimal));
}
END_TEST

START_TEST(is_greater28) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater29) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(is_greater30) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater31) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, SIGN_MASK}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater32) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0x000A0000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(is_greater33) {
  s21_decimal value_1 = {{234, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0x000A0000}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *test_greater() {
  Suite *test_set = suite_create("s21_greater");
  TCase *test_group = tcase_create("s21_greater_test_group");

  tcase_add_test(test_group, is_greater1);
  tcase_add_test(test_group, is_greater2);
  tcase_add_test(test_group, is_greater3);
  tcase_add_test(test_group, is_greater4);
  tcase_add_test(test_group, is_greater5);
  tcase_add_test(test_group, is_greater6);
  tcase_add_test(test_group, is_greater7);
  tcase_add_test(test_group, is_greater8);
  tcase_add_test(test_group, is_greater9);
  tcase_add_test(test_group, is_greater10);
  tcase_add_test(test_group, is_greater11);
  tcase_add_test(test_group, is_greater12);
  tcase_add_test(test_group, is_greater13);
  tcase_add_test(test_group, is_greater14);
  tcase_add_test(test_group, is_greater15);
  tcase_add_test(test_group, is_greater16);
  tcase_add_test(test_group, is_greater17);
  tcase_add_test(test_group, is_greater18);
  tcase_add_test(test_group, is_greater19);
  tcase_add_test(test_group, is_greater20);
  tcase_add_test(test_group, is_greater21);
  tcase_add_test(test_group, is_greater22);
  tcase_add_test(test_group, is_greater23);
  tcase_add_test(test_group, is_greater25);
  tcase_add_test(test_group, is_greater26);
  tcase_add_test(test_group, is_greater27);
  tcase_add_test(test_group, is_greater28);
  tcase_add_test(test_group, is_greater29);
  tcase_add_test(test_group, is_greater30);
  tcase_add_test(test_group, is_greater31);
  tcase_add_test(test_group, is_greater32);
  tcase_add_test(test_group, is_greater33);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

#include "s21_decimal_tests.h"

START_TEST(dec2int_1) {
  // Bit 0 contains the maximum int32 number; negative
  s21_decimal inputDecimal = {{0x7FFFFFFF, 0, 0, SIGN_MASK}};
  int output = 0;
  int status = s21_from_decimal_to_int(inputDecimal, &output);
  ck_assert_int_eq(status, CONVERSION_OK);
  ck_assert_int_eq(output, -2147483647);
}
END_TEST

START_TEST(dec2int_2) {
  // Bit 0 is entirely occupied, and the number is positiv
  s21_decimal inputDecimal = {{0xFFFFFFFF, 0, 0, 0}};
  int output = 0;
  int status = s21_from_decimal_to_int(inputDecimal, &output);
  ck_assert_int_eq(status, CONVERSION_ERROR);
  ck_assert_int_eq(output, 0);
}
END_TEST

START_TEST(dec2int_3) {
  // Bit 0 is entirely occupied
  s21_decimal inputDecimal = {{0xFFFFFFFF, 0, 0, 0}};
  int output = 0;
  int status = s21_from_decimal_to_int(inputDecimal, &output);
  ck_assert_int_eq(status, CONVERSION_ERROR);
  ck_assert_int_eq(output, 0);
}
END_TEST

START_TEST(dec2int_4) {
  // Value is 4913564.8
  s21_decimal value = {{49135648, 0, 0, 0x80010000}};
  int output = 0;
  int return_value = s21_from_decimal_to_int(value, &output);
  ck_assert_int_eq(return_value, CONVERSION_OK);
  ck_assert_int_eq(output, -4913564);
}
END_TEST

START_TEST(dec2int_5) {
  // Value is greater than int32
  s21_decimal value = {{2, 3, 0, 0}};
  int output = 0;
  int return_value = s21_from_decimal_to_int(value, &output);
  ck_assert_int_eq(return_value, CONVERSION_ERROR);
  ck_assert_int_eq(output, 0);
}
END_TEST

START_TEST(dec2int_6) {
  // Value is 7,922,816,251,426,433,759,343,759,354,395
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C << 16}};
  int output = 0;
  int return_value = s21_from_decimal_to_int(value, &output);
  ck_assert_int_eq(return_value, CONVERSION_OK);
  ck_assert_int_eq(output, 7);
}
END_TEST

START_TEST(dec2int_7) {
  // Check the behavior of the function with a NULL pointer for the result
  // variable. The function is expected to return CONVERSION_ERROR.
  s21_decimal inputDecimal = {{0, 0, 0, 0}};
  int *output = NULL;
  int status = s21_from_decimal_to_int(inputDecimal, output);
  ck_assert_int_eq(status, CONVERSION_ERROR);
}
END_TEST

START_TEST(dec2int_8) {
  // Check the behavior of the function with a number that does not fit into 32
  // bits. The function is expected to return CONVERSION_ERROR.
  s21_decimal inputDecimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int output = 0;
  int status = s21_from_decimal_to_int(inputDecimal, &output);
  ck_assert_int_eq(status, CONVERSION_ERROR);
}
END_TEST

START_TEST(dec2int_9) {
  // Exponent in decimal > 28
  s21_decimal inputDecimal = {{0, 0, 0, 0x00FF0000}};
  int output = 0;
  int status = s21_from_decimal_to_int(inputDecimal, &output);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

Suite *test_dec2int() {
  Suite *test_set = suite_create("s21_dec2int");
  TCase *test_group = tcase_create("s21_dec2int_test_group");

  tcase_add_test(test_group, dec2int_1);
  tcase_add_test(test_group, dec2int_2);
  tcase_add_test(test_group, dec2int_3);
  tcase_add_test(test_group, dec2int_4);
  tcase_add_test(test_group, dec2int_5);
  tcase_add_test(test_group, dec2int_6);
  tcase_add_test(test_group, dec2int_7);
  tcase_add_test(test_group, dec2int_8);
  tcase_add_test(test_group, dec2int_9);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

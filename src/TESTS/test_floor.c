#include "s21_decimal_tests.h"

START_TEST(floor1) {
  // Rounding a negative number -2.2 = -3
  s21_decimal value = {{22, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor2) {
  // Max positive number - edge cases - integer number
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor3) {
  // Max negative number - edge cases - integer negative number
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor4) {
  // Rounding a positive number 2.86 = 2
  s21_decimal value = {{286, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor5) {
  // result = NULL
  s21_decimal value = {{0, 43, 342874, 0x000A0000}};
  s21_decimal *result = NULL;
  int status = s21_floor(value, result);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(floor6) {
  // Max positive number - maximum scale
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 7);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor7) {
  // Max negative number is the maximum scale
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor8) {
  // 0 -> 0
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor9) {
  // Negative zero 0 -> 0
  s21_decimal value = {{0, 0, 0, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor10) {
  // 0.5 -> 0
  s21_decimal value = {{5, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor11) {
  // Very small positive number 1e-28 -> 0
  // 0.0000000000000000000000000001
  s21_decimal value = {{1, 0, 0, 0x001C0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor12) {
  // Very small negative number 1e-28 -> 0
  // -0.0000000000000000000000000001
  s21_decimal value = {{1, 0, 0, 0x801C0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor13) {
  // Checking the metadata of a positive number
  // 15.0 -> 15
  s21_decimal value = {{150, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor14) {
  // Checking the metadata of a negative number
  // -15.0 -> -15
  s21_decimal value = {{150, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor15) {
  // A very large number with a large number of decimal places
  // 9876543210.123456789
  s21_decimal value = {{0xB0347115, 0x891087B8, 0, 0x00090000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0x4CB016EA);
  ck_assert_int_eq(result.bits[1], 0x2);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor16) {
  // Only the fractional part is present, 0.123456789 -> 0
  s21_decimal value = {{123456789, 0, 0, 0x00090000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor17) {
  // The number is -1 -> -1
  s21_decimal value = {{1, 0, 0, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor18) {
  // -0.9999999 -> -1
  s21_decimal value = {{9999999, 0, 0, 0x80070000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(floor19) {
  // Rounding a positive number 15.550 -> 15
  s21_decimal value = {{15550, 0, 0, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor20) {
  // Rounding a positive number 155.50 -> 155
  s21_decimal value = {{15550, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 155);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor21) {
  // Rounding of 16 (2^4) -> 16
  // Representation of 16.0 with one decimal place
  s21_decimal value = {{160, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 16);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(floor22) {
  // Rounding 16.25 (2^4 + 2^-2) -> 16
  // Representation of 16.25 with two decimal places
  s21_decimal value2 = {{1625, 0, 0, 0x00020000}};
  s21_decimal result2 = {{0, 0, 0, 0}};
  int status2 = s21_floor(value2, &result2);
  ck_assert_int_eq(status2, CALCULATION_OK);
  ck_assert_int_eq(result2.bits[0], 16);
  ck_assert_int_eq(result2.bits[1], 0);
  ck_assert_int_eq(result2.bits[2], 0);
  ck_assert_int_eq(result2.bits[3], 0);
}
END_TEST

Suite *test_floor() {
  Suite *test_set = suite_create("s21_floor");
  TCase *test_group = tcase_create("s21_floor_test_group");

  tcase_add_test(test_group, floor1);
  tcase_add_test(test_group, floor2);
  tcase_add_test(test_group, floor3);
  tcase_add_test(test_group, floor4);
  tcase_add_test(test_group, floor5);
  tcase_add_test(test_group, floor6);
  tcase_add_test(test_group, floor7);
  tcase_add_test(test_group, floor8);
  tcase_add_test(test_group, floor9);
  tcase_add_test(test_group, floor10);
  tcase_add_test(test_group, floor11);
  tcase_add_test(test_group, floor12);
  tcase_add_test(test_group, floor13);
  tcase_add_test(test_group, floor14);
  tcase_add_test(test_group, floor15);
  tcase_add_test(test_group, floor16);
  tcase_add_test(test_group, floor17);
  tcase_add_test(test_group, floor18);
  tcase_add_test(test_group, floor19);
  tcase_add_test(test_group, floor20);
  tcase_add_test(test_group, floor21);
  tcase_add_test(test_group, floor22);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

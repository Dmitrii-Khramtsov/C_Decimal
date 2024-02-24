#include "s21_decimal_tests.h"

START_TEST(round1) {
  // Rounding a negative number up -2.2 = -2
  s21_decimal value = {.bits = {22, 0, 0, 0x80010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round2) {
  // Rounding a negative number down -2.8 = -3
  s21_decimal value = {.bits = {28, 0, 0, 0x80010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round3) {
  // Max positive number - edge case - integer value
  s21_decimal value = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round4) {
  // Max negative number - edge case - negative integer value
  s21_decimal value = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round5) {
  // Rounding a positive number up 2.86 = 3
  s21_decimal value = {.bits = {286, 0, 0, 0x00020000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round6) {
  // Rounding a positive number down 2.16 = 2
  s21_decimal value = {.bits = {216, 0, 0, 0x00020000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round7) {
  // result = NULL
  s21_decimal value = {.bits = {0, 43, 342874, 0x000A0000}};
  s21_decimal *result = NULL;
  int status = s21_round(value, result);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

START_TEST(round8) {
  // Max positive number - maximum scale
  s21_decimal value = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round9) {
  // Max negative number - maximum scale
  s21_decimal value = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 8);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round10) {
  // Rounding a number 2.5 = 3
  s21_decimal value = {.bits = {25, 0, 0, 0x00010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round11) {
  // 0 -> 0
  s21_decimal value = {.bits = {0, 0, 0, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round12) {
  // Negative zero 0 -> 0
  s21_decimal value = {.bits = {0, 0, 0, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round13) {
  // 0.5 -> 1
  s21_decimal value = {.bits = {5, 0, 0, 0x00010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round14) {
  // Very small positive number 1e-28 -> 0
  // 0.0000000000000000000000000001
  s21_decimal value = {.bits = {1, 0, 0, 0x001C0000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round15) {
  // Very small negative number 1e-28 -> 0
  // -0.0000000000000000000000000001
  s21_decimal value = {.bits = {1, 0, 0, 0x801C0000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round16) {
  // Checking metadata of a positive number
  // 15.0 -> 15
  s21_decimal value = {.bits = {150, 0, 0, 0x00010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round17) {
  // Checking metadata of a negative number
  // -15.0 -> -15
  s21_decimal value = {.bits = {150, 0, 0, 0x80010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round18) {
  // Very large number with many digits after the decimal point
  // 9876543210.123456789
  s21_decimal value = {.bits = {0xB0347115, 0x891087B8, 0, 0x00090000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0x4CB016EA);
  ck_assert_int_eq(result.bits[1], 0x2);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round19) {
  // Number equals -1 -> -1
  s21_decimal value = {.bits = {1, 0, 0, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(round20) {
  // Rounding a number 2.5 = 3
  s21_decimal value = {.bits = {25, 0, 0, 0x00010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 3);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(round21) {
  // Rounding a number 4.999999999999999999999999 to 5
  // 4999999999999999999999999
  s21_decimal value = {.bits = {0x24FFFFFF, 0x8B0A00A4, 0x422CA, 0x00180000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

Suite *test_round() {
  Suite *test_set = suite_create("s21_round");
  TCase *test_group = tcase_create("s21_round_test_group");

  tcase_add_test(test_group, round1);
  tcase_add_test(test_group, round2);
  tcase_add_test(test_group, round3);
  tcase_add_test(test_group, round4);
  tcase_add_test(test_group, round5);
  tcase_add_test(test_group, round6);
  tcase_add_test(test_group, round7);
  tcase_add_test(test_group, round8);
  tcase_add_test(test_group, round9);
  tcase_add_test(test_group, round10);
  tcase_add_test(test_group, round11);
  tcase_add_test(test_group, round12);
  tcase_add_test(test_group, round13);
  tcase_add_test(test_group, round14);
  tcase_add_test(test_group, round15);
  tcase_add_test(test_group, round16);
  tcase_add_test(test_group, round17);
  tcase_add_test(test_group, round18);
  tcase_add_test(test_group, round19);
  tcase_add_test(test_group, round20);
  tcase_add_test(test_group, round21);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

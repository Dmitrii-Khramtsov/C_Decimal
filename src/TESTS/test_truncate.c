#include "s21_decimal_tests.h"

START_TEST(truncate1) {
  // Mantissa 1000, order 10^3
  s21_decimal value1 = {.bits = {1000, 0, 0, 3 << 16}};
  s21_decimal result1;
  int status1 = s21_truncate(value1, &result1);
  ck_assert_int_eq(status1, CALCULATION_OK);
  ck_assert_int_eq(result1.bits[0], 1);
  ck_assert_int_eq(result1.bits[1], 0);
  ck_assert_int_eq(result1.bits[3], 0);
  ck_assert_int_eq(result1.bits[2], 0);
}
END_TEST

START_TEST(truncate2) {
  // Mantissa 1, order 10^3
  s21_decimal value1 = {.bits = {1, 0, 0, 3 << 16}};
  s21_decimal result1;
  int status1 = s21_truncate(value1, &result1);
  ck_assert_int_eq(status1, CALCULATION_OK);
  ck_assert_int_eq(result1.bits[0], 0);
  ck_assert_int_eq(result1.bits[1], 0);
  ck_assert_int_eq(result1.bits[3], 0);
  ck_assert_int_eq(result1.bits[2], 0);
}
END_TEST

START_TEST(truncate3) {
  // The value is set to the maximum possible value, and the result is expected
  // to be truncated to a smaller value.
  s21_decimal value2 = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C << 16}};
  s21_decimal result2;
  int status2 = s21_truncate(value2, &result2);
  ck_assert_int_eq(status2, CALCULATION_OK);
  ck_assert_int_eq(result2.bits[0], 7);
  ck_assert_int_eq(result2.bits[1], 0);
  ck_assert_int_eq(result2.bits[2], 0);
  ck_assert_int_eq(result2.bits[3], 0);
}
END_TEST

START_TEST(truncate4) {
  // The maximum mantissa, the exponent of degree is 10^27 and the number is
  // positive.
  s21_decimal value = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B << 16}};
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 79);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate5) {
  // Only bits[0] is filled.
  s21_decimal value = {.bits = {123456789, 0, 0, 0x000A0000}};
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate6) {
  // Only bits[1] is filled.
  s21_decimal value = {.bits = {0, 123456789, 0, 0x000A0000}};
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 53024287);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate7) {
  // Only bits[2] is filled.
  s21_decimal value = {.bits = {0, 0, 123456789, 0x000A0000}};
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 525778104);
  ck_assert_int_eq(result.bits[1], 53024287);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate8) {
  // Scale = 0.
  s21_decimal value = {.bits = {123456789, 987654321, 111222333, 0}};
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, CALCULATION_OK);
  ck_assert_int_eq(result.bits[0], 123456789);
  ck_assert_int_eq(result.bits[1], 987654321);
  ck_assert_int_eq(result.bits[2], 111222333);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(truncate9) {
  // Bits[0], bits[1] are occupied; bits[2] is empty.
  s21_decimal src1;
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result;
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res_od;
  s21_truncate(src1, &res_od);
  ck_assert_int_eq(res_od.bits[0], result.bits[0]);
  ck_assert_int_eq(res_od.bits[1], result.bits[1]);
  ck_assert_int_eq(res_od.bits[2], result.bits[2]);
  ck_assert_int_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate10) {
  // Incompletely utilized each of the bits.
  s21_decimal src1;
  src1.bits[0] = 0x0000006D;  // 0b00000000000000000000000001101101;
  src1.bits[1] = 0x000C655B;  // 0b00000000000011000110010101011011;
  src1.bits[2] = 0x00003039;  // 0b00000000000000000011000000111001;
  src1.bits[3] = 0x000E0000;  // 0b00000000000011100000000000000000;
  s21_decimal result;
  result.bits[0] = 0x87BC161E;  // 0b10000111101111000001011000011110;
  result.bits[1] = 0x00000000;  // 0b00000000000000000000000000000000;
  result.bits[2] = 0x00000000;  // 0b00000000000000000000000000000000;
  result.bits[3] = 0x00000000;  // 0b00000000000000000000000000000000;
  s21_decimal res_od;
  s21_truncate(src1, &res_od);
  ck_assert_int_eq(res_od.bits[0], result.bits[0]);
  ck_assert_int_eq(res_od.bits[1], result.bits[1]);
  ck_assert_int_eq(res_od.bits[2], result.bits[2]);
  ck_assert_int_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate11) {
  // result = NULL
  s21_decimal value = {.bits = {0, 123456789, 0, 0x000A0000}};
  s21_decimal *result = NULL;
  int status = s21_truncate(value, result);
  ck_assert_int_eq(status, CALCULATION_ERROR);
}
END_TEST

Suite *test_truncate() {
  Suite *test_set = suite_create("s21_truncate");
  TCase *test_group = tcase_create("s21_truncate_test_group");

  tcase_add_test(test_group, truncate1);
  tcase_add_test(test_group, truncate2);
  tcase_add_test(test_group, truncate3);
  tcase_add_test(test_group, truncate4);
  tcase_add_test(test_group, truncate5);
  tcase_add_test(test_group, truncate6);
  tcase_add_test(test_group, truncate7);
  tcase_add_test(test_group, truncate8);
  tcase_add_test(test_group, truncate9);
  tcase_add_test(test_group, truncate10);
  tcase_add_test(test_group, truncate11);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

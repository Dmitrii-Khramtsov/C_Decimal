#include "s21_decimal_tests.h"

START_TEST(add_1) {
  // 0 + maximum positive number -> result is maximum positive
  s21_decimal first = {{0, 0, 0, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_add(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(add_2) {
  // Maximum positive number + maximum positive number -> error, too large
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_add(first, second, &result);
  ck_assert_int_eq(status, TOO_LARGE_OR_INF);
}
END_TEST

START_TEST(add_3) {
  // Maximum negative number + Maximum negative number -> error, too small
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(first, second, &result);
  ck_assert_int_eq(status, TOO_SMALL_OR_NEG_INF);
}
END_TEST

START_TEST(add_4) {
  // 1.3 + 2.86 = 4.16
  s21_decimal value_1 = {{13, 0, 0, 0x00010000}};
  s21_decimal value_2 = {{286, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 416);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(add_5) {
  // maximum positive + maximum negative -> 0
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(add_6) {
  // 0.2 + occupied two bits * 10^-1
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0x00010000}};
  s21_decimal value_2 = {{2, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0x1);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(add_7) {
  // 0.13 + 28.6 -> 28.73
  s21_decimal value_1 = {{13, 0, 0, 0x00020000}};
  s21_decimal value_2 = {{286, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2873);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(add_8) {
  // 1 + 7922816251426433759354395033.5 -> 7922816251426433759354395034
  // banking rounding occurs here
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x9999999a);
  ck_assert_int_eq(result.bits[1], 0x99999999);
  ck_assert_int_eq(result.bits[2], 0x19999999);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(add_9) {
  // 7922816251426433759354395033.5 + 1 -> 7922816251426433759354395034
  // banking rounding occurs here
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x9999999a);
  ck_assert_int_eq(result.bits[1], 0x99999999);
  ck_assert_int_eq(result.bits[2], 0x19999999);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(add_10) {
  // 1 + maximum positive number -> error, too large
  // + check that nothing is written to result
  s21_decimal first = {{1, 0, 0, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(first, second, &result);
  ck_assert_int_eq(status, TOO_LARGE_OR_INF);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(add_11) {
  // -0.13 + 28.6 -> 28.47
  s21_decimal value_1 = {{13, 0, 0, 0x80020000}};
  s21_decimal value_2 = {{286, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2847);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(add_12) {
  // -1.3 + (-2.86) = -4.16
  s21_decimal value_1 = {{13, 0, 0, 0x80010000}};
  s21_decimal value_2 = {{286, 0, 0, 0x80020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 416);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

START_TEST(add_13) {
  // Negative fractional + positive fractional; different exponents
  // -281474968550.991 + 1759217.7884751 = -281473209333.2025249
  s21_decimal value_1 = {{0xFF837E4F, 0x0000FFFF, 0, 0x80030000}};
  s21_decimal value_2 = {{0xFF837E4F, 0x00000FFF, 0, 0x00070000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[3], 0x80070000);
  ck_assert_int_eq(result.bits[0], 0x00F26FA1);
  ck_assert_int_eq(result.bits[1], 0x270FEFED);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(add_14) {
  // -integer + -integer without overflow
  // -13 + (-26) -> -39
  s21_decimal value_1 = {{13, 0, 0, SIGN_MASK}};
  s21_decimal value_2 = {{26, 0, 0, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 39);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(add_15) {
  // [+] integer + [+] fractional without overflow
  // 13 + 13.12 -> 26.12
  s21_decimal value_1 = {{13, 0, 0, 0}};
  s21_decimal value_2 = {{1312, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2612);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(add_16) {
  // [+] integer + [-] fractional without overflow
  // 13 + (-3.333) ->  9.667
  s21_decimal value_1 = {{13, 0, 0, 0}};
  s21_decimal value_2 = {{3333, 0, 0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 9667);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00030000);
}
END_TEST

START_TEST(add_17) {
  // [-] integer + [+] fractional without overflow
  // -13 + 3.333 -> -9.667
  s21_decimal value_1 = {{13, 0, 0, SIGN_MASK}};
  s21_decimal value_2 = {{3333, 0, 0, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 9667);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80030000);
}
END_TEST

START_TEST(add_18) {
  // [-] integer + [-] fractional without overflow
  // -13 + (-3.333) ->  -16.333
  s21_decimal value_1 = {{13, 0, 0, SIGN_MASK}};
  s21_decimal value_2 = {{3333, 0, 0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 16333);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80030000);
}
END_TEST

START_TEST(add_19) {
  // [-] integer + [-] fractional with overflow
  // max [-] integer + (max mantissa, [-] fractional 10^10) -> error, too small
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, TOO_SMALL_OR_NEG_INF);
}
END_TEST

START_TEST(add_20) {
  // [-] integer + [-] fractional with banking rounding without overflow
  // -79228162514264337593543950334 - 0.6 -> -79228162514264337593543950334.6
  // rounding: -79228162514264337593543950335
  s21_decimal value_1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal value_2 = {{6, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(add_21) {
  // [+] fractional + [+] fractional with banking rounding without overflow
  // 7922816251426433759354395031.1 + 2.12 = 7922816251426433759354395033.22
  // Rounding to 7922816251426433759354395033.2 (banking rounding)
  s21_decimal value_1 = {{0xFFFFFFE7, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  s21_decimal value_2 = {{212, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFC);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

Suite *test_add() {
  Suite *test_set = suite_create("s21_add");
  TCase *test_group = tcase_create("s21_add_test_group");

  tcase_add_test(test_group, add_1);
  tcase_add_test(test_group, add_2);
  tcase_add_test(test_group, add_3);
  tcase_add_test(test_group, add_4);
  tcase_add_test(test_group, add_5);
  tcase_add_test(test_group, add_6);
  tcase_add_test(test_group, add_7);
  tcase_add_test(test_group, add_8);
  tcase_add_test(test_group, add_9);
  tcase_add_test(test_group, add_10);
  tcase_add_test(test_group, add_11);
  tcase_add_test(test_group, add_12);
  tcase_add_test(test_group, add_13);
  tcase_add_test(test_group, add_14);
  tcase_add_test(test_group, add_15);
  tcase_add_test(test_group, add_16);
  tcase_add_test(test_group, add_17);
  tcase_add_test(test_group, add_18);
  tcase_add_test(test_group, add_19);
  tcase_add_test(test_group, add_20);
  tcase_add_test(test_group, add_21);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

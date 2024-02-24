#include "s21_decimal_tests.h"

START_TEST(div_1) {
  // 1 / 5 = 0.2
  s21_decimal first = {{1, 0, 0, 0}};
  s21_decimal second = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(div_2) {
  // 10 / 5 = 0.2; + integer / + integer without overflow
  s21_decimal first = {{10, 0, 0, 0}};
  s21_decimal second = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_3) {
  // Max positive number / max positive number = 1
  // 79228162514264337593543950335 / 79228162514264337593543950335 = 1
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_4) {
  // 9 / 1 = 9; + integer / + integer without overflow
  s21_decimal first = {{9, 0, 0, 0}};
  s21_decimal second = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 9);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_5) {
  // Maximum positive integer / 1 = maximum positive integer
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_6) {
  // 10 / -5 = -2
  s21_decimal first = {{10, 0, 0, 0}};
  s21_decimal second = {{5, 0, 0, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(div_7) {
  // Positive max integer / (-1) = Maximum negative integer
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{1, 0, 0, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], 0x80000000);
}
END_TEST

START_TEST(div_8) {
  // -10 / -5 = 2
  s21_decimal first = {{10, 0, 0, SIGN_MASK}};
  s21_decimal second = {{5, 0, 0, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_9) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {{2, 0, 0, SIGN_MASK}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0x80000000);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(div_10) {
  // 5 / 0.5 = 10
  s21_decimal first = {{5, 0, 0, 0}};
  s21_decimal second = {{5, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_11) {
  // 5 / 0.25 = 20
  s21_decimal first = {{5, 0, 0, 0}};
  s21_decimal second = {{25, 0, 0, 0x00020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_12) {
  // 10 / -0.5 = -20
  s21_decimal first = {{10, 0, 0, 0}};
  s21_decimal second = {{5, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(div_13) {
  // -15 / 0.2 = -75
  s21_decimal first = {{15, 0, 0, SIGN_MASK}};
  s21_decimal second = {{2, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 75);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(div_14) {
  // -10 / -0.1 = 100
  s21_decimal first = {{10, 0, 0, SIGN_MASK}};
  s21_decimal second = {{1, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_15) {
  s21_decimal first = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {{1, 0, 0, 0x80170000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, TOO_LARGE_OR_INF);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_16) {
  // -12 / -0.5 = 6
  s21_decimal first = {{12, 0, 0, SIGN_MASK}};
  s21_decimal second = {{5, 0, 0, 0x80010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 24);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_17) {
  // 0.125 / 0.0625 = 2 (different degrees)
  s21_decimal first = {{125, 0, 0, 0x00030000}};
  s21_decimal second = {{625, 0, 0, 0x00040000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_18) {
  // 0.2 / 0.3
  // bank rounding: 0.6666666666666666666666666667
  s21_decimal first = {{2, 0, 0, 0x00010000}};
  s21_decimal second = {{3, 0, 0, 0x00010000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 178956971);
  ck_assert_int_eq(result.bits[1], 695075222);
  ck_assert_int_eq(result.bits[2], 361400724);
  ck_assert_int_eq(result.bits[3], 0x001C0000);
}
END_TEST

START_TEST(div_19) {
  // 0.25 / -0.125 = -2 (different degrees)
  s21_decimal first = {{25, 0, 0, 0x00020000}};
  s21_decimal second = {{125, 0, 0, 0x80030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(div_20) {
  // -0.1 / -0.01 = 10 (different degrees)
  s21_decimal first = {{1, 0, 0, 0x80010000}};
  s21_decimal second = {{1, 0, 0, 0x80020000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_21) {
  // 0.5 / 0.125 = 4
  s21_decimal first = {{5, 0, 0, 0x00010000}};
  s21_decimal second = {{125, 0, 0, 0x00030000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 4);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_22) {
  // 100 / 1 = 100
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_23) {
  // 100 / 2 = 50
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_24) {
  // 100 / 3 = 33.33333333333333333333333333333333333....
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{3, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x35555555);
  ck_assert_int_eq(result.bits[1], 0xCF2607EE);
  ck_assert_int_eq(result.bits[2], 0x6BB4AFE4);
  ck_assert_int_eq(result.bits[3], 0x001B0000);
}
END_TEST

START_TEST(div_25) {
  // 100 / 4 = 25
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{4, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 25);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_26) {
  // 100 / 5 = 20
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_27) {
  // 100 / 6
  // bank rounding: 16.666666666666666666666666667
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{6, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x1AAAAAAB);
  ck_assert_int_eq(result.bits[1], 0x679303F7);
  ck_assert_int_eq(result.bits[2], 0x35DA57F2);
  ck_assert_int_eq(result.bits[3], 0x001B0000);
}
END_TEST

START_TEST(div_28) {
  //      100 / 7 = 14.2857142857142857142857142857142857142857142857142857...
  // bank rounding: 14.285714285714285714285714286

  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{7, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xCDB6DB6E);
  ck_assert_int_eq(result.bits[1], 0x3434DED3);
  ck_assert_int_eq(result.bits[2], 0x2E28DDAB);
  ck_assert_int_eq(result.bits[3], 0x001B0000);
}
END_TEST

START_TEST(div_29) {
  // 100 / 8 = 12.5
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{8, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 125);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(div_30) {
  // 100 / 9 = 11.111111111111111111111111111111111111...
  // bank rounding: 11.111111111111111111111111111
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{9, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x671C71C7);
  ck_assert_int_eq(result.bits[1], 0x450CAD4F);
  ck_assert_int_eq(result.bits[2], 0x23E6E54C);
  ck_assert_int_eq(result.bits[3], 0x001B0000);
}
END_TEST

START_TEST(div_31) {
  // 100 / 10 = 10
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_32) {
  // 100 / 0 = Division by zero error
  s21_decimal first = {{100, 0, 0, 0}};
  s21_decimal second = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, DIV_BY_ZERO);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_33) {
  // 0 / 100 -> 0
  s21_decimal first = {.bits = {0, 0, 0, 0}};
  s21_decimal second = {.bits = {100, 0, 0, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_div(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

Suite *test_div() {
  Suite *test_set = suite_create("s21_div");
  TCase *test_group = tcase_create("s21_div_test_group");

  tcase_add_test(test_group, div_1);
  tcase_add_test(test_group, div_2);
  tcase_add_test(test_group, div_3);
  tcase_add_test(test_group, div_4);
  tcase_add_test(test_group, div_5);
  tcase_add_test(test_group, div_6);
  tcase_add_test(test_group, div_7);
  tcase_add_test(test_group, div_8);
  tcase_add_test(test_group, div_9);
  tcase_add_test(test_group, div_10);
  tcase_add_test(test_group, div_11);
  tcase_add_test(test_group, div_12);
  tcase_add_test(test_group, div_13);
  tcase_add_test(test_group, div_14);
  tcase_add_test(test_group, div_15);
  tcase_add_test(test_group, div_16);
  tcase_add_test(test_group, div_17);
  tcase_add_test(test_group, div_18);
  tcase_add_test(test_group, div_19);
  tcase_add_test(test_group, div_20);
  tcase_add_test(test_group, div_21);
  tcase_add_test(test_group, div_22);
  tcase_add_test(test_group, div_23);
  tcase_add_test(test_group, div_24);
  tcase_add_test(test_group, div_25);
  tcase_add_test(test_group, div_26);
  tcase_add_test(test_group, div_27);
  tcase_add_test(test_group, div_28);
  tcase_add_test(test_group, div_29);
  tcase_add_test(test_group, div_30);
  tcase_add_test(test_group, div_31);
  tcase_add_test(test_group, div_32);
  tcase_add_test(test_group, div_33);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

#include "s21_decimal_tests.h"

START_TEST(sub_1) {
  // 0 - max positive number -> - max number
  s21_decimal first = {.bits = {0, 0, 0, 0}};
  s21_decimal second = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_sub(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], 0xFFFFFFFF);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(sub_2) {
  // Max positive number - max positive number -> 0
  s21_decimal first = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_sub(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(sub_3) {
  // Max negative number - Max negative number -> 0
  s21_decimal first = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_sub(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal value_1 = {.bits = {13, 0, 0, 0x00010000}};
  s21_decimal value_2 = {.bits = {286, 0, 0, 0x00020000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 156);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x80020000);
}
END_TEST

Suite *test_sub() {
  Suite *test_set = suite_create("s21_sub");
  TCase *test_group = tcase_create("s21_sub_test_group");

  tcase_add_test(test_group, sub_1);
  tcase_add_test(test_group, sub_2);
  tcase_add_test(test_group, sub_3);
  tcase_add_test(test_group, sub_4);

  suite_add_tcase(test_set, test_group);

  return test_set;
}

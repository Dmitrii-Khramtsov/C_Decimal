#include "s21_decimal_tests.h"

START_TEST(mul1) {
  // 0 * max positive number -> 0
  s21_decimal first = {.bits = {0, 0, 0, 0}};
  s21_decimal second = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul2) {
  // max positive number * max positive number -> plus overflow
  s21_decimal first = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, TOO_LARGE_OR_INF);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul3) {
  // max positive number * (- max positive number) -> overflow in minus
  s21_decimal first = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal second = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, TOO_SMALL_OR_NEG_INF);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul4) {
  // 123 * 13 = 1599
  s21_decimal first = {.bits = {123, 0, 0, 0}};
  s21_decimal second = {.bits = {13, 0, 0, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 1599);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul5) {
  // 123 * -13 = 1599
  s21_decimal first = {.bits = {123, 0, 0, 0}};
  s21_decimal second = {.bits = {13, 0, 0, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 1599);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], SIGN_MASK);
}
END_TEST

START_TEST(mul6) {
  // -123 * -13 = 1599
  s21_decimal first = {.bits = {123, 0, 0, SIGN_MASK}};
  s21_decimal second = {.bits = {13, 0, 0, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 1599);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul7) {
  // (-max positive number) * (-max positive number) -> overflow in plus
  s21_decimal first = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal second = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, SIGN_MASK}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, TOO_LARGE_OR_INF);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul8) {
  // test res 1599 0 0 [2]
  // my = 159900 0 0 [4] = 15.99
  s21_decimal first = {.bits = {123, 0, 0, 0x00020000}};
  s21_decimal second = {.bits = {13, 0, 0, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = 0;
  status = s21_mul(first, second, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 1599);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x00020000);
}
END_TEST

START_TEST(mul9) {
  // 2922816251426433759354395033.5 * 2 -> 5845632502852867518708790067.0
  // This is where the bank rounding takes place
  s21_decimal value_1 = {
      .bits = {2952790015, 3376870426, 1584461864, 0x00010000}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 1610612734);
  ck_assert_int_eq(result.bits[1], 2458773557);
  ck_assert_int_eq(result.bits[2], 3168923729);
  ck_assert_int_eq(result.bits[3], 0x00010000);
}
END_TEST

START_TEST(mul10) {
  // 2922816251426433759354395033 * 2 -> 5845632502852867518708790066
  s21_decimal value_1 = {.bits = {295279001, 2055673961, 158446186, 0}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 590558002);
  ck_assert_int_eq(result.bits[1], 4111347922);
  ck_assert_int_eq(result.bits[2], 316892372);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul11) {
  //   // my {0} 3510766279 3615164911 4294967288 [0] =
  //   79228162382217400069770054343 good!
  s21_decimal value_1 = {.bits = {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x00080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 3510766279);
  ck_assert_int_eq(result.bits[1], 3615164911);
  ck_assert_int_eq(result.bits[2], 4294967288);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul12) {
  // my 1320469375237738 * -5.99999999 -> -7922816238221734.24762262
  s21_decimal value_1 = {.bits = {0xBC0C3E6A, 0x4B0F5, 0, 0}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x80080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xA5C2BD96);
  ck_assert_int_eq(result.bits[1], 0xAC426A51);
  ck_assert_int_eq(result.bits[2], 0xA7C5);
  ck_assert_int_eq(result.bits[3], 0x80080000);
}
END_TEST

START_TEST(mul13) {
  // my = -1320469375237738 * 5.99999999 -> -7922816238221734.24762262
  s21_decimal value_1 = {.bits = {0xBC0C3E6A, 0x4B0F5, 0, 0x80000000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x00080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xA5C2BD96);
  ck_assert_int_eq(result.bits[1], 0xAC426A51);
  ck_assert_int_eq(result.bits[2], 0xA7C5);
  ck_assert_int_eq(result.bits[3], 0x80080000);
}
END_TEST

START_TEST(mul14) {
  // my = -1320469375237738 * -5.99999999 -> 7922816238221734.24762262
  s21_decimal value_1 = {.bits = {0xBC0C3E6A, 0x4B0F5, 0, 0x80000000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x80080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0xA5C2BD96);
  ck_assert_int_eq(result.bits[1], 0xAC426A51);
  ck_assert_int_eq(result.bits[2], 0xA7C5);
  ck_assert_int_eq(result.bits[3], 0x00080000);
}
END_TEST

START_TEST(mul15) {
  // -79228162514264337593543950300 * -5.99999999 ->
  // 475368974293304400418620325864.560497 overflow
  s21_decimal value_1 = {
      .bits = {0xFFFFFFDC, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x80080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, TOO_LARGE_OR_INF);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul16) {
  // -13204693752377389598923991722 * -5.99999999 ->
  // 79228162382217400069770054342.76008278
  // my 79228162382217400069770054343 bank rounding
  s21_decimal value_1 = {
      .bits = {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x80080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 3510766279);
  ck_assert_int_eq(result.bits[1], 3615164911);
  ck_assert_int_eq(result.bits[2], 4294967288);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(mul17) {
  // 5.99999999998 * 5.99999999 -> 35.9999999398800000002
  s21_decimal value_1 = {.bits = {0xB2C96FFE, 0x8B, 0, 0x000B0000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x00080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x6A500402);
  ck_assert_int_eq(result.bits[1], 0x8400EC17);
  ck_assert_int_eq(result.bits[2], 0x13);
  ck_assert_int_eq(result.bits[3], 0x00130000);
}
END_TEST

START_TEST(mul18) {
  // 5.9999999999812345678912 * 5.99999999 -> 35.999999939887407407534854321088
  // bank rounding 35.999999939887407407534854321
  s21_decimal value_1 = {.bits = {0x7C6E4C40, 0x9B44BA34, 0xCB4, 0x00160000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x00080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x9E5650B1);
  ck_assert_int_eq(result.bits[1], 0x37173417);
  ck_assert_int_eq(result.bits[2], 0x74528083);
  ck_assert_int_eq(result.bits[3], 0x001B0000);
}
END_TEST

START_TEST(mul19) {
  // -5.99999999998 * 5.99999999 -> -35.9999999398800000002
  s21_decimal value_1 = {.bits = {0xB2C96FFE, 0x8B, 0, 0x800B0000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x00080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x6A500402);
  ck_assert_int_eq(result.bits[1], 0x8400EC17);
  ck_assert_int_eq(result.bits[2], 0x13);
  ck_assert_int_eq(result.bits[3], 0x80130000);
}
END_TEST

START_TEST(mul20) {
  // -5.99999999998 * -5.99999999 -> 35.9999999398800000002
  s21_decimal value_1 = {.bits = {0xB2C96FFE, 0x8B, 0, 0x800B0000}};
  s21_decimal value_2 = {.bits = {0x23C345FF, 0, 0, 0x80080000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 0x6A500402);
  ck_assert_int_eq(result.bits[1], 0x8400EC17);
  ck_assert_int_eq(result.bits[2], 0x13);
  ck_assert_int_eq(result.bits[3], 0x00130000);
}
END_TEST

START_TEST(mul21) {
  // test_mul_operation_high_exp_case
  s21_decimal value_1 = {.bits = {0xffffffff, 0, 0, 0x801C0000}};
  s21_decimal value_2 = {.bits = {0xffffffff, 0, 0, 0x80010000}};
  s21_decimal result = {.bits = {0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.bits[0], 1717986918);
  ck_assert_int_eq(result.bits[1], 429496729);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0x001c0000);
}
END_TEST

Suite *test_mul() {
  Suite *test_set = suite_create("s21_mul");
  TCase *test_group = tcase_create("s21_mul_test_group");

  tcase_add_test(test_group, mul1);
  tcase_add_test(test_group, mul2);
  tcase_add_test(test_group, mul3);
  tcase_add_test(test_group, mul4);
  tcase_add_test(test_group, mul5);
  tcase_add_test(test_group, mul6);
  tcase_add_test(test_group, mul7);
  tcase_add_test(test_group, mul8);
  tcase_add_test(test_group, mul9);
  tcase_add_test(test_group, mul10);
  tcase_add_test(test_group, mul11);
  tcase_add_test(test_group, mul12);
  tcase_add_test(test_group, mul13);
  tcase_add_test(test_group, mul14);
  tcase_add_test(test_group, mul15);
  tcase_add_test(test_group, mul16);
  tcase_add_test(test_group, mul17);
  tcase_add_test(test_group, mul18);
  tcase_add_test(test_group, mul19);
  tcase_add_test(test_group, mul20);
  tcase_add_test(test_group, mul21);

  suite_add_tcase(test_set, test_group);

  return test_set;
}
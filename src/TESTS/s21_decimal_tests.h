#ifndef S21_DECIMAL_TESTS_H
#define S21_DECIMAL_TESTS_H

#include <assert.h>
#include <check.h>
#include <stdio.h>

#include "../s21_decimal.h"

Suite *test_add();
Suite *test_sub();
Suite *test_mul();
Suite *test_div();
Suite *test_negate();

Suite *test_int2dec();
Suite *test_dec2int();

Suite *test_float2dec();
Suite *test_dec2float();

Suite *test_equal();
Suite *test_notequal();
Suite *test_greater();
Suite *test_greater_equal();
Suite *test_less();
Suite *test_less_equal();

Suite *test_truncate();
Suite *test_round();
Suite *test_floor();

#endif
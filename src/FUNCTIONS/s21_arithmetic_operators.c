#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_operations = 0;  // because we're in a function - <<addition>>
  int output = add_sub_big_decimal(value_1, value_2, &sign_operations, result);

  return output;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_operations = 1;  // because we're in a function - <<difference>>
  int output = add_sub_big_decimal(value_1, value_2, &sign_operations, result);

  output = output ? TOO_SMALL_OR_NEG_INF : OK;
  return output;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sum_scale = get_scale(value_1) + get_scale(value_2);
  if (is_decimal_zero(&value_1) || is_decimal_zero(&value_2) ||
      sum_scale > MAX_DEGREE * 2) {
    reset_decimal(result);
    return OK;
  }
  reset_decimal(result);
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal tmp_result = {0};
  int output = 0;

  convert_to_big_decimal(value_1, &big_value_1);
  convert_to_big_decimal(value_2, &big_value_2);

  alignment_scale_big_decimal(&big_value_1, &big_value_2);

  mult_big_decimal(big_value_1, big_value_2, &tmp_result);

  tmp_result.sign = sign_for_mult_and_div(big_value_1, big_value_2);
  tmp_result.scale =
      big_value_1.scale + big_value_2.scale;  // scale with multiplication

  output = decimal_owerflow_error(tmp_result);
  if (!output) {
    output = bank_round(tmp_result, result);
  }

  if (get_scale(*result) > sum_scale) {
    div_ten_without_remainder_and_sub_scale(result);
  }

  return output;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) {
    return CALCULATION_ERROR;
  }
  if (is_decimal_zero(&value_2)) {
    return DIV_BY_ZERO;
  } else if (is_decimal_zero(&value_1)) {
    reset_decimal(result);
    return OK;
  }

  reset_decimal(result);
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal tmp_result = {0};
  int output = OK;

  convert_to_big_decimal(value_1, &big_value_1);
  convert_to_big_decimal(value_2, &big_value_2);

  alignment_scale_big_decimal(&big_value_1, &big_value_2);

  div_mantissa_big_decimal(big_value_1, big_value_2, &tmp_result);

  tmp_result.sign = sign_for_mult_and_div(big_value_1, big_value_2);

  output = bank_round(tmp_result, result);

  return output;
}

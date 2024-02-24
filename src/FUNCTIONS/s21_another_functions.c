#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return CALCULATION_ERROR;
  }
  int degree = get_scale(value);
  if (degree > MAX_DEGREE) {
    return CALCULATION_ERROR;
  }

  unsigned int sign = get_sign(value);
  reset_decimal(result);
  *result = value;

  while (degree > 0) {
    div_ten(result);
    --degree;
  }

  set_sign(result, sign);

  return CALCULATION_OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return CALCULATION_ERROR;
  }

  reset_decimal(result);

  *result = value;
  unsigned int sign = get_sign(value);
  sign ^= 1;
  set_sign(result, sign);
  return CALCULATION_OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return CALCULATION_ERROR;
  }

  reset_decimal(result);

  s21_decimal tmp_value = value;
  int final_owerflow = 0;
  int sum_owerflow = 0;
  s21_decimal round_owerflow = {0};

  round_overflow(&tmp_value, &sum_owerflow, &final_owerflow);

  round_owerflow.bits[0] = final_owerflow >= 5 ? 1 : 0;

  add_mantissa(tmp_value, round_owerflow, result);

  unsigned int sign = get_sign(value);
  set_sign(result, sign);

  return CALCULATION_OK;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return CALCULATION_ERROR;
  }

  reset_decimal(result);

  s21_decimal tmp_value = value;
  s21_decimal round_owerflow = {0};
  int final_owerflow = 0;
  int sum_owerflow = 0;

  round_overflow(&tmp_value, &sum_owerflow, &final_owerflow);

  unsigned int sign = get_sign(value);
  if (sign && sum_owerflow != 0) {
    round_owerflow.bits[0] = 1;
    add_mantissa(tmp_value, round_owerflow, result);
  } else
    *result = tmp_value;

  set_sign(result, sign);

  return CALCULATION_OK;
}

#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int output = FALSE;

  if (is_decimal_zero(&value_1) && is_decimal_zero(&value_2)) {
    output = TRUE;
  } else if (get_sign(value_1) == get_sign(value_2)) {
    alignment_scale(&value_1, &value_2);
    output = !compare_mantissa(&value_1, &value_2);
  }

  return output;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int output = FALSE;

  unsigned int sign_1 = get_sign(value_1);
  unsigned int sign_2 = get_sign(value_2);
  int mode = 0;

  if ((sign_1 && is_decimal_zero(&value_2)) ||
      (is_decimal_zero(&value_1) && !sign_2) || (sign_1 > sign_2)) {
    output = TRUE;
  } else if (sign_1 == sign_2) {
    alignment_scale(&value_1, &value_2);
    mode = compare_mantissa(&value_1, &value_2);

    if ((sign_1 && mode == GREATER) || (!sign_1 && mode == LESS)) {
      output = TRUE;
    }
  }

  return output;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less_or_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2);
}

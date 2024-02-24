#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (input_errors_float(src, dst)) {
    return CONVERSION_ERROR;
  }
  if (!src) {
    return CONVERSION_OK;
  }

  reset_decimal(dst);

  unsigned int sign = src < 0;

  int scale = 0;
  // Bringing 7 significant figures
  dst->bits[0] = seven_signific(src, &scale);

  // Bringing scale to the range from 0 to 28
  unsigned int count_scale = 0;
  while (scale < 0 && count_scale <= MAX_DEGREE) {
    mult_ten(dst);
    ++scale;
    ++count_scale;
  }
  while (scale > MAX_DEGREE) {
    div_ten(dst);
    --scale;
  }

  set_sign(dst, sign);
  set_scale(dst, scale);

  return CONVERSION_OK;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return CONVERSION_ERROR;
  }

  reset_decimal(dst);
  int sign = src < 0;

  src = abs(src);
  dst->bits[0] = src;

  set_sign(dst, sign);

  return CONVERSION_OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return CONVERSION_ERROR;
  }

  *dst = 0;

  for (int i = 0; i < MANTISSA_BITS_SIZE; ++i) {
    *dst += get_bit(src, i) * pow(2, i);
  }

  *dst /= pow(10, get_scale(src));

  unsigned int sign = get_sign(src);
  *dst = sign ? -fabsf(*dst) : fabsf(*dst);

  return CONVERSION_OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return CONVERSION_ERROR;
  }

  int output = CONVERSION_OK;
  *dst = 0;

  output = s21_truncate(src, &src);

  if (output) {
    return CONVERSION_ERROR;
  }

  if (src.bits[1] || src.bits[2]) {
    output = CONVERSION_ERROR;
  } else {
    if (get_bit(src, BITS_SIZE - 1) && !get_sign(src)) {
      output = CONVERSION_ERROR;
    } else {
      *dst = src.bits[0];
    }
  }

  // if (sign) {*dst = ~(*dst - 1);}
  if (get_sign(src)) {
    *dst = -*dst;
  }
  return output;
}

#include "../s21_decimal.h"

void reset_decimal(s21_decimal *dcml) {
  for (int i = 0; i < SIZE_STRUCT; ++i) dcml->bits[i] = 0;
}

int is_decimal_zero(s21_decimal *dcml) {
  if (!dcml->bits[0] && !dcml->bits[1] && !dcml->bits[2]) {
    set_sign(dcml, 0);  // sign at zero '+'
    return TRUE;
  }

  return FALSE;
}

void left_shift(s21_decimal *dcml) {
  dcml->bits[2] <<= 1;
  dcml->bits[2] += (dcml->bits[1] >> (BITS_SIZE - 1)) & 1;
  dcml->bits[1] <<= 1;
  dcml->bits[1] += (dcml->bits[0] >> (BITS_SIZE - 1)) & 1;
  dcml->bits[0] <<= 1;
}

void set_bit(s21_decimal *dcml, unsigned int bit, unsigned int order) {
  int i_struct = order / BITS_SIZE;
  int bit_order = order % BITS_SIZE;
  if (bit) {
    dcml->bits[i_struct] = dcml->bits[i_struct] | bit << bit_order;
  } else {
    dcml->bits[i_struct] = ~(~dcml->bits[i_struct] | !bit << bit_order);
  }
}

int get_bit(s21_decimal dcml, unsigned int order) {
  int i_struct = order / BITS_SIZE;
  int bit_order = order % BITS_SIZE;
  return (dcml.bits[i_struct] >> bit_order) & 1;
}

int get_scale(s21_decimal dcml) { return (dcml.bits[3] & SCALE_MASK) >> 16; }

void set_scale(s21_decimal *dcml, int scale) {
  dcml->bits[3] &= ~SCALE_MASK;
  dcml->bits[3] |= scale << 16;
}

int mult_ten(s21_decimal *dcml) {
  int output = OK;
  s21_decimal dcml_1 = {0};
  s21_decimal dcml_2 = {0};
  s21_decimal tmp_dcml = {0};
  tmp_dcml = *dcml;

  for (int i = 0; i < MANTISSA_BITS_SIZE; i++) {
    unsigned int dcml_bit = get_bit(*dcml, i);
    set_bit(&dcml_1, dcml_bit, i);
    set_bit(&dcml_2, dcml_bit, i);
  }

  for (int i = 0; i < 3; i++) {
    left_shift(&dcml_1);
  }
  left_shift(&dcml_2);

  output = add_mantissa(dcml_1, dcml_2, &tmp_dcml);
  if (!output) {
    *dcml = tmp_dcml;
  }

  return output;
}

unsigned int get_sign(s21_decimal dcml) {
  return dcml.bits[3] & SIGN_MASK ? 1 : 0;
}

void set_sign(s21_decimal *dcml, unsigned int sign) {
  dcml->bits[3] &= ~SIGN_MASK;
  if (sign) dcml->bits[3] |= SIGN_MASK;
}

int div_ten(s21_decimal *dcml) {
  unsigned int sign = get_sign(*dcml);
  int scale = get_scale(*dcml);
  s21_decimal result = {0};
  int tmp = 0;

  for (int i = MANTISSA_BITS_SIZE - 1; i >= 0; --i) {
    tmp *= 2;
    left_shift(&result);
    tmp += get_bit(*dcml, i);
    if (tmp >= 10) {
      tmp -= 10;
      result.bits[0] += 1;
    }
  }

  *dcml = result;
  set_sign(&result, sign);
  set_scale(&result, scale);
  return tmp;
}

int add_mantissa(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int overflow = 0;
  s21_decimal tmp_result = {0};

  for (int i = 0; i < MANTISSA_BITS_SIZE; ++i) {
    int bit_1 = get_bit(value_1, i);
    int bit_2 = get_bit(value_2, i);

    int sum = (bit_1 + bit_2 + overflow) % 2;
    overflow = (bit_1 + bit_2 + overflow) / 2;
    set_bit(&tmp_result, sum, i);
  }
  if (!overflow) {
    *result = tmp_result;
    result->bits[3] = value_1.bits[3];
  }
  return overflow;
}

int seven_signific(float src, int *scale) {
  long double seven_signific = fabs(src);
  *scale = 0;

  while (seven_signific < 1000000) {
    seven_signific *= 10;
    ++*scale;
  }
  while (seven_signific > 10000000) {
    seven_signific /= 10;
    --*scale;
  }

  return round(seven_signific);
}

int input_errors_float(float src, s21_decimal *dst) {
  int error = CONVERSION_OK;
  if (dst == NULL) {
    error = CONVERSION_ERROR;
  }

  if (NUMB_TOO_BIG || isnan(src)) {
    error = CONVERSION_ERROR;
  }

  if (NUMB_TOO_SMALL || isinf(src)) {
    reset_decimal(dst);
    error = CONVERSION_ERROR;
  }
  return error;
}

void alignment_scale(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal alignment_1 = *value_1;
  s21_decimal alignment_2 = *value_2;
  int scale_1 = get_scale(alignment_1);
  int scale_2 = get_scale(alignment_2);
  int overflow = 0;
  int difference = abs(scale_1 - scale_2);

  while (difference && !overflow) {
    difference = abs(scale_1 - scale_2);
    if (scale_1 > scale_2) {
      overflow = mult_ten(&alignment_2);
      if (!overflow) {
        scale_2++;
      }
    } else if (scale_1 < scale_2) {
      overflow = mult_ten(&alignment_1);
      if (!overflow) {
        scale_1++;
      }
    }
    if (!overflow) {
      --difference;
    }
  }

  while (difference) {
    difference = abs(scale_1 - scale_2);
    if (scale_1 > scale_2) {
      div_ten(&alignment_1);
      scale_1--;
    } else if (scale_1 < scale_2) {
      div_ten(&alignment_2);
      scale_2--;
    }
    --difference;
  }

  alignment_1.bits[3] &= SIGN_MASK;
  alignment_2.bits[3] &= SIGN_MASK;
  set_scale(&alignment_1, scale_1);
  set_scale(&alignment_2, scale_2);
  *value_1 = alignment_1;
  *value_2 = alignment_2;
}

int compare_mantissa(s21_decimal *value_1, s21_decimal *value_2) {
  int output = EQUAL;

  for (int i = MANTISSA_BITS_SIZE - 1; i >= 0 && !output; i--) {
    if (get_bit(*value_1, i) > get_bit(*value_2, i)) {
      output = GREATER;
    } else if (get_bit(*value_1, i) < get_bit(*value_2, i)) {
      output = LESS;
    }
  }

  return output;
}

void round_overflow(s21_decimal *tmp_value, int *sum_owerflow,
                    int *final_owerflow) {
  *sum_owerflow = 0;
  *final_owerflow = 0;
  int owerflow = 0;
  int scale = get_scale(*tmp_value);

  for (int i = 0; i < scale; ++i) {
    owerflow = div_ten(tmp_value);

    if (i == scale - 1) {
      *final_owerflow = owerflow;
    }
    *sum_owerflow += owerflow;
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<˚∆˚>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void reset_big_decimal(s21_big_decimal *big_dcml) {
  for (int i = 0; i < SIZE_BIG_STRUCT; ++i) big_dcml->bits[i] = 0;
}

int is_big_decimal_zero(s21_big_decimal *dcml) {
  if (!dcml->bits[0] && !dcml->bits[1] && !dcml->bits[2] && !dcml->bits[3] &&
      !dcml->bits[4] && !dcml->bits[5]) {
    dcml->sign = 0;  // sign at zero '+'
    return TRUE;
  }

  return FALSE;
}

void convert_to_big_decimal(s21_decimal value, s21_big_decimal *result) {
  reset_big_decimal(result);
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->scale = get_scale(value);
  result->sign = get_sign(value);
}

void set_bit_big_decimal(s21_big_decimal *big_dcml, unsigned int bit,
                         unsigned int order) {
  int i_struct = order / BITS_SIZE;
  int bit_order = order % BITS_SIZE;
  if (bit) {
    big_dcml->bits[i_struct] = big_dcml->bits[i_struct] | bit << bit_order;
  } else {
    big_dcml->bits[i_struct] = ~(~big_dcml->bits[i_struct] | !bit << bit_order);
  }
}

int get_bit_big_decimal(s21_big_decimal big_dcml, unsigned int order) {
  int i_struct = order / BITS_SIZE;
  int bit_order = order % BITS_SIZE;
  return (big_dcml.bits[i_struct] >> bit_order) & 1;
}

void left_shift_big_decimal(s21_big_decimal *big_dcml) {
  for (int i = SIZE_BIG_STRUCT - 1; i >= 0; --i) {
    big_dcml->bits[i] <<= 1;
    if (i > 0) {
      big_dcml->bits[i] += (big_dcml->bits[i - 1] >> (BITS_SIZE - 1)) & 1;
    }
  }
}

void copy_scale_and_sign_value(s21_big_decimal from_value,
                               s21_big_decimal *to_result) {
  to_result->scale = from_value.scale;
  to_result->sign = from_value.sign;
}

int compare_mantissa_big_decimal(s21_big_decimal *value_1,
                                 s21_big_decimal *value_2) {
  int output = EQUAL;

  for (int i = MANTISSA_BITS_SIZE - 1; i >= 0 && !output; i--) {
    if (get_bit_big_decimal(*value_1, i) > get_bit_big_decimal(*value_2, i)) {
      output = GREATER;
    } else if (get_bit_big_decimal(*value_1, i) <
               get_bit_big_decimal(*value_2, i)) {
      output = LESS;
    }
  }

  return output;
}

int is_less_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2) {
  int output = FALSE;

  unsigned int sign_1 = value_1.sign;
  unsigned int sign_2 = value_2.sign;
  int mode = 0;

  if ((sign_1 && is_big_decimal_zero(&value_2)) ||
      (is_big_decimal_zero(&value_1) && !sign_2) || (sign_1 > sign_2)) {
    output = TRUE;
  } else if (sign_1 == sign_2) {
    alignment_scale_big_decimal(&value_1, &value_2);
    mode = compare_mantissa_big_decimal(&value_1, &value_2);

    if ((sign_1 && mode == GREATER) || (!sign_1 && mode == LESS)) {
      output = TRUE;
    }
  }

  return output;
}

void modulo_values_big_decimal(s21_big_decimal *value_1,
                               s21_big_decimal *value_2) {
  value_1->sign = 0;
  value_2->sign = 0;
}

int subtracted_less(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  s21_big_decimal decimal_1 = *value_1;
  s21_big_decimal decimal_2 = *value_2;

  modulo_values_big_decimal(value_1, value_2);
  int subtracted_less = is_less_big_decimal(*value_1, *value_2);
  *value_1 = subtracted_less ? decimal_2 : decimal_1;
  *value_2 = subtracted_less ? decimal_1 : decimal_2;

  return subtracted_less;
}

int operations_sign(s21_big_decimal *value_1, s21_big_decimal *value_2,
                    int *sign_operations) {
  int less = subtracted_less(value_1, value_2);
  int sign_result = value_1->sign;

  if (*sign_operations) {
    if (less) {
      sign_result = value_1->sign ^ 1;
    }
    *sign_operations = (value_1->sign == value_2->sign) ? 1 : 0;
  } else {
    *sign_operations = (value_1->sign == value_2->sign) ? 0 : 1;
  }

  modulo_values_big_decimal(value_1, value_2);

  return sign_result;
}

int sub_mantissa_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result) {
  reset_big_decimal(result);
  int sub = 0;
  int occupy = 0;

  for (int i = 0; i < MANTISSA_BIG_BITS_SIZE; ++i) {
    int bit_1 = get_bit_big_decimal(value_1, i);
    int bit_2 = get_bit_big_decimal(value_2, i);

    if ((bit_1 - bit_2 - occupy) == 0) {
      sub = 0;
      occupy = 0;
    } else if ((bit_1 - bit_2 - occupy) == 1) {
      sub = 1;
    } else if ((bit_1 - bit_2 - occupy) == -1) {
      sub = 1;
      occupy = 1;
    } else if ((bit_1 - bit_2 - occupy) == -2) {
      sub = occupy ? 0 : 1;
    }

    set_bit_big_decimal(result, sub, i);
  }

  copy_scale_and_sign_value(value_1, result);
  return OK;
}

int add_mantissa_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result) {
  reset_big_decimal(result);
  int overflow = 0;

  for (int i = 0; i < MANTISSA_BIG_BITS_SIZE; ++i) {
    int bit_1 = get_bit_big_decimal(value_1, i);
    int bit_2 = get_bit_big_decimal(value_2, i);

    int sum = (bit_1 + bit_2 + overflow) % 2;
    overflow = (bit_1 + bit_2 + overflow) / 2;

    set_bit_big_decimal(result, sum, i);
  }

  copy_scale_and_sign_value(value_1, result);
  return OK;
}

void mult_ten_big_decimal(s21_big_decimal *big_dcml) {
  s21_big_decimal dcml_1 = {0};
  s21_big_decimal dcml_2 = {0};

  for (int i = 0; i < MANTISSA_BIG_BITS_SIZE; i++) {
    unsigned int dcml_bit = get_bit_big_decimal(*big_dcml, i);
    set_bit_big_decimal(&dcml_1, dcml_bit, i);
    set_bit_big_decimal(&dcml_2, dcml_bit, i);
  }

  for (int i = 0; i < 3; i++) {
    left_shift_big_decimal(&dcml_1);
  }
  left_shift_big_decimal(&dcml_2);

  copy_scale_and_sign_value(*big_dcml, &dcml_1);
  copy_scale_and_sign_value(*big_dcml, &dcml_2);

  add_mantissa_big_decimal(dcml_1, dcml_2, big_dcml);
}

void alignment_scale_big_decimal(s21_big_decimal *value_1,
                                 s21_big_decimal *value_2) {
  int diff_scale = abs(value_1->scale - value_2->scale);

  while (diff_scale) {
    if (value_1->scale > value_2->scale) {
      mult_ten_big_decimal(value_2);
      value_2->scale++;
    } else if (value_1->scale < value_2->scale) {
      mult_ten_big_decimal(value_1);
      value_1->scale++;
    }
    diff_scale = abs(value_1->scale - value_2->scale);
  }
}

int div_ten_big_decimal(s21_big_decimal *big_dcml) {
  int tmp = 0;
  s21_big_decimal result = {0};

  for (int i = MANTISSA_BIG_BITS_SIZE - 1; i >= 0; --i) {
    tmp *= 2;
    left_shift_big_decimal(&result);
    tmp += get_bit_big_decimal(*big_dcml, i);
    if (tmp >= 10) {
      tmp -= 10;
      result.bits[0] += 1;
    }
  }

  copy_scale_and_sign_value(*big_dcml, &result);
  *big_dcml = result;

  return tmp;
}

int div_ten_without_remainder_and_sub_scale(s21_decimal *dcml) {
  if (is_decimal_zero(dcml)) {
    return 0;
  }

  s21_decimal tmp_dcml = *dcml;
  int scale = get_scale(*dcml);
  unsigned int sing = get_sign(*dcml);

  while (!div_ten(&tmp_dcml)) {
    tmp_dcml = *dcml;

    if (!div_ten(&tmp_dcml)) {
      *dcml = tmp_dcml;
      --scale;
      set_scale(dcml, scale);
    }
  }

  set_sign(dcml, sing);
  set_scale(dcml, scale);

  return 0;
}

int convert_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result) {
  reset_decimal(result);
  int output = 0;
  if (!value.bits[3] && !value.bits[4] && !value.bits[5]) {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    set_sign(result, value.sign);
    set_scale(result, value.scale);
  } else {
    output = value.sign ? TOO_SMALL_OR_NEG_INF : TOO_LARGE_OR_INF;
  }
  return output;
}

int truncate_big_decimal(s21_big_decimal value, s21_big_decimal *result) {
  reset_big_decimal(result);
  *result = value;

  while (result->scale > 0) {
    div_ten_big_decimal(result);
    --result->scale;
  }

  result->sign = value.sign;

  return CALCULATION_OK;
}

int decimal_owerflow_error(s21_big_decimal dcml) {
  s21_decimal tmp_result = {0};
  s21_big_decimal result = {0};
  int output = FALSE;

  output = truncate_big_decimal(dcml, &result);

  if (!output) {
    output = convert_big_decimal_to_decimal(result, &tmp_result);
  }

  return output;
}

int bank_round(s21_big_decimal value, s21_decimal *result) {
  reset_decimal(result);

  s21_big_decimal tmp_value = {0};
  s21_decimal tmp_result = {0};
  s21_decimal round_owerflow = {0};
  tmp_value = value;

  int output = 0;
  int owerflow = 0;
  int sum_owerflow = 0;
  int final_owerflow = 0;

  output = convert_big_decimal_to_decimal(tmp_value, &tmp_result);

  if (output || tmp_value.scale > MAX_DEGREE) {
    for (int i = 0;
         (output && tmp_value.scale != 0) || tmp_value.scale > MAX_DEGREE;
         ++i) {
      owerflow = div_ten_big_decimal(&tmp_value);

      sum_owerflow += owerflow;
      --tmp_value.scale;

      output = convert_big_decimal_to_decimal(tmp_value, &tmp_result);

      if (i == value.scale - get_scale(tmp_result) - 1) {
        final_owerflow = owerflow;
      }
    }

    if (final_owerflow == 5) {
      round_owerflow.bits[0] = sum_owerflow == 5 ? tmp_value.bits[0] & 1 : 1;
    } else {
      round_owerflow.bits[0] = final_owerflow > 5 ? 1 : 0;
    }
  }

  if (!output) {
    add_mantissa(tmp_result, round_owerflow, result);
    set_sign(result, value.sign);
    set_scale(result, tmp_value.scale);
  }

  return output;
}

int add_sub_big_decimal(s21_decimal value_1, s21_decimal value_2,
                        int *sign_operations, s21_decimal *result) {
  reset_decimal(result);
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal tmp_result = {0};
  int output = 0;

  convert_to_big_decimal(value_1, &big_value_1);
  convert_to_big_decimal(value_2, &big_value_2);

  alignment_scale_big_decimal(&big_value_1, &big_value_2);

  int sign_result =
      operations_sign(&big_value_1, &big_value_2, sign_operations);

  if (*sign_operations) {
    sub_mantissa_big_decimal(big_value_1, big_value_2, &tmp_result);
  } else {
    add_mantissa_big_decimal(big_value_1, big_value_2, &tmp_result);
  }

  tmp_result.sign = sign_result;
  tmp_result.scale = big_value_1.scale;

  output = bank_round(tmp_result, result);

  is_decimal_zero(result);  // if zero, sign the zero with '+'

  return output;
}

int sign_for_mult_and_div(s21_big_decimal value_1, s21_big_decimal value_2) {
  return value_1.sign == value_2.sign ? 0 : 1;
}

void mult_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                      s21_big_decimal *result) {
  reset_big_decimal(result);
  result->scale = value_1.scale;
  s21_big_decimal tmp_value_1 = value_1;

  for (int i = MANTISSA_BIG_BITS_SIZE - 1; i >= 0; --i) {
    if (get_bit_big_decimal(value_2, i)) {
      for (int j = 0; j < i; ++j) {
        left_shift_big_decimal(&tmp_value_1);
      }

      add_mantissa_big_decimal(*result, tmp_value_1, result);
      tmp_value_1 = value_1;
    }
  }
}

int num_of_bits_in_the_decimal_value(s21_big_decimal big_dcml) {
  int number_of_bits = FALSE;
  for (int i = MANTISSA_BIG_BITS_SIZE - 1; i >= 0; --i) {
    if (get_bit_big_decimal(big_dcml, i)) {
      number_of_bits = i + 1;
      break;
    }
  }
  return number_of_bits;
}

int div_mantissa_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result) {
  value_1.scale = value_2.scale = 0;

  modulo_values_big_decimal(&value_1, &value_2);
  reset_big_decimal(result);
  s21_big_decimal tmp = {0};
  s21_big_decimal tmp_bit_value_1 = {0};
  const int empty_bits =
      MANTISSA_BIG_BITS_SIZE - num_of_bits_in_the_decimal_value(value_1);

  for (int i = MANTISSA_BIG_BITS_SIZE - 1; i >= 0; --i) {
    if (i - empty_bits >= 0) {
      left_shift_big_decimal(&tmp);
      left_shift_big_decimal(result);

      tmp_bit_value_1.bits[0] = get_bit_big_decimal(value_1, i - empty_bits);
      add_mantissa_big_decimal(tmp, tmp_bit_value_1, &tmp);

    } else if (i <= (empty_bits - 1) && is_less_big_decimal(tmp, value_2) &&
               !is_big_decimal_zero(&tmp) && result->scale < 56) {
      mult_ten_big_decimal(&tmp);
      mult_ten_big_decimal(result);
      ++result->scale;

    } else if (is_big_decimal_zero(&tmp)) {
      break;
    }

    if (!is_less_big_decimal(tmp, value_2)) {
      sub_mantissa_big_decimal(tmp, value_2, &tmp);
      result->bits[0] += 1;
    }
  }

  return CALCULATION_OK;
}

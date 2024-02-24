#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGN_MASK 0x80000000
#define SCALE_MASK 0xFF0000

#define SIZE_STRUCT 4
#define SIZE_BIG_STRUCT 6
#define BITS_SIZE 32
#define MANTISSA_BITS_SIZE 96
#define MANTISSA_BIG_BITS_SIZE 192
#define MAX_DEGREE 28

#define NUMB_TOO_SMALL (fabs(src) > 0.0 && fabs(src) < 1e-28)
#define NUMB_TOO_BIG (fabs(src) > 7.9228162514264337593543950335e28)

enum { OK, TOO_LARGE_OR_INF, TOO_SMALL_OR_NEG_INF, DIV_BY_ZERO };
enum { FALSE, TRUE };
enum { EQUAL, GREATER, LESS };
enum { CONVERSION_OK, CONVERSION_ERROR };
enum { CALCULATION_OK, CALCULATION_ERROR };
enum { FUNCTION_ADD, FUNCTION_SUB };

// Definition of the s21_decimal structure
typedef struct {
  unsigned int bits[SIZE_STRUCT];
} s21_decimal;

// Definition of the s21_big_decimal structure
typedef struct {
  unsigned int bits[SIZE_BIG_STRUCT];
  int scale;
  unsigned int sign;
} s21_big_decimal;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Convertors and Parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another Functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Decimal bitwise functions
void left_shift(s21_decimal *dcml);
int get_bit(s21_decimal dcml, unsigned int order);
void set_bit(s21_decimal *dcml, unsigned int bit, unsigned int order);
unsigned int get_sign(s21_decimal dcml);
void set_sign(s21_decimal *dcml, unsigned int sign);
int get_scale(s21_decimal dcml);
void set_scale(s21_decimal *dcml, int scale);
void reset_decimal(s21_decimal *dcml);
int is_decimal_zero(s21_decimal *dcml);

// Bitwise mantissa arithmetic
int mult_ten(s21_decimal *dcml);
int div_ten(s21_decimal *dcml);
int add_mantissa(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void alignment_scale(s21_decimal *value_1, s21_decimal *value_2);

// Auxiliary convertors and parsers
int seven_signific(float src, int *scale);
int input_errors_float(float src, s21_decimal *dst);

// Auxiliary comparison cperators
int compare_mantissa(s21_decimal *value_1, s21_decimal *value_2);

// Auxiliary another functions
void round_overflow(s21_decimal *tmp_value, int *sum_owerflow,
                    int *final_owerflow);

/// Big decimal bitwise functions
void left_shift_big_decimal(s21_big_decimal *big_dcml);
int get_bit_big_decimal(s21_big_decimal big_dcml, unsigned int order);
void set_bit_big_decimal(s21_big_decimal *big_dcml, unsigned int bit,
                         unsigned int order);
void reset_big_decimal(s21_big_decimal *big_dcml);
int is_big_decimal_zero(s21_big_decimal *dcml);
int num_of_bits_in_the_decimal_value(s21_big_decimal big_dcml);

/// Auxiliary arithmetic operators
int compare_mantissa_big_decimal(s21_big_decimal *value_1,
                                 s21_big_decimal *value_2);
int is_less_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2);
void alignment_scale_big_decimal(s21_big_decimal *value_1,
                                 s21_big_decimal *value_2);
int decimal_owerflow_error(s21_big_decimal dcml);
int truncate_big_decimal(s21_big_decimal value, s21_big_decimal *result);
int bank_round(s21_big_decimal value, s21_decimal *result);

int operations_sign(s21_big_decimal *value_1, s21_big_decimal *value_2,
                    int *sign_operations);
int subtracted_less(s21_big_decimal *value_1, s21_big_decimal *value_2);
int sub_mantissa_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result);
int add_sub_big_decimal(s21_decimal value_1, s21_decimal value_2,
                        int *sign_operations, s21_decimal *result);

int add_mantissa_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result);

int sign_for_mult_and_div(s21_big_decimal value_1, s21_big_decimal value_2);
void mult_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                      s21_big_decimal *result);
void mult_ten_big_decimal(s21_big_decimal *big_dcml);

int div_ten_big_decimal(s21_big_decimal *big_dcml);
int div_ten_without_remainder_and_sub_scale(s21_decimal *dcml);
int div_mantissa_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result);

/// Big decimal other
void modulo_values_big_decimal(s21_big_decimal *value_1,
                               s21_big_decimal *value_2);
void convert_to_big_decimal(s21_decimal value, s21_big_decimal *result);
void copy_scale_and_sign_value(s21_big_decimal from_value,
                               s21_big_decimal *to_result);
int convert_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result);

#endif /* S21_DECIMAL_H */

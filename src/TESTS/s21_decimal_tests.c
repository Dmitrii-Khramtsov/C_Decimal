#include "s21_decimal_tests.h"

int main() {
  int fail = 0;
  Suite *s21_decimal_test[] = {

      test_add(),           test_sub(),       test_mul(),
      test_div(),           test_negate(),

      test_int2dec(),       test_dec2int(),

      test_float2dec(),     test_dec2float(),

      test_equal(),         test_notequal(),  test_greater(),
      test_greater_equal(), test_less(),      test_less_equal(),

      test_truncate(),      test_round(),     test_floor(),

  };

  int sizeof_test_suite = sizeof(s21_decimal_test) / sizeof(*s21_decimal_test);

  for (int i = 0; i < sizeof_test_suite; i++) {
    SRunner *test_set_runner = srunner_create(s21_decimal_test[i]);
    srunner_set_fork_status(test_set_runner, CK_NOFORK);
    srunner_run_all(test_set_runner, CK_NORMAL);  // prevents leaks
    fail += srunner_ntests_failed(test_set_runner);
    srunner_free(test_set_runner);
  }

  return fail == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

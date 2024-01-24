// Copyright [2023] jupitere
#include "./tests.h"

int main(void) {
  SRunner *srunner = srunner_create(get_notation_suite());
  int counted_errors = 0;

  srunner_add_suite(srunner, get_unary_minus());
  srunner_add_suite(srunner, get_unary_plus());
  srunner_add_suite(srunner, get_math_func());
  srunner_add_suite(srunner, get_calc_suite());

  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  counted_errors = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return counted_errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

// Copyright [2023] jupitere
#ifndef SRC_S21_TESTS_H_
#define SRC_S21_TESTS_H_
#include <check.h>
#include "./s21_calc.h"

#define SUITE_NAME "Unit"
#define TCASE_NAME "Tests"
#define EPS 1e-7

#define TEST1 "1 + 3 * 2 - (2 / 1)"
#define TEST2 "(1 + 2) * 3 + (3 - 1)"
#define TEST3 "(1 + (2 - 1) * 3) / 5 * 2 + 1"
#define TEST4 "(1 + 3 * 3 - (2 / 1))"
#define TEST5 "(1 + 3 * 2 - (2 / 1)) / 5 mod 3 + ((3 - 1) * 5)"
#define TEST6 "(1 / (2) + 1)"
#define TEST7 "1 + 2"
#define TEST8 "2 - 1"
#define TEST9 "2 * 1"
#define TEST10 "2 / 1"
#define TEST11 "3 mod 2"

#define RES1 "1 3 2 * + 2 1 / -"
#define RES2 "1 2 + 3 * 3 1 - +"
#define RES3 "1 2 1 - 3 * + 5 / 2 * 1 +"
#define RES4 "1 3 3 * + 2 1 / -"
#define RES5 "1 3 2 * + 2 1 / - 5 / 3 m 3 1 - 5 * +"
#define RES6 "1 2 / 1 +"

Suite *get_notation_suite(void);
Suite *get_unary_minus(void);
Suite *get_unary_plus(void);
Suite *get_math_func(void);
Suite *get_calc_suite(void);

#endif  // SRC_S21_TESTS_H_
// Copyright [2023] jupitere
#include "../tests.h"

START_TEST(calc_test_1) {
  char str[SIZE_STR] = {0};
  int status = OK;
  char test[] = "1 + 3";
  double res = 0;
  ck_assert_int_eq(OK, convert_polish_notation(test, str));
  status = calc(str, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(4.0, res);
}
END_TEST

START_TEST(calc_test_2) {
  char str[SIZE_STR] = {0};
  int status = OK;
  char test[] = "1 - 3";
  double res = 0;
  ck_assert_int_eq(OK, convert_polish_notation(test, str));
  status = calc(str, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(-2, res);
}
END_TEST

START_TEST(calc_test_3) {
  char str[SIZE_STR] = {0};
  int status = OK;
  char test[] = "1 * 3";
  double res = 0;
  ck_assert_int_eq(OK, convert_polish_notation(test, str));
  status = calc(str, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(3.0, res);
}
END_TEST

START_TEST(calc_test_4) {
  char str[SIZE_STR] = {0};
  int status = OK;
  char test[] = "1 / 3";
  double res = 0;
  ck_assert_int_eq(OK, convert_polish_notation(test, str));
  status = calc(str, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(1. / 3, res);
}
END_TEST

START_TEST(calc_test_5) {
  int status = OK;
  char test[] = "10 mod 3";
  double res = 0;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(1, res);
}
END_TEST

START_TEST(calc_test_6) {
  int status = OK;
  char test[] = "1 ^ 3";
  double res = 0;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(1.0, res);
}
END_TEST

START_TEST(calc_test_7) {
  int status = OK;
  char test[] = "(+1) + (+3) * (+2)";
  double res = 0;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(7.0, res);
}
END_TEST

START_TEST(calc_test_8) {
  char test[] = "(-1.3) + (-3.541) * (-2.860)";
  double res = 0, check = -1.3 + -3.541 * -2.860;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  if (fabs(check - res) >= EPS) status = NOT_EQUAL;
  ck_assert_double_eq(OK, status);
}
END_TEST

START_TEST(calc_test_9) {
  char test[] = "1 + 3 * 2 mod (2 / 1) ^ 2";
  double res = 0, check = fmod(1 + 3 * 2, pow((2 / 1), 2));
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_10) {
  char test[] = "1 ^ 2 + 3 * 2 mod (2 / 1) / 2";
  double res = 0, check = pow(1, 2) + 3 * 2 % (2 / 1) / 2;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_11) {
  char test[] = "(1 + 3 * cos(2 - (2 / 1)) / 5 mod 3 + (3 - 1) * 5)";
  double res = 0, check = (1 + 3 * fmod(cos(2 - (2 / 1)) / 5, 3) + (3 - 1) * 5);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_12) {
  char test[] = "1 + sin(3 * 2 - (2 / 1))";
  double res = 0, check = 1 + sin(3 * 2 - (2 / 1.));
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_13) {
  char test[] = "(1 + 3 * 2 - (tan(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  double res = 0,
         check = fmod((1 + 3 * 2 - (tan(2) / 1)) / 5, 3) + ((3 - 1) * 5);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_14) {
  char test[] = "(1 + 3 * 2 - (acos(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  double res = 0;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(ERROR, status);
}
END_TEST

START_TEST(calc_test_15) {
  char test[] = "(1 + 3 * asin(2 - (2 / 1) / 5 mod 3 + (3 - 1) * 5))";
  double res = 0;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(ERROR, status);
}
END_TEST

START_TEST(calc_test_16) {
  char test[] = "(1 + 3 * 2 - (atan(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  double res = 0,
         check = fmod((1 + 3 * 2 - (atan(2) / 1)) / 5, 3) + ((3 - 1) * 5);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_17) {
  char test[] = "1 + sqrt(3 * 2) - (2 / 1)";
  double res = 0, check = 1 + sqrt(3 * 2) - (2 / 1);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_18) {
  char test[] = "ln((1 + 3 * 2 - (2 / 1)) / 5 mod (+3) + ((3 - 1) * 5))";
  double res = 0,
         check = log(fmod((1 + 3 * 2 - (2 / 1)) / 5, 3) + ((3 - 1) * 5));
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_19) {
  char test[] = "1 + log(3 * 2 - (2 / 1))";
  double res = 0, check = 1 + log10(3 * 2 - (2 / 1));
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_20) {
  char test[] = "(1 + 2) * acos(0.1) - (2 / 1)";
  double res = 0, check = (1 + 2) * acos(0.1) - (2 / 1);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_21) {
  char test[] = "(1 + 2) * asin(0.9) - (2 / 1)";
  double res = 0, check = (1 + 2) * asin(0.9) - (2 / 1);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_22) {
  char test[] = "3 + -2 ^ 3 / 5";
  double res = 0;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
}
END_TEST

START_TEST(calc_test_23) {
  char test[] = "3 + -2 ^ 3 / 5 + x";
  double res = 0, check = 3 + pow(-2, 3) / 5 + 0;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_24) {
  char test[] = "-x + 3 + -2 ^ 3 / 5";
  double res = 0, check = -0 + 3 + pow(-2, 3) / 5;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_25) {
  char test[] = "(-x) + (1 + 2) * acos(0.1) - (2 / 1)";
  double res = 0, check = -3 + (1 + 2) * acos(0.1) - (2 / 1);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 3);
  ck_assert_int_eq(OK, status);
  ck_assert_double_eq(check, res);
}
END_TEST

START_TEST(calc_test_26) {
  char test[] = "x / 0";
  double res = 0;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(DIVISION_BY_ZERO, status);
}
END_TEST

START_TEST(calc_test_27) {
  char test[] = "sqrt(-4)";
  double res = 0;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(ERROR, status);
}
END_TEST

START_TEST(calc_test_28) {
  char test[] = "sin(1) + 3 * 2 - (2 / 1)";
  double res = 0, check = sin(1) + 3 * 2 - (2 / 1);
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(OK, status);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(calc_test_29) {
  char test[] = "2 ^ (-3)";
  double res = 0;
  int status = OK;
  char exp[SIZE_STR] = {0};
  convert_polish_notation(test, exp);
  status = calc(exp, &res, 0);
  ck_assert_int_eq(ERROR, status);
}
END_TEST

Suite *get_calc_suite(void) {
  Suite *s = suite_create("Calc_tests");
  TCase *tc = tcase_create(TCASE_NAME);
  suite_add_tcase(s, tc);

  tcase_add_test(tc, calc_test_1);
  tcase_add_test(tc, calc_test_2);
  tcase_add_test(tc, calc_test_3);
  tcase_add_test(tc, calc_test_4);
  tcase_add_test(tc, calc_test_5);
  tcase_add_test(tc, calc_test_6);
  tcase_add_test(tc, calc_test_7);
  tcase_add_test(tc, calc_test_8);
  tcase_add_test(tc, calc_test_9);
  tcase_add_test(tc, calc_test_10);
  tcase_add_test(tc, calc_test_11);
  tcase_add_test(tc, calc_test_12);
  tcase_add_test(tc, calc_test_13);
  tcase_add_test(tc, calc_test_14);
  tcase_add_test(tc, calc_test_15);
  tcase_add_test(tc, calc_test_16);
  tcase_add_test(tc, calc_test_17);
  tcase_add_test(tc, calc_test_18);
  tcase_add_test(tc, calc_test_19);
  tcase_add_test(tc, calc_test_20);
  tcase_add_test(tc, calc_test_21);
  tcase_add_test(tc, calc_test_22);
  tcase_add_test(tc, calc_test_23);
  tcase_add_test(tc, calc_test_24);
  tcase_add_test(tc, calc_test_25);
  tcase_add_test(tc, calc_test_26);
  tcase_add_test(tc, calc_test_27);
  tcase_add_test(tc, calc_test_28);
  tcase_add_test(tc, calc_test_29);

  return s;
}

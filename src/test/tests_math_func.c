// Copyright [2023] jupitere
#include "../tests.h"

START_TEST(sin_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "sin(4)";
  const char res[] = "4 s";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "sin(1) + 3 * 2 - (2 / 1)";
  const char res[] = "1 s 3 2 * + 2 1 / -";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_3) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + 3 * 2 - sin(2 / 1)";
  const char res[] = "1 3 2 * + 2 1 / s -";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_4) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + sin(3) * 2 - (2 / 1)";
  const char res[] = "1 3 s 2 * + 2 1 / -";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_5) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + 3 * sin(2) - (2 / 1)";
  const char res[] = "1 3 2 s * + 2 1 / -";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_6) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + sin(3 * 2) - (2 / 1)";
  const char res[] = "1 3 2 * s + 2 1 / -";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_7) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + sin(3 * 2 - (2 / 1))";
  const char res[] = "1 3 2 * 2 1 / - s +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_8) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "sin((1 + 3 * 2 - (2 / 1)) / 5 mod 3 + ((3 - 1) * 5))";
  const char res[] = "1 3 2 * + 2 1 / - 5 / 3 m 3 1 - 5 * + s";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_9) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * 2 - (2 / 1)) / 5 mod 3 + sin((3 - 1) * 5)";
  const char res[] = "1 3 2 * + 2 1 / - 5 / 3 m 3 1 - 5 * s +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_10) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * 2 - (sin(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  const char res[] = "1 3 2 * + 2 s 1 / - 5 / 3 m 3 1 - 5 * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sin_test_11) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * 2 - (2 / 1)) / sin(5 mod 3) + ((3 - 1) * 5)";
  const char res[] = "1 3 2 * + 2 1 / - 5 3 m s / 3 1 - 5 * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(cos_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * cos(2 - (2 / 1))) / 5 mod 3 + ((3 - 1) * 5)";
  const char res[] = "1 3 2 2 1 / - c * + 5 / 3 m 3 1 - 5 * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(cos_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * cos(2 - (2 / 1) / 5 mod 3 + (3 - 1) * 5)";
  const char res[] = "1 3 2 2 1 / 5 / 3 m - 3 1 - 5 * + c * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(tan_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * tan(2 - (2 / 1) / 5 mod 3 + (3 - 1) * 5)";
  const char res[] = "1 3 2 2 1 / 5 / 3 m - 3 1 - 5 * + t * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(tan_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * 2 - (tan(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  const char res[] = "1 3 2 * + 2 t 1 / - 5 / 3 m 3 1 - 5 * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(acos_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * acos(2 - (2 / 1) / 5 mod 3 + (3 - 1) * 5)";
  const char res[] = "1 3 2 2 1 / 5 / 3 m - 3 1 - 5 * + o * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(acos_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * 2 - (acos(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  const char res[] = "1 3 2 * + 2 o 1 / - 5 / 3 m 3 1 - 5 * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(asin_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * asin(2 - (2 / 1) / 5 mod 3 + (3 - 1) * 5)";
  const char res[] = "1 3 2 2 1 / 5 / 3 m - 3 1 - 5 * + i * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(asin_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "((+1) + 3 * 2 - (asin(2) / 1)) / 5 mod 3 + ((3 - 1) * (-5))";
  const char res[] = "1+ 3 2 * + 2 i 1 / - 5 / 3 m 3 1 - 5- * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(atan_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * atan(2 - (2 / 1) / 5 mod 3 + (3 - 1) * 5)";
  const char res[] = "1 3 2 2 1 / 5 / 3 m - 3 1 - 5 * + a * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(atan_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * 2 - (atan(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  const char res[] = "1 3 2 * + 2 a 1 / - 5 / 3 m 3 1 - 5 * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sqrt_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + sqrt(3 * 2) - (2 / 1)";
  const char res[] = "1 3 2 * q + 2 1 / -";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(sqrt_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(1 + 3 * 2 - (sqrt(2) / 1)) / 5 mod 3 + ((3 - 1) * 5)";
  const char res[] = "1 3 2 * + 2 q 1 / - 5 / 3 m 3 1 - 5 * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(ln_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + ln(3 * 2 - (2 / 1))";
  const char res[] = "1 3 2 * 2 1 / - l +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(ln_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "ln((1 + 3 * 2 - (2 / 1)) / 5 mod (+3) + ((3 - 1) * 5))";
  const char res[] = "1 3 2 * + 2 1 / - 5 / 3+ m 3 1 - 5 * + l";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(log_test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + log(3 * 2 - (2 / 1))";
  const char res[] = "1 3 2 * 2 1 / - g +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(log_test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "log((1 + 3 * (-2) - (2 / 1)) / 5 mod 3 + ((3 - 1) * 5))";
  const char res[] = "1 3 2- * + 2 1 / - 5 / 3 m 3 1 - 5 * + g";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

Suite *get_math_func(void) {
  Suite *s = suite_create("Math_func");
  TCase *tc = tcase_create(TCASE_NAME);
  suite_add_tcase(s, tc);

  tcase_add_test(tc, sin_test_1);
  tcase_add_test(tc, sin_test_2);
  tcase_add_test(tc, sin_test_3);
  tcase_add_test(tc, sin_test_4);
  tcase_add_test(tc, sin_test_5);
  tcase_add_test(tc, sin_test_6);
  tcase_add_test(tc, sin_test_7);
  tcase_add_test(tc, sin_test_8);
  tcase_add_test(tc, sin_test_9);
  tcase_add_test(tc, sin_test_10);
  tcase_add_test(tc, sin_test_11);

  tcase_add_test(tc, cos_test_1);
  tcase_add_test(tc, cos_test_2);
  tcase_add_test(tc, tan_test_1);
  tcase_add_test(tc, tan_test_2);
  tcase_add_test(tc, acos_test_1);
  tcase_add_test(tc, acos_test_2);
  tcase_add_test(tc, asin_test_1);
  tcase_add_test(tc, asin_test_2);
  tcase_add_test(tc, atan_test_1);
  tcase_add_test(tc, atan_test_2);
  tcase_add_test(tc, sqrt_test_1);
  tcase_add_test(tc, sqrt_test_2);
  tcase_add_test(tc, ln_test_1);
  tcase_add_test(tc, ln_test_2);
  tcase_add_test(tc, log_test_1);
  tcase_add_test(tc, log_test_2);

  return s;
}

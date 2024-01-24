// Copyright [2023] jupitere
#include "../tests.h"

START_TEST(test_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  convert_polish_notation(TEST1, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (RES1[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  convert_polish_notation(TEST2, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (RES2[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_3) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  convert_polish_notation(TEST3, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (RES3[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_4) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  convert_polish_notation(TEST4, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (RES4[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_5) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  convert_polish_notation(TEST5, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (RES5[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_6) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  convert_polish_notation(TEST6, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (RES6[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_7) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  const char res[] = "1 2 +";
  convert_polish_notation(TEST7, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_8) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  const char res[] = "2 1 -";
  convert_polish_notation(TEST8, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_9) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  const char res[] = "2 1 *";
  convert_polish_notation(TEST9, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_10) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  const char res[] = "2 1 /";
  convert_polish_notation(TEST10, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_11) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  const char res[] = "3 2 m";
  convert_polish_notation(TEST11, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_12) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + 3 * 2 mod (2 / 1) ^ 2";
  const char res[] = "1 3 2 * 2 1 / 2 ^ m +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_13) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 ^ 2 + 3 * 2 mod (2 / 1) / 2";
  const char res[] = "1 2 ^ 3 2 * 2 1 / m 2 / +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_14) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 ^ 2 + 3 * 2 mod (2 / 1)";
  const char res[] = "1 2 ^ 3 2 * 2 1 / m +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_15) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(-1.3) + (-3.541) * (-2.860)";
  const char res[] = "1.3- 3.541- 2.860- * +";
  convert_polish_notation(test, str);
  printf("%s\n", str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(test_16) {
  char str[SIZE_STR] = {0};
  char test[] = "((1 ^ 2) + 3)) * 2 mod (2 / 1)";
  int status = convert_polish_notation(test, str);
  ck_assert_int_eq(status, UNCORRECT_BRACKETS);
}
END_TEST

Suite *get_notation_suite(void) {
  Suite *s = suite_create("Polish_notation");
  TCase *tc = tcase_create(TCASE_NAME);
  suite_add_tcase(s, tc);

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);

  return s;
}

START_TEST(unary_minus_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(-1) + 3";
  const char res[] = "1- 3 +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(unary_minus_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + (-3)";
  const char res[] = "1 3- +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(unary_minus_3) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(-1) + (-3) * (-2)";
  const char res[] = "1- 3- 2- * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(unary_minus_4) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(-1.3) + (-3.54) * (-2.860)";
  const char res[] = "1.3- 3.54- 2.860- * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

Suite *get_unary_minus(void) {
  Suite *s = suite_create("Unary_minus");
  TCase *tc = tcase_create(TCASE_NAME);
  suite_add_tcase(s, tc);

  tcase_add_test(tc, unary_minus_1);
  tcase_add_test(tc, unary_minus_2);
  tcase_add_test(tc, unary_minus_3);
  tcase_add_test(tc, unary_minus_4);

  return s;
}

START_TEST(unary_plus_1) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(+1) + 3";
  const char res[] = "1+ 3 +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(unary_plus_2) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "1 + (+3)";
  const char res[] = "1 3+ +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(unary_plus_3) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(+1) + (+3) * (+2)";
  const char res[] = "1+ 3+ 2+ * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

START_TEST(unary_plus_4) {
  char str[SIZE_STR] = {0};
  int eq = 1;
  char test[] = "(+1.3) + (+3.54) * (+2.860)";
  const char res[] = "1.3+ 3.54+ 2.860+ * +";
  convert_polish_notation(test, str);
  for (size_t i = 0; i < strlen(str); i++)
    if (res[i] != str[i]) eq = 0;
  ck_assert_int_eq(1, eq);
}
END_TEST

Suite *get_unary_plus(void) {
  Suite *s = suite_create("Unary_plus");
  TCase *tc = tcase_create(TCASE_NAME);
  suite_add_tcase(s, tc);

  tcase_add_test(tc, unary_plus_1);
  tcase_add_test(tc, unary_plus_2);
  tcase_add_test(tc, unary_plus_3);
  tcase_add_test(tc, unary_plus_4);

  return s;
}

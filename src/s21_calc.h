// Copyright [2023] jupitere
#ifndef S21_CALC_H_
#define S21_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STR 512

typedef struct Stack {
  char operation;
  struct Stack *next;
} Stack_t;

typedef struct Node {
  double num;
  struct Node *next;
} Node_t;

typedef enum {
  OK,
  ALLOCATE,
  UNCORRECT_BRACKETS,
  END_STACK,
  END_BRACKETS,
  END_EQUAL,
  END_LESS,
  DIVISION_BY_ZERO,
  NOT_EQUAL,
  ERROR,
  ERR_X_VALUE,
} Status;

typedef enum {
  ADD = 43,
  SUB = 45,
  MUL = 42,
  DIV = 47,
  MOD = 109,
  DEG = 94,
  COS = 99,
  SIN = 115,
  TAN = 116,
  ACOS = 111,
  ASIN = 105,
  ATAN = 97,
  SQRT = 113,
  LN = 108,
  LOG = 103
} Operations;

typedef enum { OPEN = 40, CLOSE = 41 } Brackets;

int check_brackets(char expression[]);
int convert_polish_notation(char str[], char res_str[]);

/**
 * @brief take from the stack while ch_put is equal to the first element of
 * stack
 * @return END_EQUAL
 */
int _take_while_equal(Stack_t *stack, size_t *size, size_t *len, char *res,
                      char ch_put);
/**
 * @return END_STACK
 */
int _take_everything_from_stack(Stack_t *stack, size_t *size, size_t *len,
                                char *res);
/**
 * @brief take from stack while the first element of stack isn't equal to
 * openning brace
 * @return END_BRACKETS
 */
int _take_until_brace(Stack_t *stack, size_t *size, size_t *len, char *res);
/**
 * @brief take while first element of stack less than ch_put
 * @return END_LESS
 */
int _take_while_less(Stack_t *stack, size_t *size, size_t *len, char *res,
                     char ch_put);
/**
 * @brief adding element num in the Stack_t
 * @return 0 is OK \
 * @return 1 is Stack_t not exists \
 * @return 2 is num is uncorrect
 */
int push(Stack_t **stack, char operation);
char pop(Stack_t **stack);
char peek(Stack_t *stack);
void print(Stack_t *stack);
void remove_stack(Stack_t **stack);
int is_digit(char ch);
double s21_atof(const char str[], size_t *i);
int create(Stack_t **stack);
/**
 * @return 1 if ch > first opration in the stack \
 * @return 3 if ch = ')' \
 * @return 0 otherwise
 */
int _is_greater(Stack_t *stack, char ch);
/**
 * @return 1 if ch <= first operation in the stack \
 * @return 0 otherwise
 */
int _is_less(Stack_t *stack, char ch);
/**
 * @return 1 if ch == first operation in the stack \
 * @return 0 otherwise
 */
int _is_equal(Stack_t *stack, char ch);

/**
 * @brief take a number from a string as a string and push it onto the Stack_t
 * @return status
 */
int put_in_stack(char str[], size_t *i, size_t len, Stack_t **operands);
int _check_double(int res, size_t len);
int _is_negative_number(char str[], size_t *i);
size_t strcat_num(char *destination, const char *append);
int _is_dot(const char *str, size_t i);
/**
 * @brief if is_less_or_equal is equal to 1, then pop the stack up to the
 * openning curly brace if is_less_or_equal is equal to 0, then pop evething
 * from the whole stack
 * @param is_less_or_equal is equal to 2 - first element of stack greater than
 * input
 */
int _take_from_stack(Stack_t *stack, size_t *size, char *res, int is_less_or_eq,
                     char ch_put);
/**
 * @return operator from operations struct \
 * @return 0 otherwise
 */
int get_operator(char *str, size_t *i);
// return operator of function
int _get_func_operator(char *str, size_t *i);
int _get_cos_sin_tan(const char *str, size_t *i);
int _is_heigh(char ch);
int create_node(Node_t **node);
int push_node(Node_t **node, double num);
double pop_node(Node_t **node);
void delete_node(Node_t **node, int *size);
int is_unary_operator(char operation);

/**
 * @brief calculate expression the str
 * @return status OK or other status
 */
int calc(char *str, double *res, double x);
/**
 * @brief calculate binary operations
 * @return OK \
 * @return DIVISION BY ZERO \
 * @return
 */
int calculate_double(Node_t *node, int *size, char operation, double *res);
/**
 * @brief calculate values
 * @return result of calculate
 */
double switch_arithmetic(double num1, double num2, char operation);
void print_node(Node_t *node);
/**
 * @brief check ch, if it is operation return operation othewise return 0
 * @return char - operation \
 * @return 0 otherwise
 */
int _take_operation(char ch);
/**
 * @brief calculate unary operations
 * @return OK \
 * @return ERROR if invalid operation
 */
int calculate_unary(Node_t *node, int *size, char operation, double *res);
/**
 * @brief calculate values for math functions
 * @return result of calculate
 */
double switch_unary(double num, char operation);
int is_nan(double num, char operation);

#endif  // S21_CALC_H_

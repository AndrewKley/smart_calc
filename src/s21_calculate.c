// Copyright [2023] jupitere
#include "./s21_calc.h"

int calc(char *str, double *res, double x) {
  Status status = OK;
  Node_t *node = NULL;
  create_node(&node);
  int size = 0;
  for (size_t i = 0; i < strlen(str) && status == OK; i++) {
    if (is_digit(str[i]) || str[i] == 'x') {
      double num = 0;
      if (str[i] != 'x') {
        num = s21_atof(str, &i);
      } else {
        num = x;
        i++;
      }
      if (str[i] == '-') num *= -1;
      if (str[i] == '+' || str[i] == '-') i++;
      push_node(&node, num);
      size++;
    }
    int operation = _take_operation(str[i]);
    if (operation) {
      // take a numbers or a number from the stack and perform an operation
      if (is_unary_operator(operation)) {
        if (size) {
          double res_unary = 0;
          if ((status = calculate_unary(node, &size, operation, &res_unary)) ==
              OK) {
            push_node(&node, res_unary);
            size++;
          }
        }
      } else {
        if (size >= 2) {
          double res_double = 0;
          if ((status = calculate_double(node, &size, operation,
                                         &res_double)) == OK) {
            push_node(&node, res_double);
            size++;
          }
        }
      }
    }
    if (status != OK) break;
  }
  if (status == OK) {
    *res = node->next->num;
    delete_node(&node, &size);
  } else {
    delete_node(&node, &size);
  }
  return status;
}

int calculate_unary(Node_t *node, int *size, char operation, double *res) {
  Status status = OK;
  if (*size && res) {
    double num = pop_node(&node);
    (*size)--;
    status = is_nan(num, operation);
    if (status == OK) *res = switch_unary(num, operation);
  }
  return status;
}

double switch_unary(double num, char operation) {
  double res = 0;
  switch (operation) {
    case COS:
      res = cos(num);
      break;
    case SIN:
      res = sin(num);
      break;
    case TAN:
      res = tan(num);
      break;
    case ACOS:
      res = acos(num);
      break;
    case ASIN:
      res = asin(num);
      break;
    case ATAN:
      res = atan(num);
      break;
    case SQRT:
      res = sqrt(num);
      break;
    case LN:
      res = log(num);
      break;
    case LOG:
      res = log10(num);
      break;
  }
  return res;
}

int calculate_double(Node_t *node, int *size, char operation, double *res) {
  Status status = OK;
  if (*size >= 2 && res) {
    double num_second = pop_node(&node);
    double num_first = pop_node(&node);
    (*size) -= 2;
    if (num_second == 0. && operation == DIV)
      status = DIVISION_BY_ZERO;
    else if ((num_second < 0. || num_first == 0.) && operation == DEG)
      status = ERROR;
    else if (num_first < 0 && operation == DEG && status == OK)
      *res = switch_arithmetic(num_first, (int)num_second, operation);
    else
      *res = switch_arithmetic(num_first, num_second, operation);
  }
  return status;
}

double switch_arithmetic(double num1, double num2, char operation) {
  double res = 0;
  switch (operation) {
    case ADD:
      res = num1 + num2;
      break;
    case SUB:
      res = num1 - num2;
      break;
    case MUL:
      res = num1 * num2;
      break;
    case DIV:
      res = num1 / num2;
      break;
    case MOD:
      res = fmod(num1, num2);
      break;
    case DEG:
      res = pow(num1, num2);
      break;
  }
  return res;
}

int _take_operation(char ch) {
  int is_operation = 0;
  if (ch == ADD || ch == SUB || ch == MUL) is_operation = 1;
  if (ch == DIV || ch == MOD || ch == DEG) is_operation = 1;
  if (ch == COS || ch == SIN || ch == TAN) is_operation = 1;
  if (ch == ACOS || ch == ASIN || ch == ATAN) is_operation = 1;
  if (ch == SQRT || ch == LN || ch == LOG) is_operation = 1;
  return is_operation ? ch : 0;
}

int is_unary_operator(char operation) {
  int is_unary = 0;
  if (operation == COS || operation == SIN) is_unary = 1;
  if (operation == TAN || operation == LOG) is_unary = 1;
  if (operation == ACOS || operation == ASIN) is_unary = 1;
  if (operation == ATAN || operation == SQRT) is_unary = 1;
  if (operation == LN) is_unary = 1;

  return is_unary;
}

int is_nan(double num, char operation) {
  Status is_nan = OK;
  if (operation == SQRT && num < 0) is_nan = ERROR;
  if ((operation == ASIN || operation == ACOS) && (num < -1 || num > 1))
    is_nan = ERROR;
  if ((operation == LN || operation == LOG) && num < 0) is_nan = ERROR;
  return is_nan;
}

// Copyright [2023] jupitere
#include "./s21_calc.h"

int convert_polish_notation(char str[], char res_str[]) {
  Status status = OK;
  Stack_t *operations = NULL;
  create(&operations);
  size_t len = strlen(str), stack_size = 0;
  if ((status = check_brackets(str)) != OK) {
  }
  for (size_t i = 0; i < len && status == OK; i++) {
    int is_sign = 0;
    if ((str[i] == SUB || str[i] == ADD) && i < len - 1 && is_digit(str[i + 1]))
      if (i > 0 && str[i - 1] == '(') is_sign = 1;
    if (is_digit(str[i]) || is_sign) {
      size_t i_res = 0;
      i_res += strcat_num(res_str, str + i) - 1;
      i += i_res;
      strcat(res_str, " ");
    }
    int is_operator = get_operator(str, &i);
    if (is_operator || str[i] == CLOSE || str[i] == OPEN) {
      if (is_operator == 0 && (str[i] == CLOSE || str[i] == OPEN))
        is_operator = str[i];
      int is_greater_or_eq = _is_greater(operations, is_operator);
      if (is_greater_or_eq == 1 || str[i] == OPEN) {
        push(&operations, is_operator);
        stack_size++;
      } else {
        // take as long as str[i] less than first element of stack
        // or str[i] is equal to '('
        int is_less_or_eq = is_operator == CLOSE ? 1 : 0;
        if (_is_less(operations, is_operator)) is_less_or_eq = 2;
        if (_is_equal(operations, is_operator)) is_less_or_eq = 3;
        _take_from_stack(operations, &stack_size, res_str, is_less_or_eq,
                         is_operator);
        if (is_operator != CLOSE) {
          push(&operations, is_operator);
          stack_size++;
        }
      }
    }
  }
  _take_from_stack(operations, &stack_size, res_str, 0, 0);
  res_str[strlen(res_str) != 0 ? strlen(res_str) - 1 : 0] = 0;
  remove_stack(&operations);
  return status;
}

int get_operator(char *str, size_t *i) {
  size_t len = strlen(str);
  int is_low = str[*i] == ADD || str[*i] == SUB;
  int is_mid = str[*i] == MUL || str[*i] == DIV;
  int is_heigh = str[*i] == DEG;
  int ch = 0, MAX_OPERATOR_LEN = 4;
  if (is_low || is_mid || is_heigh) ch = str[*i];
  if (ch == 0 && (*i) + MAX_OPERATOR_LEN < len) {
    if (str[*i] == 'm' && str[(*i) + 1] == 'o' && str[(*i) + 2] == 'd') {
      ch = MOD;
      (*i) += 2;
    }
    if (ch == 0) ch = _get_func_operator(str, i);
  }
  return ch;
}

int _get_func_operator(char *str, size_t *i) {
  int ch = 0;
  ch = _get_cos_sin_tan(str, i);
  if (str[*i] == 'l' && str[(*i) + 1] == 'o' && str[(*i) + 2] == 'g') {
    ch = LOG;
    (*i) += 2;
  } else if (str[*i] == 'l' && str[(*i) + 1] == 'n') {
    ch = LN;
    (*i) += 1;
  } else if (str[*i] == 's' && str[(*i) + 1] == 'q' && str[(*i) + 2] == 'r' &&
             str[(*i) + 3] == 't') {
    ch = SQRT;
    (*i) += 3;
  }
  if (str[*i] == 'a') {
    (*i)++;
    ch = _get_cos_sin_tan(str, i);
    if (ch == COS) ch = ACOS;
    if (ch == SIN) ch = ASIN;
    if (ch == TAN) ch = ATAN;
  }
  return ch;
}

int _get_cos_sin_tan(const char *str, size_t *i) {
  char ch = 0;
  if (str[*i] == 'c' && str[(*i) + 1] == 'o' && str[(*i) + 2] == 's') {
    ch = COS;
    (*i) += 2;
  } else if (str[*i] == 's' && str[(*i) + 1] == 'i' && str[(*i) + 2] == 'n') {
    ch = SIN;
    (*i) += 2;
  } else if (str[*i] == 't' && str[(*i) + 1] == 'a' && str[(*i) + 2] == 'n') {
    ch = TAN;
    (*i) += 2;
  }
  return ch;
}

size_t strcat_num(char *destination, const char *append) {
  size_t len = strlen(destination);
  size_t i = 0, is_sub = 0, is_add = 0;
  if (append[i] == SUB) {
    is_sub = 1;
    i++;
  }
  if (append[i] == ADD) {
    is_add = 1;
    i++;
  }
  for (; append[i] && (is_digit(append[i]) || _is_dot(append, i)); i++, len++)
    destination[len] = append[i];
  if (is_sub) destination[len] = SUB;
  if (is_add) destination[len++] = ADD;
  destination[++len] = '\0';
  return i;
}

int _is_dot(const char *str, size_t i) {
  size_t len = strlen(str);
  return i < len - 1 && str[i] == '.' && is_digit(str[i + 1]);
}

int _take_from_stack(Stack_t *stack, size_t *size, char *res, int is_less_or_eq,
                     char ch_put) {
  size_t len = strlen(res);
  Status status = OK;
  if (is_less_or_eq == 1) {
    status = _take_until_brace(stack, size, &len, res);
  } else if (is_less_or_eq == 2) {
    _take_while_less(stack, size, &len, res, ch_put);
    status = _take_while_equal(stack, size, &len, res, ch_put);
  } else if (is_less_or_eq == 3) {
    status = _take_while_equal(stack, size, &len, res, ch_put);
  } else {
    status = _take_everything_from_stack(stack, size, &len, res);
  }
  len = '\0';
  return status;
}

int _take_while_less(Stack_t *stack, size_t *size, size_t *len, char *res,
                     char ch_put) {
  while (peek(stack) != OPEN && *size && _is_less(stack, ch_put)) {
    char ch = peek(stack);
    if (ch != OPEN && ch != CLOSE) {
      res[(*len)++] = ch;
      res[(*len)++] = ' ';
      pop(&stack);
    }
    (*size)--;
  }
  return END_LESS;
}

int _take_while_equal(Stack_t *stack, size_t *size, size_t *len, char *res,
                      char ch_put) {
  while (peek(stack) != OPEN && *size && _is_equal(stack, ch_put)) {
    char ch = pop(&stack);
    if (ch != OPEN && ch != CLOSE) {
      res[(*len)++] = ch;
      res[(*len)++] = ' ';
    }
    (*size)--;
  }
  return END_EQUAL;
}

int _take_everything_from_stack(Stack_t *stack, size_t *size, size_t *len,
                                char *res) {
  for (; *size; (*size)--) {
    char ch = pop(&stack);
    if (ch != OPEN && ch != CLOSE) {
      res[(*len)++] = ch;
      res[(*len)++] = ' ';
    }
  }
  return END_STACK;
}

int _take_until_brace(Stack_t *stack, size_t *size, size_t *len, char *res) {
  while (peek(stack) != OPEN && *size) {
    char ch = pop(&stack);
    if (ch != OPEN && ch != CLOSE) {
      res[(*len)++] = ch;
      res[(*len)++] = ' ';
    }
    (*size)--;
  }
  if (peek(stack) == OPEN) {
    pop(&stack);
    (*size)--;
  }
  if (*size) {
    if (_is_heigh(peek(stack))) {
      res[(*len)++] = pop(&stack);
      res[(*len)++] = ' ';
      (*size)--;
    }
  }
  return END_BRACKETS;
}

int _is_less(Stack_t *stack, char ch) {
  int is_less_or_eq = 0;
  int curr = peek(stack);
  int is_low = ch == ADD || ch == SUB;
  int is_heigh = _is_heigh(ch);
  int is_curr = _is_heigh(curr);
  if (curr == MUL && is_low) is_less_or_eq = 1;
  if (curr == DIV && is_low) is_less_or_eq = 1;
  if (curr == MOD && is_low) is_less_or_eq = 1;
  if (is_curr && !is_heigh) is_less_or_eq = 1;
  return is_less_or_eq;
}

int _is_greater(Stack_t *stack, char ch) {
  int is_greater = 0;
  int curr = peek(stack);
  int is_mid = ch == MUL || ch == DIV || ch == MOD;
  int is_heigh = _is_heigh(ch);

  if (curr == 0 || curr == OPEN) is_greater = 1;
  if (curr == ADD && (is_mid || is_heigh)) is_greater = 1;
  if (curr == SUB && (is_mid || is_heigh)) is_greater = 1;
  if ((curr == MUL || curr == DIV) && is_heigh) is_greater = 1;
  if (curr == MOD && is_heigh) is_greater = 1;
  if (ch == CLOSE) is_greater = 3;
  return is_greater;
}

int _is_heigh(char ch) {
  int tmp = 0;
  if (ch == DEG || ch == COS || ch == SIN || ch == TAN) tmp = 1;
  if (ch == ACOS || ch == ASIN || ch == ATAN) tmp = 1;
  if (ch == SQRT || ch == LN || ch == LOG) tmp = 1;
  return tmp;
}

int _is_equal(Stack_t *stack, char ch) {
  int is_equal = 0;
  int curr = peek(stack);
  int is_low = ch == ADD || ch == SUB;
  int is_mid = ch == MUL || ch == DIV || ch == MOD;
  if (curr == MUL && is_mid) is_equal = 1;
  if (curr == DIV && is_mid) is_equal = 1;
  if (curr == MOD && is_mid) is_equal = 1;
  if (curr == ADD && is_low) is_equal = 1;
  if (curr == SUB && is_low) is_equal = 1;
  if (_is_heigh(curr) && _is_heigh(ch)) is_equal = 1;
  return is_equal;
}

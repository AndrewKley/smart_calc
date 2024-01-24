// Copyright [2023] jupitere
#include "./s21_calc.h"

int create_node(Node_t **node) {
  Status status = OK;
  Node_t *tmp = malloc(sizeof(Node_t));
  if (tmp) {
    tmp->next = NULL;
    tmp->num = 0;
    *node = tmp;
  } else {
    status = ALLOCATE;
  }
  return status;
}

int push_node(Node_t **node, double num) {
  Status status = OK;
  Node_t *tmp = malloc(sizeof(Node_t));
  if (tmp && node) {
    tmp->num = num;
    tmp->next = (*node)->next;
    (*node)->next = tmp;
  } else {
    status = ALLOCATE;
  }
  return status;
}

double pop_node(Node_t **node) {
  Node_t *tmp = NULL;
  double num = 0;
  if (*node) {
    tmp = (*node)->next;
    num = tmp->num;
    (*node)->next = (*node)->next->next;
    free(tmp);
  }
  return num;
}

void delete_node(Node_t **node, int *size) {
  Node_t *tmp = NULL;
  while (*size) {
    tmp = *node;
    *node = (*node)->next;
    free(tmp);
    (*size)--;
  }
  free(*node);
  (*node) = NULL;
}

int push(Stack_t **stack, char operation) {
  Status status = OK;
  Stack_t *tmp = malloc(sizeof(Stack_t));
  if (tmp && stack) {
    tmp->operation = operation;
    tmp->next = (*stack)->next;
    (*stack)->next = tmp;
  } else {
    status = ALLOCATE;
  }
  return status;
}

void remove_stack(Stack_t **stack) {
  free(*stack);
  (*stack) = NULL;
}

char pop(Stack_t **stack) {
  Stack_t *tmp = NULL;
  char ch = 0;
  if (*stack) {
    tmp = (*stack)->next;
    ch = tmp->operation;
    (*stack)->next = (*stack)->next->next;
    free(tmp);
  }
  return ch;
}

char peek(Stack_t *stack) {
  Stack_t *tmp = stack->next;
  return tmp ? tmp->operation : 0;
}

int create(Stack_t **stack) {
  Status status = OK;
  Stack_t *tmp = malloc(sizeof(Stack_t));
  if (tmp) {
    tmp->next = NULL;
    tmp->operation = 0;
    *stack = tmp;
  } else {
    status = ALLOCATE;
  }
  return status;
}

int check_brackets(char expression[]) {
  int left_brackets = 0, right_brackets = 0;
  int status = OK;
  size_t len = strlen(expression);
  for (size_t i = 0; i < len; i++) {
    if (expression[i] == '(') {
      left_brackets++;
    }
    if (expression[i] == ')') {
      right_brackets++;
    }
    if (left_brackets < right_brackets) {
      status = UNCORRECT_BRACKETS;
      break;
    }
  }
  if (left_brackets != right_brackets) status = UNCORRECT_BRACKETS;
  return status;
}

int is_digit(char ch) { return (ch >= 48 && ch <= 57) || ch == 'x'; }

double s21_atof(const char *str, size_t *i) {
  size_t len = strlen(str);
  double num = 0;
  int exp = 0, is_exp = 0;
  size_t j = *i;
  for (; j < len && (is_digit(str[j]) || str[j] == '.'); j++) {
    if (str[j] == '.') {
      is_exp = 1;
      continue;
    }
    if (is_exp) exp++;
    num = num * 10 + (str[j] - '0');
  }
  for (int k = 0; k < exp; k++) {
    num /= 10;
  }
  *i += j - *i;
  return num;
}

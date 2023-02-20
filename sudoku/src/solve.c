#include "ft.h"

int preparing(char *x, char *y, char **new_arr) {
  *x = 0;
  while (*x < 9) {
    *y = 0;
    while (*y < 9 && *(*(new_arr + *x) + *y) != 0) *y += 1;
    if (*y == 9) *y = 8;
    if (*(*(new_arr + *x) + *y) == 0) break;
    *x += 1;
  }
  if (*x == 9) *x = 8;
  return (0);
}

int zero_check(char **new_arr, int x, int y) {
  int acc;
  int index;

  acc = 0;
  index = 0;
  while (++acc <= 9) index += num_check(new_arr, x, y, acc);
  return (index);
}

int recur(char **new_arr, int x, int y) {
  int acc;

  acc = 0;
  while (++acc <= 9)
    if (num_check(new_arr, x, y, acc)) {
      *(*(new_arr + x) + y) = acc;
      if (x != 8 || y != 8) solve(new_arr);
    }
  return (0);
}

int solve(char **arr) {
  char x, y;
  char **new_arr;

  if (sud_check(arr)) return (1);
  arr_copy(&new_arr, arr);
  preparing(&x, &y, new_arr);
  if (*(*(new_arr + x) + y) == 0) {
    if (zero_check(new_arr, x, y) == 0) {
      free(new_arr);
      return (0);
    }
    recur(new_arr, x, y);
  }
  if (sud_check(new_arr)) arr_print(new_arr);
  free(new_arr);
  return (1);
}


int recur_num(char **new_arr, int x, int y, int *s_num) {
  int acc;

  acc = 0;
  while (++acc <= 9)
    if (num_check(new_arr, x, y, acc)) {
      *(*(new_arr + x) + y) = acc;
      if (x != 8 || y != 8) solve_num(new_arr, s_num);
    }
  return (0);
}

int solve_num(char **arr, int *s_num) {
  char x, y;
  char **new_arr;

  if (*s_num > 1000) return (0);
  if (sud_check(arr)) return (1);
  arr_copy(&new_arr, arr);
  preparing(&x, &y, new_arr);
  if (*(*(new_arr + x) + y) == 0) {
    if (zero_check(new_arr, x, y) == 0) {
      free(new_arr);
      return (0);
    }
    recur_num(new_arr, x, y, s_num);
  }
  if (sud_check(new_arr)) *s_num += 1;
  free(new_arr);
  return (1);
}
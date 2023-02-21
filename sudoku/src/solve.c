#include "ft.h"

int preparing(int *x, int *y, char **new_arr) {
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

int recur(char **new_arr, int x, int y, int *s_num) {
  int acc;

  acc = 0;
  while (++acc <= 9)
    if (num_check(new_arr, x, y, acc)) {
      *(*(new_arr + x) + y) = acc;
      if (x != 8 || y != 8) solve(new_arr, s_num);
    }
  return (0);
}

int solve(char **arr, int *s_num) {
  int x, y;
  char **new_arr;

  if (*s_num > 1000) return (0);
  if (sud_check(arr)) return (1);
  new_arr = arr_cpy(arr);
  preparing(&x, &y, new_arr);
  if (new_arr[x][y] == 0) {
    if (zero_check(new_arr, x, y) == 0) {
      new_arr = arr_delete(new_arr);
      return (0);
    }
    recur(new_arr, x, y, s_num);
  }
  if (sud_check(new_arr)) {
    *s_num += 1;
    arr_print(new_arr);
  }
  new_arr = arr_delete(new_arr);
  return (1);
}
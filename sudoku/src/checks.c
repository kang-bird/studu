#include "ft.h"

int line_check(char **arr, int x, int num) {
  int acc = 0;
  while (acc < 9) {
    if (*(*(arr + x) + acc) == num) return 0;
    acc++;
  }
  return 1;
}

int column_check(char **arr, int y, int num) {
  int acc;

  acc = 0;
  while (acc < 9) {
    if (*(*(arr + acc) + y) == num) return 0;
    acc++;
  }
  return 1;
}

int box_check(char **arr, int x, int y, int num) {
  int acc_x;
  int acc_y;

  x = (x / 3) * 3;
  y = (y / 3) * 3;
  acc_x = 0;
  while (acc_x < 3) {
    acc_y = 0;
    while (acc_y < 3) {
      if (*(*(arr + acc_x + x) + acc_y + y) == num) return 0;
      acc_y++;
    }
    acc_x++;
  }
  return 1;
}

int double_check(char **arr) {
  int x;
  int y;
  int acc;
  char **temp;

  x = -1;
  arr_copy(&temp, arr);
  while (++x < 9) {
    y = -1;
    while (++y < 9) {
      acc = *(*(temp + x) + y);
      *(*(temp + x) + y) = 0;
      if (!num_check(temp, x, y, acc) && acc != 0) {
        error(kERR_CHAR);
        free(temp);
        return 1;
      }
      *(*(temp + x) + y) = acc;
    }
  }
  free(temp);
  return 0;
}

int num_check(char **arr, int x, int y, int num) {
  if (box_check(arr, x, y, num) && line_check(arr, x, num) &&
      column_check(arr, y, num))
    return 1;
  return 0;
}

// проверка значения параметров
char par_check_value(char **argv) {
  int x = 1;
  char result = kZERO;
  char acc;

  while (x < 10 && !result) {
    int y = 0;
    while (y < 9 &&  !result) {
      acc = *(*(argv + x) + y);
      if ((acc != '.' && (acc < '1' || acc > '9'))) {
        error(kERR_CHAR);
        result = 1;
      }
      y++;
    }
    result = ft_strlen(*(argv + x)) != 9;
    x++;
  }
  return result;
}

// проверка параметров, сначало кол-во
char par_check(int argc, char **argv) {
  if (argc == 1) {
    error(kZERO);
    return 1;
  }
  if (argc != 10) {
    error(kERR_PAR_NUM);
    return 1;
  }
  return (par_check_value(argv));
}

int sud_check(char **arr) {
  int x;

  x = 0;
  while (x < 9) {
    int y = 0;
    while (y < 9) {
      if (*(*(arr + x) + y) == 0) return 0;
      y++;
    }
    x++;
  }
  return 1;
}
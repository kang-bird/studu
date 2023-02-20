#include "ft.h"

// проверка строки
char line_check(char **arr, int x, char num) {
  int acc = 0;
  char result = 1;
  while (acc < 9 && result) {
    result = arr[x][acc] != num;
    acc++;
  }
  return result;
}

// проверка столбца
char column_check(char **arr, int y, char num) {
  int acc = 0;
  char result = 1;

  while (acc < 9 && result) {
    result = arr[acc][y] != num;
    acc++;
  }
  return result;
}

// проверка числа в квадрате 3х3
char box_check(char **arr, int x, int y, char num) {
  int acc_x = 0;
  char result = 1;

  x = (x / 3) * 3;
  y = (y / 3) * 3;
  while (acc_x < 3 && result) {
    char acc_y = 0;
    while (acc_y < 3 && result) {
      result = arr[acc_x + x][acc_y + y] != num;
      acc_y++;
    }
    acc_x++;
  }
  return result;
}

// проверка совпадения числа по всем фронтам
char num_check(char **arr, int x, int y, char num) {
  return box_check(arr, x, y, num) && line_check(arr, x, num) &&
      column_check(arr, y, num);
}

// проверка совпадения всех чисел по всем фронтам
char double_check(char **arr) {
  int x = 0;
  char acc = 0;
  char result = 0;

  while (x < 9 && !result) {
    int y = 0;
    while (y < 9 && !result) {
      acc = arr[x][y];
      arr[x][y] = 0;
      if (acc != 0 && !num_check(arr, x, y, acc)) {
        error(kERR_CHAR);
        result = 1;
      }
      arr[x][y] = acc;
      y++;
    }
    x++;
  }
  return result;
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
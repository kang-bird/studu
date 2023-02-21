#include "ft.h"

// проверка строки
bool row_check(char **arr, int x, char num) {
  int acc = 0;
  bool result = true;
  while (acc < 9 && result) {
    result &= arr[x][acc] != num;
    acc++;
  }
  return result;
}

// проверка столбца
bool column_check(char **arr, int y, char num) {
  int acc = 0;
  bool result = true;

  while (acc < 9 && result) {
    result &= arr[acc][y] != num;
    acc++;
  }
  return result;
}

// проверка числа в квадрате 3х3
bool box_check(char **arr, int x, int y, char num) {
  int acc_x = 0;
  bool result = true;

  x -= x % 3;
  y -= y % 3;
  while (acc_x < 3 && result) {
    int acc_y = 0;
    while (acc_y < 3 && result) {
      result &= arr[acc_x + x][acc_y + y] != num;
      acc_y++;
    }
    acc_x++;
  }
  return result;
}

// проверка отсутствия числа по всем фронтам
bool num_check(char **arr, int x, int y, char num) {
  return box_check(arr, x, y, num) && row_check(arr, x, num) &&
         column_check(arr, y, num);
}

// проверка совпадения всех чисел по всем фронтам
bool double_check(char **arr) {
  int x = 0;
  char acc = 0;
  char result = true;

  while (x < 9 && result) {
    int y = 0;
    while (y < 9 && result) {
      acc = arr[x][y];
      arr[x][y] = 0;
      if (acc != 0 && !num_check(arr, x, y, acc)) {
        error(kERR_CHAR);
        result = false;
      }
      arr[x][y] = acc;
      y++;
    }
    x++;
  }
  return result;
}

// проверка значения параметров
bool par_check_value(char **argv) {
  int x = 1;
  bool result = true;
  char acc;

  while (x < 10 && result) {
    int y = 0;
    while (y < 9 && result) {
      acc = argv[x][y];
      if ((acc != '.' && (acc < '1' || acc > '9'))) {
        error(kERR_CHAR);
        result = false;
      }
      y++;
    }
    result &= ft_strlen(argv[x]) == 9;
    x++;
  }
  return result;
}

// проверка параметров, сначало кол-во
bool par_check(int argc, char **argv) {
  if (argc == 1) {
    error(kZERO);
    return false;
  }
  if (argc != 10) {
    error(kERR_PAR_NUM);
    return false;
  }
  return (par_check_value(argv));
}

// проверяем полностью ли решён судоку
bool sud_check(char **arr) {
  bool result = true;
  int x = 0;

  while (x < 9 && result) {
    int y = 0;
    while (y < 9 && result) {
      result &= (arr[x][y] != 0);
      y++;
    }
    x++;
  }
  return result;
}

// подсчёт кол-ва допустимых для вставки чисел
char zero_check(char **new_arr, int x, int y) {
  char acc = 1;
  char index = 0;

  while (acc < 10) {
    index += num_check(new_arr, x, y, acc);
    acc++;
  }
  return (index);
}
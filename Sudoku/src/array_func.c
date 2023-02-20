#include "ft.h"

int arr_create(int ***arr, char **argv) {
  int x;
  int y;

  x = 0;
  *arr = (int **)malloc(sizeof(int *) * 9);
  while (x < 9) {
    y = 0;
    *(*arr + x) = (int *)malloc(sizeof(int) * 9);
    while (y < 9) {
      if (*(*(argv + x) + y) == '.')
        *(*(*arr + x) + y) = 0;
      else
        *(*(*arr + x) + y) = *(*(argv + x) + y) - '0';
      y++;
    }
    x++;
  }
  return (0);
}

int arr_copy(int ***arr_new, int **arr_old) {
  int x;
  int y;

  x = 0;
  *arr_new = (int **)malloc(sizeof(int *) * 9);
  while (x < 9) {
    y = 0;
    *(*arr_new + x) = (int *)malloc(sizeof(int) * 9);
    while (y < 9) {
      *(*(*arr_new + x) + y) = *(*(arr_old + x) + y);
      y++;
    }
    x++;
  }
  return (0);
}

int arr_print(int **arr) {
  int x;
  int y;

  x = 0;
  while (x < 9) {
    y = 0;
    while (y < 9) {
      ft_putchar(*(*(arr + x) + y) + '0');
      y++;
    }
    ft_putchar('\n');
    x++;
  }
  ft_putchar('\n');
  return (0);
}
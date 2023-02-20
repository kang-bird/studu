#include "ft.h"

char** arr_create(char **argv) {
  int x;
  char** result = NULL;

  x = 0;
  result = (char**)malloc(sizeof(char *) * 9);
  while (x < 9) {
    int y = 0;
    *(result + x) = (char *)malloc(sizeof(int) * 9);
    while (y < 9) {
      if (*(*(argv + x) + y) == '.')
        *(*(result + x) + y) = 0;
      else
        *(*(result + x) + y) = *(*(argv + x) + y) - '0';
      y++;
    }
    x++;
  }
  return result;
}

int arr_copy(char ***arr_new, char **arr_old) {
  int x;
  int y;

  x = 0;
  *arr_new = (char **)malloc(sizeof(char *) * 9);
  while (x < 9) {
    y = 0;
    *(*arr_new + x) = (char *)malloc(sizeof(int) * 9);
    while (y < 9) {
      *(*(*arr_new + x) + y) = *(*(arr_old + x) + y);
      y++;
    }
    x++;
  }
  return (0);
}

int arr_print(char **arr) {
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
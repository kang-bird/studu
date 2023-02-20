#include "ft.h"

// вывод исмвола
int ft_putchar(char c) {
  write(1, &c, 1);
  return (0);
}

// вывод строки
int ft_putstr(char *str) {
  while (*str) {
    ft_putchar(*str);
    str++;
  }
  return (0);
}

// преобразование цифры в строку
void ft_putnbr(int num) {
  char str[100];
  int acc;

  if (num == 0) {
    ft_putchar('0');
    return;
  }
  str[99] = 0;
  acc = 99;
  while (num) {
    acc--;
    str[acc] = num % 10 + '0';
    num /= 10;
  }
  ft_putstr(str + acc);
}

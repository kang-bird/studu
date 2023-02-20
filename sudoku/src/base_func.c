#include "ft.h"

// вывод символа
void ft_putchar(char c) {
  write(1, &c, 1);
}

// вывод строки
void ft_putstr(char *str) {
  while (*str) {
    ft_putchar(*str);
    str++;
  }
}

// преобразование числа в строку
void ft_putnbr(int num) {
  char str[100];
  int acc;

  if (num == kZERO) {
    ft_putchar('0');
    return;
  }
  str[99] = kZERO;
  acc = 99;
  while (num) {
    acc--;
    str[acc] = num % 10 + '0';
    num /= 10;
  }
  ft_putstr(str + acc);
}

// длина строки
int ft_strlen(char *str) {
  int result = kZERO;
  while (*(str + result)) {
    result++;
  }
  return result;
}

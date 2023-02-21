#include "ft.h"

// вывод символа
void ft_putchar(char c) { write(1, &c, 1); }

// вывод строки
void ft_putstr(char *str) {
  while (*str) {
    ft_putchar(*str);
    str++;
  }
}

// преобразование числа в строку
void ft_putnbr(unsigned int num) {
  if (num > 9) {
    ft_putnbr(num / 10);
    ft_putnbr(num % 10);
  } else {
    ft_putchar(num + '0');
  }
}

// длина строки
int ft_strlen(char *str) {
  int result = kZERO;
  while (*(str + result)) {
    result++;
  }
  return result;
}

#ifndef FT_H
#define FT_H
#include <unistd.h>
#include <stdlib.h>

// const char kZERO = 0;
// const char kERR_PAR_NUM = 1;
// const char kERR_CHAR = 2;
// const char kERR_OPTION = 3;

#define kZERO 0
#define kERR_PAR_NUM 1
#define kERR_CHAR 2
#define kERR_OPTION 3

void	ft_putchar(char c);  // вывод символа
void	ft_putstr(char *str);  // вывод строки
void	ft_putnbr(int num);  // преобразование числа в строку
int	    ft_strlen(char *str);  // вывод строки
void	error(int x);  // вывод ошибки
char    par_check_value(char **argv);  // проверка значения параметров
char	par_check(int argc, char **argv);  // проверка параметров, сначало кол-во
int		arr_create(int ***arr, char **argv);
int		arr_print(int **arr);
int		sud_check(int **arr);
int		num_check(int **arr, int x, int y, int num);
int		solve(int **arr);
int		solve_num(int **arr, int *s_num);
int		arr_copy(int ***arr_new, int **arr_old);
int		double_check(int **arr);
int		preparing(int *x, int *y, int **new_arr);
int		zero_check(int **new_arr, int x, int y);
#endif

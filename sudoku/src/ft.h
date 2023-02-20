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
char**	arr_create(char **argv);
int		arr_print(char **arr);
int		sud_check(char **arr);
int		num_check(char **arr, int x, int y, int num);
int		solve(char **arr);
int		solve_num(char **arr, int *s_num);
int		arr_copy(char ***arr_new, char **arr_old);
int		double_check(char **arr);
int		preparing(char *x, char *y, char **new_arr);
int		zero_check(char **new_arr, int x, int y);
#endif

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
void	ft_putnbr(unsigned int num);  // преобразование числа в строку
int	    ft_strlen(char *str);  // вывод строки
void	error(int x);  // вывод ошибки
char    par_check_value(char **argv);  // проверка значения параметров
char	par_check(int argc, char **argv);  // проверка параметров, сначало кол-во
char**	arr_create(char **argv);  // выделение памяти под первичный массив
char**  arr_delete(char **arr);  // очистка памяти массива
int		arr_print(char **arr);
int		sud_check(char **arr);
char    row_check(char **arr, int x, char num);  // проверка строки
char    column_check(char **arr, int y, char num);  // проверка столбца
char    box_check(char **arr, int x, int y, char num);  // проверка числа в квадрате 3х3
char	num_check(char **arr, int x, int y, char num);  // проверка совпадения числа по всем фронтам
int		solve(char **arr, int *s_num);
char**	arr_cpy(char **arr_old);  // копирование массива
char	double_check(char **arr);  // проверка совпадения всех чисел по всем фронтам
int		preparing(int *x, int *y, char **new_arr);
int		zero_check(char **new_arr, int x, int y);
#endif

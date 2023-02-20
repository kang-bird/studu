#ifndef FT_H
# define FT_H
# define ERR_PAR_NUM	1
# define ERR_CHAR		2
# define ERR_OPTION		3

#include <unistd.h>
#include <stdlib.h>

int		ft_putchar(char c);
void	error(int x);
int		par_check(int argc, char **argv);
int		arr_create(int ***arr, char **argv);
int		arr_print(int **arr);
int		sud_check(int **arr);
int		num_check(int **arr, int x, int y, int num);
int		solve(int **arr);
int		solve_num(int **arr, int *s_num);
int		arr_copy(int ***arr_new, int **arr_old);
int		ft_putstr(char *str);
void	ft_putnbr(int num);
int		double_check(int **arr);
int		preparing(int *x, int *y, int **new_arr);
int		zero_check(int **new_arr, int x, int y);
#endif

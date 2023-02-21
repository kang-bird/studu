#ifndef FT_H
#define FT_H
#include <stdlib.h>
#include <unistd.h>

typedef enum { false, true } bool;

extern const char kZERO;
extern const char kERR_PAR_NUM;
extern const char kERR_CHAR;
extern const int kMAX_SOLUTION;

void ft_putchar(char c);    // вывод символа
void ft_putstr(char *str);  // вывод строки
void ft_putnbr(unsigned int num);  // преобразование числа в строку
int ft_strlen(char *str);  // вывод строки
void error(int x);         // вывод ошибки
bool par_check_value(char **argv);  // проверка значения параметров
bool par_check(int argc, char **argv);  // проверка параметров, сначало кол-во
char **arr_create(char **argv);  // выделение памяти под первичный массив
char **arr_delete(char **arr);  // очистка памяти массива
void arr_print(char **arr);     // печать массива
bool sud_check(char **arr);  // проверяем полностью ли решён судоку
bool row_check(char **arr, int x, char num);  // проверка строки
bool column_check(char **arr, int y, char num);  // проверка столбца
bool box_check(char **arr, int x, int y,
               char num);  // проверка числа в квадрате 3х3
bool num_check(char **arr, int x, int y,
               char num);  // проверка совпадения числа по всем фронтам
void recur(char **new_arr, int x, int y,
           int *s_num);  // узел ветвления для всех допустимых чисел
void solve(char **arr, int *s_num);  // решение судоку
char **arr_cpy(char **arr_old);      // копирование массива
bool double_check(
    char **arr);  // проверка совпадения всех чисел по всем фронтам
bool preparing(int *x, int *y, char **new_arr);  // находим пустую ячейку
char zero_check(char **new_arr, int x,
                int y);  // подсчёт кол-ва допустимых для вставки чисел
#endif

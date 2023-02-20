#include "ft.h"

int main(int argc, char **argv) {
  int **arr;
  int total = 0;

  if (par_check(argc, argv)) return (0);
  if (arr_create(&arr, argv + 1)) return (0);
  if (double_check(arr)) return (0);
  solve_num(arr, &total);
  if (total > 10) {
    ft_putstr("Total number of solutions more than 10.");
    ft_putstr(" Please, use more keys.\n");
    return (0);
  }
  solve(arr);
  ft_putstr("Total number of solutions: ");
  ft_putnbr(total);
  ft_putchar('\n');
  return (0);
}

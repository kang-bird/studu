#include "ft.h"

const char kZERO = 0;
const char kERR_PAR_NUM = 1;
const char kERR_CHAR = 2;

int main(int argc, char **argv) {
  char **arr = NULL;
  int total = 0;

  if (!par_check(argc, argv) || ((arr = arr_create(argv + 1)) == NULL) || !double_check(arr))
    return 0;
  solve(arr, &total);
  if (total > 10) {
    ft_putstr("Total number of solutions more than 10.");
    ft_putstr(" Please, use more keys.\n");
    return 0;
  }
  ft_putstr("Total number of solutions: ");
  ft_putnbr(total);
  ft_putchar('\n');
  arr = arr_delete(arr);
  return 0;
}

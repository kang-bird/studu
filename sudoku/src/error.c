#include "ft.h"

// вывод ошибки
void error(int x) {
  if (x == kZERO) {
    ft_putstr("Error. Please use this rule for program lounching:\n");
    ft_putstr(">./sudoku line0 line1 line2 line3 line4 line5 ");
    ft_putstr("line6 line7 line8\nLineN represents a ");
    ft_putstr("characters string of values ranged between ’1’ ");
    ft_putstr("and ’9’ or ’.’ (for empty boxes).\n");
  }
  if (x == kERR_PAR_NUM) ft_putstr("Error, wrong number of lines\n");
  if (x == kERR_CHAR) ft_putstr("Error, wrong keys characters\n");
  if (x == kERR_OPTION) ft_putstr("Error, wrong option");
}

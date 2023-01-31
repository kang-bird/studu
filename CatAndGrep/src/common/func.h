#ifndef SRC_COMMON_FUNC_H_
#define SRC_COMMON_FUNC_H_
#include <string.h>

int checks(char* opt, char* ben, int* benstuv, int* err);
int check_benstuv(char* opt, int* benstuv);  // реализация в каждой утилите своя
int check_benstuv_box(char* opt, char* ben, int* benstuv);
int check_opt(char* opt, char* opt_def, int* benstuv, int bit);
void error_print(int benstuv, char code, char* str);

void error_print(int benstuv, char code, char* str) {
    if (!(benstuv & bit_s)) {
        if (code == 1)
            printf("%s: No such file or directory\n", str);
        if (code == 2)
            printf("%s: Illegal option\n", str);
    }
}

// укоротим длинные строки в условиях циклов
int checks(char* opt, char* ben, int* benstuv, int* err) {
    *err = !(check_benstuv(opt, benstuv)
        || check_benstuv_box(opt, ben, benstuv));
    return !(*err);
}

// через логическое ИЛИ заполняем переменную флагов benstuv
int check_opt(char* opt, char* opt_def, int* benstuv, int bit) {
    int result = 0;
    if (!(strcmp(opt, opt_def))) {
        if (benstuv != NULL)
            *benstuv |= bit;
        result = 1;
    }
    return result;
}

// проверка наборных параметров
int check_benstuv_box(char* opt, char* ben, int* benstuv) {
    int result = 0;
    if (*opt == '-') {
        opt += 1;
        // ищем посимвольно в наборе флагов, если находим,
        // то обновляем переменную benstuv
        while (*opt && strchr(ben, *opt) != NULL) {
            char temp[3];
            temp[0] = '-';
            temp[1] = *strchr(ben, *opt);
            temp[2] = 0;
            check_benstuv(temp, benstuv);
            opt += 1;
        }
        if (!(*opt))
            result = 1;
        else
            error_print(*benstuv, 2, opt);
    }
    return result;
}

#endif  // SRC_COMMON_FUNC_H_

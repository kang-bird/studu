#include "cat.h"
#include "../common/func.h"

int check_benstuv(char* opt, int* benstuv) {
    int result = 0;
    // через логическое ИЛИ определяем было ли удачнное считывание флага
    // -A, --show-all equivalent to -vET
    result |= check_opt(opt, opt_A, benstuv, bit_v);
    result |= check_opt(opt, opt_A, benstuv, bit_e);
    result |= check_opt(opt, opt_A, benstuv, bit_t);
    result |= check_opt(opt, opt_A_l, benstuv, bit_v);
    result |= check_opt(opt, opt_A_l, benstuv, bit_e);
    result |= check_opt(opt, opt_A_l, benstuv, bit_t);
    // -b, --number-nonblank
    result |= check_opt(opt, opt_b, benstuv, bit_b);
    result |= check_opt(opt, opt_b_l, benstuv, bit_b);
    // -e     equivalent to -vE
    result |= check_opt(opt, opt_e, benstuv, bit_v);
    result |= check_opt(opt, opt_e, benstuv, bit_e);
    // -E, --show-ends
    result |= check_opt(opt, opt_E, benstuv, bit_e);
    result |= check_opt(opt, opt_E_l, benstuv, bit_e);
    // -n, --number
    result |= check_opt(opt, opt_n, benstuv, bit_n);
    result |= check_opt(opt, opt_n_l, benstuv, bit_n);
    // -s, --squeeze-blank
    result |= check_opt(opt, opt_s, benstuv, bit_s);
    result |= check_opt(opt, opt_s_l, benstuv, bit_s);
    // -t     equivalent to -vT
    result |= check_opt(opt, opt_t, benstuv, bit_v);
    result |= check_opt(opt, opt_t, benstuv, bit_t);
    // -T, --show-tabs
    result |= check_opt(opt, opt_T, benstuv, bit_t);
    result |= check_opt(opt, opt_T_l, benstuv, bit_t);
    // -u     (ignored)
    result |= !strcmp(opt, "-u");
    // -v, --show-nonprinting
    result |= check_opt(opt, opt_v, benstuv, bit_v);
    result |= check_opt(opt, opt_v_l, benstuv, bit_v);
    // отменяем флаг n, если у нас есть флаг b
    if (*benstuv & bit_b)
        *benstuv &= ~bit_n;
    return result;
}

// печать невидимых исмволов для 127
void v_under_127(char c) {
    if (c == 127) {
        putchar('^');
        putchar('?');
    } else {
        if (c == -1) {
            putchar('M');
            putchar('-');
        }
        putchar('^');
        putchar(c + '@');
    }
}

void v_over_127(char c) {
    unsigned char out = c;
    if (out > 127 && out < 160) {
        putchar('M');
        putchar('-');
        putchar('^');
        putchar(c - 64);
    }
    if (out >= 160) {
        putchar('M');
        putchar('-');
        putchar(c - 128);
    }
}

int file_out(char* name, int benstuv, int* str_count) {
    int result = 0;
    FILE* fm = fopen(name, "rb");
    if (fm != NULL) {
        int empty_str = 0;
        #if(!(__linux__))  // сквозная нумерация в linux
            *str_count = 1;
        #endif
        char past = '\n';
        for (char temp = fgetc(fm); !feof(fm) && !ferror(fm); temp = fgetc(fm)) {
            // проверяем необходимость пропуска строки
            if (!(benstuv & bit_s) || !(empty_str && temp == '\n')) {
                // прогоняем через битовые маски флагов
                if ((benstuv & bit_n) && past == '\n') {
                    printf("%6d\t", *str_count);
                    *str_count += 1;
                }
                if ((benstuv & bit_b) && past == '\n' && !(temp == '\n')) {
                    printf("%6d\t", *str_count);
                    *str_count += 1;
                }
                if ((benstuv & bit_e) && temp == '\n')
                    putchar('$');
                if ((benstuv & bit_t) && temp == '\t')
                    printf("^I");
                else if ((benstuv & bit_v) && ((temp < 32 &&
                        temp != '\t' && temp != '\n' &&
                        temp >= -1) || temp == 127))
                    v_under_127(temp);
                else if ((benstuv & bit_v) && temp < 0)
                    v_over_127(temp);
                else
                    putchar(temp);
            }
            // проверяем наличие пустой строки
            empty_str = ('\n' == past) && ('\n' == temp);
            past = temp;
        }
        fclose(fm);
    } else {
        error_print(benstuv, 1, name);
    }
    return result;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        int opt_benstuv = 0;
        int count = 1;
        int err = 0;
        int str_count = 1;
        // прогоняем наши параметры на проверку флагов
        while (count < argc) {
            if (**(argv + count) == '-')
                checks(*(argv + count), FLAGS, &opt_benstuv, &err);
            count += 1;
        }
        // если мы прошлись по всем параметрам без ошибок,
        // то работаем с файлами
        if (!err) {
            count = 1;
            while (count < argc) {
                if (!checks(*(argv + count), FLAGS, &opt_benstuv, &err))
                    file_out(*(argv + count), opt_benstuv, &str_count);
                count += 1;
            }
        }
    }
    return 0;
}

#include "grep.h"
#include "../common/func.h"

int check_benstuv(char* opt, int* benstuv) {
    int result = 0;
    // через логическое ИЛИ определяем было ли удачнное считывание флага
    // -e, --regexp
    result |= check_opt(opt, opt_e, benstuv, bit_e);
    result |= check_opt(opt, opt_e_l, benstuv, bit_e);
    // -f, --file
    result |= check_opt(opt, opt_f, benstuv, bit_f);
    result |= check_opt(opt, opt_f_l, benstuv, bit_f);
    // -i  --ignore-case
    result |= check_opt(opt, opt_i, benstuv, bit_i);
    result |= check_opt(opt, opt_i_l, benstuv, bit_i);
    // -v, --invert-match
    result |= check_opt(opt, opt_v, benstuv, bit_v);
    result |= check_opt(opt, opt_v_l, benstuv, bit_v);
    // -c, --count
    result |= check_opt(opt, opt_c, benstuv, bit_c);
    result |= check_opt(opt, opt_c_l, benstuv, bit_c);
    // -l, --files-with-matches
    result |= check_opt(opt, opt_l, benstuv, bit_l);
    result |= check_opt(opt, opt_l_l, benstuv, bit_l);
    // -o  --only-matching
    result |= check_opt(opt, opt_o, benstuv, bit_o);
    result |= check_opt(opt, opt_o_l, benstuv, bit_o);
    // -s, --no-messages
    result |= check_opt(opt, opt_s, benstuv, bit_s);
    result |= check_opt(opt, opt_s_l, benstuv, bit_s);
    // -h, --no-filename
    result |= check_opt(opt, opt_h, benstuv, bit_h);
    result |= check_opt(opt, opt_h_l, benstuv, bit_h);
    // -n, --line-number
    result |= check_opt(opt, opt_n, benstuv, bit_n);
    result |= check_opt(opt, opt_n_l, benstuv, bit_n);
    return result;
}

args args_init() {
    args result;
    memset(result.names, 0, 256);
    result.names_count = 0;
    memset(result.templates, 0, 256);
    result.templates_count = 0;
    memset(result.file_names, 0, 256);
    result.file_names_count = 0;
    return result;
}

void args_check(char** argv, unsigned char count, args* args_f, int benstuv) {
    if (check_opt(*(argv + count - 1), opt_f, NULL, bit_f) ||
        check_opt(*(argv + count - 1), opt_f_l, NULL, bit_f)) {
        args_f->file_names[args_f->file_names_count] = count;  // запоминам положние имени файла с шаблоном
        args_f->file_names_count += 1;
    } else if ((args_f->templates_count == 0 && !(benstuv & bit_e) && !(benstuv & bit_f)) ||
            check_opt(*(argv + count - 1), opt_e, NULL, bit_e) ||
            check_opt(*(argv + count - 1), opt_e_l, NULL, bit_e)) {
        args_f->templates[args_f->templates_count] = count;  // запоминам положние текущего шаблона
        args_f->templates_count += 1;
    } else {
        args_f->names[args_f->names_count] = count;  // запоминам положние текущего имени
        args_f->names_count += 1;
    }
}

void match_print(char* temp, regmatch_t pmatch, int step) {
    int j = pmatch.rm_so;
    while (j < pmatch.rm_eo) {
        putchar(*(temp + j + step));
        j += 1;
    }
    putchar('\n');
}

void print_attributs(int benstuv, const char* str, int str_count_n) {
    if (benstuv & bit_print_name)
        printf("%s:", str);  // печатаем имена, если файлов больше 2 и нет флага -h
    if (benstuv & bit_print_str_num)
        printf("%d:", str_count_n);  // печатаем номер строки, если есть флаг -n
}

int string_out(char** argv, int names_count, int benstuv, char* temp, args args_f, int str_count_n) {
    regmatch_t pmatch;
    regex_t preg;
    unsigned char templates_count = 0;
    int result = 0;
    // проходимся по всем шаблонам
    while (templates_count < args_f.templates_count) {
        int temp_result = 0;
        int step = 0;
        regcomp(&preg, *(argv + args_f.templates[templates_count]), REG_ICASE * ((benstuv & bit_i) > 0));
        temp_result = !regexec(&preg, temp, preg.re_nsub + 1, &pmatch, 0);
        result |= temp_result;
        // печатаем все совпадения в одной строке в случае флага -o
        while ((benstuv & bit_print_equal) && temp_result) {
            print_attributs(benstuv, *(argv + args_f.names[names_count]), str_count_n);
            match_print(temp, pmatch, step);
            step += pmatch.rm_eo;
            temp_result = !regexec(&preg, temp + step, preg.re_nsub + 1, &pmatch, 0);
            }
        regfree(&preg);
        templates_count += 1;
    }
    return result;
}

int string_out_f(char** argv, int names_count, int benstuv, char* temp, args args_f, int str_count_n) {
    regmatch_t pmatch;
    regex_t preg;
    unsigned char file_names_count = 0;
    int result = 0;
    char temp_f[10001];
    // проходимся по всем шаблонам
    while (file_names_count < args_f.file_names_count) {
        FILE* fm = fopen(*(argv + args_f.file_names[file_names_count]), "rb");
        while (fm != NULL && fgets(temp_f, 10000, fm) && !feof(fm) && !ferror(fm)) {
            // убираем перенос строки из шаблона, если строка не пустая
            if (strlen(temp_f) > 1 && *(temp_f + strlen(temp_f) - 1) == '\n')
                *(temp_f + strlen(temp_f) - 1) = 0;
            int temp_result = 0;
            int step = 0;
            regcomp(&preg, temp_f, REG_ICASE * ((benstuv & bit_i) > 0));
            temp_result = !regexec(&preg, temp, preg.re_nsub + 1, &pmatch, 0);
            result |= temp_result;
            // печатаем все совпадения в одной строке в случае флага -o
            while ((benstuv & bit_print_equal) && temp_result && *temp_f != '\n') {
                // интересное поведение, при отображении совпадений пустая строка игнорируется
                print_attributs(benstuv, *(argv + args_f.names[names_count]), str_count_n);
                match_print(temp, pmatch, step);
                step += pmatch.rm_eo;
                temp_result = !regexec(&preg, temp + step, preg.re_nsub + 1, &pmatch, 0);
            }
        }
        regfree(&preg);
        file_names_count += 1;
    }
    return result;
}


void file_out(char** argv, int benstuv, args args_f) {
    int result;
    int l_result;
    unsigned char names_count = 0;
    char temp[10001];
    while (names_count < args_f.names_count) {
        FILE* fm = fopen(*(argv + args_f.names[names_count]), "rb");
        if (fm != NULL) {
            int str_count_c = 0;
            int str_count_n = 1;
            l_result = 0;  // переменная для учета результата вне цикла
            while (fgets(temp, 10000, fm) && !feof(fm) && !ferror(fm)) {
                result = 0;
                result |= string_out(argv, names_count, benstuv, temp, args_f, str_count_n);
                result |= string_out_f(argv, names_count, benstuv, temp, args_f, str_count_n);
                l_result |= result;
                if ((result && !(benstuv & bit_v)) || (!result && (benstuv & bit_v))) {
                    if (benstuv & bit_print_str) {
                        // печатаем имя. номер строки и саму строку
                        print_attributs(benstuv, *(argv + args_f.names[names_count]), str_count_n);
                        printf("%s", temp);
                    }
                    str_count_c += 1;
                }
                str_count_n += 1;
            }
            if (l_result && (benstuv & bit_print_only_name))
                printf("%s\n", *(argv + args_f.names[names_count]));
            if (benstuv & bit_print_str_count) {
                if (benstuv & bit_print_ns_count)
                    printf("%s:", *(argv + args_f.names[names_count]));
                printf("%d\n", str_count_c);
            }
            fclose(fm);
        } else {
            error_print(benstuv, 1, *(argv + args_f.names[names_count]));
        }
        names_count += 1;
    }
}

void flag_generate(int* benstuv, args args_f) {
    // проверка отсутствия флагов -l и -c
    char com_lc = ((*benstuv & bit_l) == 0) * ((*benstuv & bit_c) == 0);
    // проверка комбинации флагов -o и -v
    char com_ov = !((*benstuv & bit_o) && (*benstuv & bit_v));
    // печатаем только имя, флаг -l
    *benstuv |= bit_print_only_name * ((*benstuv & bit_l) != 0);
    // печатаем только совпадния, флаг -o
    *benstuv |= bit_print_equal * ((*benstuv & bit_o) != 0) * com_lc * com_ov;
    // печатаем кол-во строк, флаг -c
    *benstuv |= bit_print_str_count * ((*benstuv & bit_c) != 0) * ((*benstuv & bit_l) == 0);
    // печатаем номер строки, флаг -n
    *benstuv |= bit_print_str_num * ((*benstuv & bit_n) != 0) * com_lc * com_ov;
    // печатаем всю строку, отсутствие флага -o и комбинаций
    *benstuv |= bit_print_str * ((*benstuv & bit_o) == 0) * com_lc * com_ov;
    // печатаем имя, отсутствие флага -h при нескольких файлах
    *benstuv |= bit_print_name * (((*benstuv & bit_h) == 0) && args_f.names_count > 1) * com_lc * com_ov;
    // печатаем имя, отсутствие флага -h при нескольких файлах и наличии флага -c
    *benstuv |= bit_print_ns_count * (((*benstuv & bit_h) == 0) && args_f.names_count > 1) *
            ((*benstuv & bit_print_str_count) != 0);
}

int main(int argc, char** argv) {
    if (argc > 2) {
        int opt_benstuv = 0;
        unsigned char count = 1;
        int err = 0;
        args args_f = args_init();
        // прогоняем наши параметры на проверку флагов
        while (count < argc) {
            if (**(argv + count) == '-')
                checks(*(argv + count), FLAGS, &opt_benstuv, &err);
            count += 1;
        }
        count = 1;
        // прогоняем ещё раз, т.к. из-за флага -е имена могут располагаться перед шаблоном
        while (count < argc) {
            if (**(argv + count) != '-')
                args_check(argv, count, &args_f, opt_benstuv);
            count += 1;
        }
        // если мы прошлись по всем параметрам без ошибок,
        // то работаем с файлами
        if (!err) {
            flag_generate(&opt_benstuv, args_f);  // генерируем флаги печати для упрощённой обработки
            file_out(argv, opt_benstuv, args_f);
        }
    }
    return 0;
}


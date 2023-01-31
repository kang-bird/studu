#ifndef SRC_GREP_GREP_H_
    #define SRC_GREP_GREP_H_
    // для битовых операций
    #define bit_e 1
    #define bit_f 2
    #define bit_i 4
    #define bit_v 8
    #define bit_c 16
    #define bit_l 32
    #define bit_o 64
    #define bit_s 128
    #define bit_h 256
    #define bit_n 512
    #define bit_print_name 1024
    #define bit_print_only_name 2048
    #define bit_print_str_num 4096
    #define bit_print_str_count 8192
    #define bit_print_str 16384
    #define bit_print_equal 32768
    #define bit_print_ns_count 65536
    #define FLAGS "efivcloshn"
    #include <string.h>  // как же без неё
    #include <stdio.h>
    #include <stdlib.h>
    #include <regex.h>
    // оперделяем флаги
    #define opt_e "-e"
    #define opt_e_l "--regexp"
    #define opt_f "-f"
    #define opt_f_l "--file"
    #define opt_i "-i"
    #define opt_i_l "--ignore-case"
    #define opt_v "-v"
    #define opt_v_l "--invert-match"
    #define opt_c "-c"
    #define opt_c_l "--count"
    #define opt_l "-l"
    #define opt_l_l "--files-with-matches"
    #define opt_o "-o"
    #define opt_o_l "--only-matching"
    #define opt_s "-s"
    #define opt_s_l "--no-messages"
    #define opt_h "-h"
    #define opt_h_l "--no-filename"
    #define opt_n "-n"
    #define opt_n_l "--line-number"
    // стуктура счётчка имён файлов и шаблонов
    typedef struct args {
        unsigned char names[256];
        unsigned char names_count;
        unsigned char templates[256];
        unsigned char templates_count;
        unsigned char file_names[256];
        unsigned char file_names_count;
    } args;
    args args_init();
    void args_check(char** argv, unsigned char count, args* args_f, int benstuv);
    void match_print(char* temp, regmatch_t pmatch, int step);
    void print_attributs(int benstuv, const char* str, int str_count_n);
    int string_out(char** argv, int names_count, int benstuv, char* temp, args args_f, int str_count_n);
    int string_out_f(char** argv, int names_count, int benstuv, char* temp, args args_f, int str_count_n);
    void flag_generate(int* benstuv, args args_f);
    void file_out(char** argv, int benstuv, args args_f);
#endif  // SRC_GREP_GREP_H_


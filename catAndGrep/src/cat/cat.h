#ifndef SRC_CAT_CAT_H_
    #define SRC_CAT_CAT_H_
    // для битовых операций
    #define bit_b 1
    #define bit_e 2
    #define bit_n 4
    #define bit_s 8
    #define bit_t 16
    #define bit_v 32
    #define FLAGS "benstv"
    #include <string.h>  // как же без неё
    #include <stdio.h>
    // GNU
    #define opt_A "-A"
    #define opt_A_l "--show-all"
    #define opt_b_l "--number-nonblank"
    #define opt_E "-E"
    #define opt_E_l "--show-ends"
    #define opt_n_l "--number"
    #define opt_s_l "--squeeze-blank"
    #define opt_T "-T"
    #define opt_T_l "--show-tabs"
    #define opt_v_l "--show-nonprinting"
    // not GNU
    #define opt_b "-b"  // имеет приоритет над n
    #define opt_e "-e"
    #define opt_n "-n"
    #define opt_s "-s"
    #define opt_t "-t"
    #define opt_v "-v"
    void v_under_127(char c);
    void v_over_127(char c);
    int file_out(char* name, int benstuv, int* str_count);
#endif  // SRC_CAT_CAT_H_

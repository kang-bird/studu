#ifndef SRC_BIT96_H_
#define SRC_BIT96_H_
#define ZERO 0
#define MUX 10  // множитель порядка
#include <math.h>

typedef enum {
    dNORMAL_VALUE = 0,
    dINFINITY = 1,
    dNEGATIVE_INFINITY = 2,
    dNAN = 3
} value_type_t;

typedef struct {
    int bits[4];
    value_type_t value_type;
} bit96;

typedef struct {
    unsigned long long x;
    unsigned long long y;
    unsigned long long z;
} long3;

typedef struct {
    unsigned long long x0;
    unsigned long long x1;
    unsigned long long x2;
    unsigned long long x3;
    unsigned long long x4;
    unsigned long long x5;
    unsigned long long x6;
} long7;

unsigned char GetRate(bit96 src);  // получаем степень
unsigned char GetSign(bit96 src);  // получаем знак
void SetRate(bit96* dst, unsigned char rate);  // записываем степень
void SetSign(bit96* dst, unsigned char sign);  // записываем знак
// разбиение одгого 128 битового инта на 3 32 битовых интов
void Normalize(bit96 src1, bit96 src2, bit96* dst1, bit96* dst2);
void ZeroSet(bit96* dst);  // обнуляем значения битов
void Bit96Init(bit96* dst);  // инициализация bit96
char ErrorCheck(bit96* dst);  // чек на состояние числа с автоматическим обнулением
void ErrorAdd(bit96* dst, value_type_t value_type);  // добавляем код ошибки и затираем значения

char LimitCheck_l(unsigned long long src);  // проверка на выход за пределы структуры
long3 Bit96ToLong3(bit96 src);  // перенос bit96 в новую структуру
void int_split_l(bit96* dst, long3 src);  // обратная конвертация сруктуры в bit96
void long3_mul(long3* src, unsigned int mux);  // умножение структуры на число
void long3_div(long3* src, unsigned int div);  // деление структуры на число
long3 long3_add(long3 src1, long3 src2);  // сложение структур
long3 long3_sub(long3 src1, long3 src2);  // вычитание структур
unsigned char long3_comp(long3 src1, long3 src2);  // сравнение структур

int from_int_to_bit96(int src, bit96 *dst);
int from_float_to_bit96(float src, bit96 *dst);
int from_bit96_to_int(bit96 src, int *dst);
int from_bit96_to_float(bit96 src, float *dst);

bit96 Negate(bit96 src);
bit96 Truncate(bit96 src);
bit96 Round(bit96 src);
bit96 Floor(bit96 src);

int is_less(bit96 src1, bit96 src2);
int is_greater(bit96 src1, bit96 src2);
int is_less_or_equal(bit96 src1, bit96 src2);
int is_greater_or_equal(bit96 src1, bit96 src2);
int is_equal(bit96 src1, bit96 src2);
int is_not_equal(bit96 src1, bit96 src2);

bit96 add(bit96 src1, bit96 src2);
bit96 sub(bit96 src1, bit96 src2);
bit96 mul(bit96 src1, bit96 src2);
bit96 div(bit96 src1, bit96 src2);
bit96 mod(bit96 src1, bit96 src2);

// подготовка переменных для мат операций
unsigned char math_preparing_l(bit96 src1, bit96 src2,
                               long3* dst1_int, long3* dst2_int);
// пушим максимально влево без потери точности
void push_left_l(long3* src, unsigned char* rate);
// пушим максимально вправо без потери точности
void push_right_l(long3* src, unsigned char* rate);
// финишная подготовка, проврка выхода за границы
void finish_preparing_l(bit96* dst, long3 src,
                        char rate, unsigned char sign);
// умножение большой структуры на число в степени
void pow128_l_l(long7* src, unsigned char mux, char rate);
// проверка ситуаций с невалидными зачениями при сложении
value_type_t add_errcheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при вычитании
value_type_t sub_errcheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при умножении
value_type_t mul_errcheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при делении
value_type_t div_errcheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при нахождении остатка
value_type_t mod_errcheck(bit96 src1, bit96 src2);
bit96 fun_mod(bit96 src1, bit96 src2);
// переносы и очистка при умножении и сложениис тркутур
void long7_preparing(long7* result);
// сложение больших структур
long7 long7_add(long7* src1, long7* src2);
// умножение большой структуры на число
void long7_mul(long7* src, unsigned int mux);
// деление большой структуры на число
void long7_div(long7* src, unsigned int div);
// получение остатка от деления большой структуры на число
unsigned int mod128_l(long3 src, unsigned int mux);

#endif  // SRC_BIT96_H_

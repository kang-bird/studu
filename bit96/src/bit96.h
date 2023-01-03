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

// структура для работы с 96битным числом
typedef struct {
    unsigned long long x;
    unsigned long long y;
    unsigned long long z;
} long3;

// структура для умножения и деления 96 битных чисел
typedef struct {
    unsigned long long x0;
    unsigned long long x1;
    unsigned long long x2;
    unsigned long long x3;
    unsigned long long x4;
    unsigned long long x5;
    unsigned long long x6;
} long7;

// Арифметические операторы
bit96 Add(bit96 src1, bit96 src2);
bit96 Sub(bit96 src1, bit96 src2);
bit96 Mul(bit96 src1, bit96 src2);
bit96 Div(bit96 src1, bit96 src2);
bit96 Mod(bit96 src1, bit96 src2);

// Операторы сравнения
int IsLess(bit96 src1, bit96 src2);
int IsGreater(bit96 src1, bit96 src2);
int IsLessOrEqual(bit96 src1, bit96 src2);
int IsGreaterOrEqual(bit96 src1, bit96 src2);
int IsEqual(bit96 src1, bit96 src2);
int IsNotEqual(bit96 src1, bit96 src2);

// Преобразователи
int IntToBit96(int src, bit96 *dst);
int FloatToBit96(float src, bit96 *dst);
int Bit96ToInt(bit96 src, int *dst);
int Bit96ToFloat(bit96 src, float *dst);

// Другие функции
bit96 Negate(bit96 src);
bit96 Truncate(bit96 src);
bit96 Round(bit96 src);
bit96 Floor(bit96 src);

unsigned char GetRate(bit96 src);  // получаем степень
unsigned char GetSign(bit96 src);  // получаем знак
void SetRate(bit96* dst, unsigned char rate);  // записываем степень
void SetSign(bit96* dst, unsigned char sign);  // записываем знак
// приведение двух чисел к одной степени
void Normalize(bit96 src1, bit96 src2, bit96* dst1, bit96* dst2);
void ZeroSet(bit96* dst);  // обнуляем значения битов
void Bit96Init(bit96* dst);  // инициализация bit96
char ErrorCheck(bit96* dst);  // чек на состояние числа с автоматическим обнулением
void ErrorAdd(bit96* dst, value_type_t value_type);  // добавляем код ошибки и затираем значения

char LimitCheck_l(unsigned long long src);  // проверка на выход за пределы структуры
long3 Bit96ToLong3(bit96 src);  // перенос bit96 в новую структуру
void Long3ToBit96(bit96* dst, long3 src);  // обратная конвертация сруктуры в bit96
void Long3Mul(long3* src, unsigned int mux);  // умножение структуры на число
void Long3Div(long3* src, unsigned int div);  // деление структуры на число
long3 Long3Add(long3 src1, long3 src2);  // сложение структур
long3 Long3Sub(long3 src1, long3 src2);  // вычитание структур
unsigned char Long3Comp(long3 src1, long3 src2);  // сравнение структур
// подготовка переменных для мат операций
unsigned char MathPreparing(bit96 src1, bit96 src2, long3* dst1_int, long3* dst2_int);
// пушим максимально влево без потери точности
void PushLeft(long3* src, unsigned char* rate);
// пушим максимально вправо без потери точности
void PushRight(long3* src, unsigned char* rate);
// финишная подготовка, проверка выхода за границы
void FinishPreparing(bit96* dst, long3 src, char rate, unsigned char sign);
// умножение большой структуры на число в степени
void PowLong7(long7* src, unsigned char mux, char rate);
// проверка ситуаций с невалидными зачениями при сложении
value_type_t AddErrorCheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при вычитании
value_type_t SubErrorCheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при умножении
value_type_t MulErrorCheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при делении
value_type_t DivErrorCheck(bit96 src1, bit96 src2);
// проверка ситуаций с невалидными зачениями при нахождении остатка
value_type_t ModErrorCheck(bit96 src1, bit96 src2);
// непосредственный поиск остатка от деления
bit96 FuncMod(bit96 src1, bit96 src2);
// переносы и очистка при умножении и сложениис тркутур
void Long7Preparing(long7* result);
// сложение больших структур
long7 Long7Add(long7* src1, long7* src2);
// умножение большой структуры на число
void Long7Mul(long7* src, unsigned int mux);
// деление большой структуры на число
void Long7Div(long7* src, unsigned int div);
// получение остатка от деления структуры на число
unsigned int ModLong3UInt(long3 src, unsigned int mux);

#endif  // SRC_BIT96_H_

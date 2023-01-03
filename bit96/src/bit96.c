#include "bit96.h"

    // получаем степень
unsigned char GetRate(bit96 src) {
    return src.bits[3] >> 16;
}

// получаем знак
unsigned char GetSign(bit96 src) {
    int result = src.bits[3];
    result = result >> 15;
    result = result >> 16;
    return (result & 1);
}

// записываем степень
void SetRate(bit96* dst, unsigned char rate) {
    if (rate > 28)
        return;
    int temp = 0;
    temp |= rate;
    temp = temp << 16;
    dst->bits[3] &= ~(255 << 16);  // обнуляем значение степени
    dst->bits[3] |= temp;  // записываем значение степени
}

// записываем знак
void SetSign(bit96* dst, unsigned char sign) {
    if (sign > 1)
        return;
    int temp = 0;
    temp |= sign;
    temp = temp << 15;
    temp = temp << 16;
    dst->bits[3] &= 0x7fffffff;  // обнуляем значение знака
    dst->bits[3] |= temp;  // записываем значение знака
}

// перенос bit96 в новую структуру
long3 Bit96ToLong3(bit96 src) {
    long3 result;
    unsigned int x = 0;  // переменные для избавление следов отрицательного числа
    unsigned int y = 0;
    unsigned int z = 0;
    x |= src.bits[0];
    y |= src.bits[1];
    z |= src.bits[2];
    result.z = z;
    result.y = y;
    result.x = x;
    return result;
}

// обратная конвертация сруктуры в bit96
void int_split_l(bit96* dst, long3 src) {
    dst->bits[0] = 0;  // обнуляем для применения битовой маски
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[0] |= src.x;
    dst->bits[1] |= src.y;
    dst->bits[2] |= src.z;
}

void Normalize(bit96 src1, bit96 src2, bit96* dst1, bit96* dst2) {
    // получаем значение степени
    unsigned char rate1 = GetRate(src1);
    unsigned char rate2 = GetRate(src2);
    // первое число должно быть больше по степени, если нет, то рекурсией меняем местами
    if (rate1 > rate2) {
        Normalize(src2, src1, dst2, dst1);
    } else {
        long3 src1_int = Bit96ToLong3(src1);  // создаём переменные чисел
        long3 src2_int = Bit96ToLong3(src2);
        // двигаем максимально вправо наименьшее число
        while (rate2 > rate1 && (src2_int.x % MUX) == 0 && rate2 > 0) {
            long3_div(&src2_int, MUX);
            rate2 -= 1;
        }
        // двигаем максимально влево наибольшее число
        while (rate2 > rate1 && LimitCheck_l(src1_int.z * MUX) == 0 &&
                rate1 < 28) {
            long3_mul(&src1_int, MUX);
            rate1 += 1;
        }
        // двигаем вправо наименьшее число с потерей точности
        while (rate2 > rate1 && rate2 > 0) {
            long3_div(&src2_int, MUX);
            rate2 -= 1;
        }
        // двигаем всё вправо
        while (rate2 == rate1 && (src1_int.x % MUX) == 0 &&
                (src2_int.x % MUX) == 0 && rate1 > 0) {
            long3_div(&src1_int, MUX);
            long3_div(&src2_int, MUX);
            rate1 -= 1;
            rate2 -= 1;
        }
        // возвращаем значения в переменные
        int_split_l(dst1, src1_int);
        int_split_l(dst2, src2_int);
        SetRate(dst1, rate1);
        SetRate(dst2, rate2);
    }
}

// сравнение структур
unsigned char long3_comp(long3 src1, long3 src2) {
    unsigned char result = 1;
    if (src1.z > src2.z)
        result = 0;
    if (src1.z == src2.z && src1.y > src2.y)
        result = 0;
    if (src1.z == src2.z && src1.y == src2.y && src1.x > src2.x)
        result = 0;
    return result;
}

// сложение структур
long3 long3_add(long3 src1, long3 src2) {
    unsigned int limit = 0xFFFFFFFF;
    long3 result;
    // складываем каждый элемент структуры
    result.x = src1.x + src2.x;
    result.y = src1.y + src2.y;
    result.z = src1.z + src2.z;
    // в случае переполнения переносим на элемент выше
    if (LimitCheck_l(result.x))
        result.y += result.x >> 32;
    if (LimitCheck_l(result.y))
        result.z += result.y >> 32;
    // избавляемся переполнения
    result.x &= limit;
    result.y &= limit;
    return result;
}

// вычитание структур
long3 long3_sub(long3 src1, long3 src2) {
    long3 result;
    result.z = src1.z - src2.z;
    // если у больше, то заимствуем 1 у z
    if (src1.y < src2.y) {
        result.z -= 1;
        result.y = src1.y - src2.y + ((unsigned long long)1 << 32);
    } else {
        result.y = src1.y - src2.y;
    }
    // если у больше, то заимствуем 1 у y, если y == 0, то ещё у z
    if (src1.x < src2.x) {
        if (result.y == 0)
            result.z -= 1;
        result.y -= 1;
        result.x = src1.x - src2.x + ((unsigned long long)1 << 32);
    } else {
        result.x = src1.x - src2.x;
    }
    return result;
}

// умножение структуры на число
void long3_mul(long3* src, unsigned int mux) {
    unsigned int limit = 0xFFFFFFFF;
    // умножаем каждый элемент структуры на множитель
    src->x *= mux;
    src->y *= mux;
    src->z *= mux;
    // в случае переполнения переносим на элемент выше
    if (LimitCheck_l(src->x))
        src->y += src->x >> 32;
    if (LimitCheck_l(src->y))
        src->z += src->y >> 32;
    // избавляемся переполнения
    src->x &= limit;
    src->y &= limit;
}

// деление структуры на число
void long3_div(long3* src, unsigned int div) {
    // в случае наличия остатка переносим его в меньшему числу
    src->y += (src->z % div) << 32;
    src->x += (src->y % div) << 32;
    // делим каждый элемент структуры на делитель
    src->x /= div;
    src->y /= div;
    src->z /= div;
}

// обнуляем значения битов
void ZeroSet(bit96* dst) {
    dst->bits[0] = ZERO;
    dst->bits[1] = ZERO;
    dst->bits[2] = ZERO;
    dst->bits[3] = ZERO;
}

// инициализация bit96
void Bit96Init(bit96* dst) {
    ZeroSet(dst);
    dst->value_type = 0;
}

// чек на состояние числа с автоматическим обнулением
char ErrorCheck(bit96* dst) {
    char result = 0;
    if (dst->value_type != 0) {
        ZeroSet(dst);
        result = 1;
    }
    return result;
}

// добавляем код ошибки и затираем значения
void ErrorAdd(bit96* dst, value_type_t value_type) {
    dst->value_type = value_type;
    ErrorCheck(dst);
}

// проверка на выход за пределы структуры
char LimitCheck_l(unsigned long long src) {
    return (src >= ((unsigned long long)1 << 32));
}

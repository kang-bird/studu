#include "bit96.h"

// подготовка переменных для мат операций
unsigned char math_preparing_l(bit96 src1, bit96 src2,
        long3* dst1_int, long3* dst2_int) {
    bit96 dst1, dst2;
    Bit96Init(&dst1);
    Bit96Init(&dst2);
    Normalize(src1, src2, &dst1, &dst2);
    *dst1_int = Bit96ToLong3(dst1);
    *dst2_int = Bit96ToLong3(dst2);
    return GetRate(dst1);
}

// пушим максимально влево без потери точности
void push_left_l(long3* src, unsigned char* rate) {
    while (*rate < 28 && LimitCheck_l(src->z * MUX) == 0) {
        long3_mul(src, MUX);
        *rate += 1;
    }
}

// пушим максимально вправо без потери точности
void push_right_l(long3* src, unsigned char* rate) {
    while (*rate > 0 && (src->x % MUX) == 0) {
        long3_div(src, MUX);
        *rate -= 1;
    }
}

// финишная подготовка, проврка выхода за границы
void finish_preparing_l(bit96* dst, long3 src,
        char rate, unsigned char sign) {
    // выравнимваем значение степени, если стало меньше нуля
    while (rate < 0 && LimitCheck_l(src.z * MUX) == 0) {
        long3_mul(&src, MUX);
        rate += 1;
    }
    // обрезаем слишком длинное число
    while (rate > 0 && LimitCheck_l(src.z) != 0) {
        long3_div(&src, MUX);
        rate -= 1;
    }
    // выравнимваем значение степени, если число слишком маленькое
    while (rate > 28) {
        long3_div(&src, MUX);
        rate -= 1;
    }
    // если степень отрицательная, значит число слишком большое
    if (rate < 0) {
        ErrorAdd(dst, 1 + sign);
    } else {
        // ставим знак
        SetSign(dst, sign);
        SetRate(dst, rate);
        int_split_l(dst, src);
    }
}

// умножение большой структуры на число в степени
void pow128_l_l(long7* src, unsigned char mux, char rate) {
    while (rate > 0) {
        long7_mul(src, mux);
        rate -= 1;
    }
}

// получение остатка от деления большой структуры на число
unsigned int mod128_l(long3 src, unsigned int mux) {
    unsigned int result;
    if (mux != 0) {
        while (src.z != 0 || src.y != 0) {
            long3 x_int = { mux, 0, 0 };
            while (!long3_comp(src, x_int)) {
                long3_mul(&x_int, 10);
            }
            long3_div(&x_int, 10);
            src = long3_sub(src, x_int);
        }
        result = src.x % mux;
    } else {
        result = 0;
    }
    return  result;
}

// переносы и очистка при умножении и сложениис тркутур
void long7_preparing(long7* result) {
    unsigned int limit = 0xFFFFFFFF;
    // в случае переполнения переносим на элемент выше
    if (LimitCheck_l(result->x0))
        result->x1 += result->x0 >> 32;
    if (LimitCheck_l(result->x1))
        result->x2 += result->x1 >> 32;
    if (LimitCheck_l(result->x2))
        result->x3 += result->x2 >> 32;
    if (LimitCheck_l(result->x3))
        result->x4 += result->x3 >> 32;
    if (LimitCheck_l(result->x4))
        result->x5 += result->x4 >> 32;
    if (LimitCheck_l(result->x5))
        result->x6 += result->x5 >> 32;
    // избавляемся переполнения
    result->x0 &= limit;
    result->x1 &= limit;
    result->x2 &= limit;
    result->x3 &= limit;
    result->x4 &= limit;
    result->x5 &= limit;
}

// сложение больших структур
long7 long7_add(long7* src1, long7* src2) {
    long7 result;
    // складываем каждый элемент структуры
    result.x0 = src1->x0 + src2->x0;
    result.x1 = src1->x1 + src2->x1;
    result.x2 = src1->x2 + src2->x2;
    result.x3 = src1->x3 + src2->x3;
    result.x4 = src1->x4 + src2->x4;
    result.x5 = src1->x5 + src2->x5;
    result.x6 = src1->x6 + src2->x6;
    long7_preparing(&result);
    return result;
}


// умножение большой структуры на число
void long7_mul(long7* src, unsigned int mux) {
    // умножаем каждый элемент структуры на множитель
    src->x0 *= mux;
    src->x1 *= mux;
    src->x2 *= mux;
    src->x3 *= mux;
    src->x4 *= mux;
    src->x5 *= mux;
    src->x6 *= mux;
    long7_preparing(src);
}

// деление большой структуры на число
void long7_div(long7* src, unsigned int div) {
    // в случае наличия остатка переносим его в меньшему числу
    src->x5 += (src->x6 % div) << 32;
    src->x4 += (src->x5 % div) << 32;
    src->x3 += (src->x4 % div) << 32;
    src->x2 += (src->x3 % div) << 32;
    src->x1 += (src->x2 % div) << 32;
    src->x0 += (src->x1 % div) << 32;
    // делим каждый элемент структуры на делитель
    src->x0 /= div;
    src->x1 /= div;
    src->x2 /= div;
    src->x3 /= div;
    src->x4 /= div;
    src->x5 /= div;
    src->x6 /= div;
}

// проверка ситуаций с невалидными зачениями при сложении
value_type_t add_errcheck(bit96 src1, bit96 src2) {
    value_type_t result = dNORMAL_VALUE;
    // любой равен dNAN, значит ответ dNAN
    if (src1.value_type == dNAN || src2.value_type == dNAN)
        result = dNAN;
    // если оба равны бесконечности с разными знаками, то dNAN
    else if ((src1.value_type == dINFINITY &&
            src2.value_type == dNEGATIVE_INFINITY) ||
            (src2.value_type == dINFINITY &&
            src1.value_type == dNEGATIVE_INFINITY))
        result = dNAN;
    // если один или оба равны бесконечности, то бесконечность
    else if (src1.value_type == dINFINITY ||
            src2.value_type == dINFINITY)
        result = dINFINITY;
    // если один или оба равны минус бесконечности, то минус бесконечность
    else if (src1.value_type == dNEGATIVE_INFINITY ||
            src2.value_type == dNEGATIVE_INFINITY)
        result = dNEGATIVE_INFINITY;
    return result;
}

// проверка ситуаций с невалидными зачениями при вычитании
value_type_t sub_errcheck(bit96 src1, bit96 src2) {
    value_type_t result = dNORMAL_VALUE;
    // любой равен dNAN, значит ответ dNAN
    if (src1.value_type == dNAN || src2.value_type == dNAN)
        result = dNAN;
    // если оба равны бесконечности, то dNAN
    else if ((src1.value_type == dINFINITY &&
            src2.value_type == dINFINITY) ||
            (src2.value_type == dNEGATIVE_INFINITY &&
            src1.value_type == dNEGATIVE_INFINITY))
        result = dNAN;
    // если вычитаемое бесконечно, а вычитатель минус бесконечность, то бесконечность
    else if (src1.value_type == dINFINITY ||
            src2.value_type == dNEGATIVE_INFINITY)
        result = dINFINITY;
    // если вычитаемое минус бесконечноcть, а вычитетль бесконечность, то минус бесконечность
    else if (src1.value_type == dNEGATIVE_INFINITY ||
            src2.value_type == dINFINITY)
        result = dNEGATIVE_INFINITY;
    return result;
}

// проверка ситуаций с невалидными зачениями при умножении
value_type_t mul_errcheck(bit96 src1, bit96 src2) {
    value_type_t result = dNORMAL_VALUE;
    // любой равен dNAN, значит ответ dNAN
    if (src1.value_type == dNAN || src2.value_type == dNAN)
        result = dNAN;
    // один равен нулю, а второй бесконечности тогда dNAN
    else if ((src1.value_type != dNORMAL_VALUE &&
                src2.value_type == dNORMAL_VALUE &&
              src2.bits[0] == 0 && src2.bits[1] == 0 && src2.bits[2] == 0) ||
            (src2.value_type != dNORMAL_VALUE &&
                src1.value_type == dNORMAL_VALUE &&
             src1.bits[0] == 0 && src1.bits[1] == 0 && src1.bits[2] == 0))
        result = dNAN;
    // если оба равны бесконечности с разными знаками, то минус бесконечность
    else if ((src1.value_type == dINFINITY &&
            src2.value_type == dNEGATIVE_INFINITY) ||
            (src2.value_type == dINFINITY &&
            src1.value_type == dNEGATIVE_INFINITY))
        result = dNEGATIVE_INFINITY;
    // если оба равны бесконечности с одинаковыми знаками, то бесконечность
    else if ((src1.value_type == dINFINITY &&
            src2.value_type == dINFINITY) ||
            (src2.value_type == dNEGATIVE_INFINITY &&
            src1.value_type == dNEGATIVE_INFINITY))
        result = dINFINITY;
    // если первый бесконечность то бесконечность и знак
    else if (src1.value_type == dINFINITY &&
            src2.value_type == dNORMAL_VALUE)
        result = 1 + GetSign(src2);
    // если первый минус бесконечность то бесконечность и знак
    else if (src1.value_type == dNEGATIVE_INFINITY &&
            src2.value_type == dNORMAL_VALUE)
        result = 2 - GetSign(src2);
    // если второй бесконечность то бесконечность и знак
    else if (src2.value_type == dINFINITY &&
            src1.value_type == dNORMAL_VALUE)
        result = 1 + GetSign(src1);
     // если второй минус бесконечность то бесконечность и знак
    else if (src2.value_type == dNEGATIVE_INFINITY &&
            src1.value_type == dNORMAL_VALUE)
        result = 2 - GetSign(src1);
    return result;
}

// проверка ситуаций с невалидными зачениями при делении
value_type_t div_errcheck(bit96 src1, bit96 src2) {
    value_type_t result = dNORMAL_VALUE;
    // любой равен dNAN, значит ответ dNAN
    if (src1.value_type == dNAN || src2.value_type == dNAN)
        result = dNAN;
    // если оба равны бесконечности, то dNAN
    else if ((src1.value_type == dINFINITY ||
            src1.value_type == dNEGATIVE_INFINITY) &&
            (src2.value_type == dINFINITY ||
            src2.value_type == dNEGATIVE_INFINITY))
        result = dNAN;
    // если первый бесконечность то бесконечность и знак
    else if (src1.value_type == dINFINITY &&
            src2.value_type == dNORMAL_VALUE)
        result = 1 + GetSign(src2);
    // если первый минус бесконечность то бесконечность и знак
    else if (src1.value_type == dNEGATIVE_INFINITY &&
            src2.value_type == dNORMAL_VALUE)
        result = 2 - GetSign(src2);
    // если делитель и делимое 0, то dNAN
    else if (src1.value_type == dNORMAL_VALUE &&
                src2.value_type == dNORMAL_VALUE &&
             src1.bits[0] == 0 && src1.bits[1] == 0 && src1.bits[2] == 0
             && src2.bits[0] == 0 && src2.bits[1] == 0 && src2.bits[2] == 0)
        result = dNAN;
    // если делитель 0, то бесконечность
    else if (src1.value_type == dNORMAL_VALUE &&
                src2.value_type == dNORMAL_VALUE &&
             src2.bits[0] == 0 && src2.bits[1] == 0 && src2.bits[2] == 0)
        result = 1 + GetSign(src1);
    return result;
}

// проверка ситуаций с невалидными зачениями при остатке от деления
value_type_t mod_errcheck(bit96 src1, bit96 src2) {
    value_type_t result = dNORMAL_VALUE;
    // любой равен dNAN, значит ответ dNAN
    if (src1.value_type == dNAN || src2.value_type == dNAN)
        result = dNAN;
    // если оба равны бесконечности, то dNAN
    else if ((src1.value_type == dINFINITY ||
            src1.value_type == dNEGATIVE_INFINITY) &&
            (src2.value_type == dINFINITY ||
            src2.value_type == dNEGATIVE_INFINITY))
        result = dNAN;
    // если делитель 0, то dNAN
    else if (src2.value_type == dNORMAL_VALUE &&
                src2.bits[0] == 0 && src2.bits[1] == 0 && src2.bits[2] == 0)
        result = dNAN;
    // если первый бесконечность то бесконечность
    else if (src1.value_type == dINFINITY &&
            src2.value_type == dNORMAL_VALUE)
        result = dINFINITY;
    // если первый минус бесконечность то минус бесконечность
    else if (src1.value_type == dNEGATIVE_INFINITY &&
            src2.value_type == dNORMAL_VALUE)
        result = dNEGATIVE_INFINITY;
    return result;
}

bit96 add(bit96 src1, bit96 src2) {
    bit96 result;
    Bit96Init(&result);
    // проверка на входные кривые значения
    result.value_type = add_errcheck(src1, src2);
    // если знаки равны, то у нас сложение
    if (GetSign(src1) == GetSign(src2) &&
            result.value_type == dNORMAL_VALUE) {
        long3 dst1_int, dst2_int;
        unsigned char rate = math_preparing_l(src1, src2, &dst1_int, &dst2_int);
        long3 result_int = long3_add(dst1_int, dst2_int);
        // прогоняем цикл для отбрасывания лишнего у малых длинных чисел
        while (rate > 0 && LimitCheck_l(result_int.z) != 0) {
            long3_div(&result_int, MUX);
            rate -= 1;
        }
        SetSign(&result, GetSign(src1));
        if (LimitCheck_l(result_int.z)) {
            if (GetSign(result))
                ErrorAdd(&result, dNEGATIVE_INFINITY);
            else
                ErrorAdd(&result, dINFINITY);
        } else {
            int_split_l(&result, result_int);
            SetRate(&result, rate);
            Normalize(result, result, &result, &result);  // номрализуем результат
        }
    } else if (result.value_type == dNORMAL_VALUE) {
        if (GetSign(src1)) {
            SetSign(&src1, !(GetSign(src1)));
            result = sub(src2, src1);
        } else {
            SetSign(&src2, !(GetSign(src2)));
            result = sub(src1, src2);
        }
    }
    return result;
}

bit96 sub(bit96 src1, bit96 src2) {
    bit96 result;
    Bit96Init(&result);
    // использовать функцию Negate для инвесии знака
    SetSign(&src2, !(GetSign(src2)));
    // проверяем на ошибки функцией сложения после изменения знака
    result.value_type = sub_errcheck(src1, src2);
    // если знаки не равны, то у нас вычитание
    if (GetSign(src1) != GetSign(src2) &&
            result.value_type == dNORMAL_VALUE) {
        long3 result_int, dst1_int, dst2_int;
        unsigned char rate = math_preparing_l(src1, src2, &dst1_int, &dst2_int);
        if (!long3_comp(dst1_int, dst2_int)) {
            result_int = long3_sub(dst1_int, dst2_int);
        } else {
            result_int = long3_sub(dst2_int, dst1_int);
           // result_int = dst2_int - dst1_int;
        }
        // прогоняем цикл для отбрасывания лишнего у малых длинных чисел
        while (rate > 0 && LimitCheck_l(result_int.z) != 0) {
            long3_div(&result_int, MUX);
            rate -= 1;
        }
        // присваиваем знак вычитаемго
        if (!long3_comp(dst1_int, dst2_int))
            SetSign(&result, GetSign(src1));
        else
            SetSign(&result, GetSign(src2));
        if (LimitCheck_l(result_int.z)) {
            if (GetSign(result))
                ErrorAdd(&result, dNEGATIVE_INFINITY);
            else
                ErrorAdd(&result, dINFINITY);
        } else {
            int_split_l(&result, result_int);
            SetRate(&result, rate);
            Normalize(result, result, &result, &result);  // номрализуем результат
        }
    } else if (result.value_type == dNORMAL_VALUE) {
        result = add(src1, src2);
    }
    return result;
}


bit96 mul(bit96 src1, bit96 src2) {
    bit96 result;
    Bit96Init(&result);
    result.value_type = mul_errcheck(src1, src2);
    if (result.value_type == dNORMAL_VALUE) {
        long7 result_int = { 0, 0, 0, 0, 0, 0, 0};
        long3 dst1_int = Bit96ToLong3(src1);
        long3 dst2_int = Bit96ToLong3(src2);
        unsigned char rate1 = GetRate(src1);
        unsigned char rate2 = GetRate(src2);
        char rate_result = 0;
        // двигаем максимально вправо оба множителя
        push_right_l(&dst1_int, &rate1);
        push_right_l(&dst2_int, &rate2);
        rate_result = rate1 + rate2;
        unsigned char count = 0;
        while (dst2_int.z != 0 || dst2_int.y != 0 ||
                dst2_int.x != 0) {
            unsigned int x = mod128_l(dst2_int, MUX);
            long7 temp = { dst1_int.x, dst1_int.y,
                dst1_int.z, 0, 0, 0, 0 };
            long7_mul(&temp, x);
            pow128_l_l(&temp, MUX, count);
            result_int = long7_add(&result_int, &temp);

                count += 1;
                long3_div(&dst2_int, MUX);
        }
        while (LimitCheck_l(result_int.x0) != 0 ||
                LimitCheck_l(result_int.x1) != 0 ||
                LimitCheck_l(result_int.x2) != 0 ||
                result_int.x3 != 0 || result_int.x4 != 0 ||
                result_int.x5 != 0 || result_int.x6 != 0) {
            long7_div(&result_int, MUX);
            rate_result -= 1;
        }
        if (rate_result < 0) {
            ErrorAdd(&result, 1 + (GetSign(src1) ^ GetSign(src2)));
        } else {
            long3 res = {result_int.x0, result_int.x1,
                result_int.x2 };
            finish_preparing_l(&result, res, rate_result,
            GetSign(src1) ^ GetSign(src2));
        }
    }
    return result;
}

bit96 div(bit96 src1, bit96 src2) {
    bit96 result;
    Bit96Init(&result);
    result.value_type = div_errcheck(src1, src2);
    if (result.value_type == dNORMAL_VALUE && src2.value_type == dNORMAL_VALUE) {
        long3 result_int = { 0, 0, 0 };
        long3 dst1_int = Bit96ToLong3(src1);
        long3 dst2_int = Bit96ToLong3(src2);
        unsigned char rate1 = GetRate(src1);
        unsigned char rate2 = GetRate(src2);
        char rate_result;
        // двигаем делимое максимально влево, делитель максимально вправо
        push_left_l(&dst1_int, &rate1);
        push_right_l(&dst2_int, &rate2);
        while (long3_comp(dst2_int, dst1_int)) {
            long3 x_int = { dst2_int.x, dst2_int.y, dst2_int.z };
            long3 count = { 1, 0, 0};
            while (long3_comp(x_int, dst1_int)) {
                long3_mul(&x_int, 10);
                long3_mul(&count, 10);
            }
            long3_div(&x_int, 10);
            long3_div(&count, 10);
            dst1_int = long3_sub(dst1_int, x_int);
            result_int = long3_add(result_int, count);
        }
        rate_result = rate1 - rate2;
        finish_preparing_l(&result, result_int, rate_result,
                GetSign(src1) ^ GetSign(src2));
        rate_result = rate1 - rate2;
        finish_preparing_l(&result, result_int, rate_result,
                GetSign(src1) ^ GetSign(src2));
    }
    return result;
}


bit96 mod(bit96 src1, bit96 src2) {
    bit96 nul = { { 0, 0, 0, 0 }, dNORMAL_VALUE };
    bit96 result;
    Bit96Init(&result);
    result.value_type = mod_errcheck(src1, src2);
    if (result.value_type == dNORMAL_VALUE) {
        if ((src2.value_type == dINFINITY ||
            src2.value_type == dNEGATIVE_INFINITY) &&
            src1.value_type == dNORMAL_VALUE) {
            result.bits[0] = src1.bits[0];
            result.bits[1] = src1.bits[1];
            result.bits[2] = src1.bits[2];
            result.bits[3] = src1.bits[3];
            result.value_type = src1.value_type;
        } else {
            int sign = 0;
            if (GetSign(src1) == 1) {
                sign = 1;
                SetSign(&src1, !GetSign(src1));
            }
            if (GetSign(src2) == 1) {
                SetSign(&src2, !GetSign(src2));
            }
            if (is_equal(src1, src2) == 0) {
                ZeroSet(&result);
            } else if (is_less(src1, src2) == 0) {
                result.bits[0] = src1.bits[0];
                result.bits[1] = src1.bits[1];
                result.bits[2] = src1.bits[2];
                result.bits[3] = src1.bits[3];
                if (sign == 1) {
                    SetSign(&result, 1);
                }
            } else {
                if (is_not_equal(src2, nul) == 0) {
                    unsigned char rate;
                    bit96 dst1, dst2;
                    Bit96Init(&dst1);
                    Bit96Init(&dst2);
                    Normalize(src1, src2, &dst1, &dst2);
                    rate = GetRate(dst1);
                    result = fun_mod(dst1, dst2);
                    SetRate(&result, rate);
                    if (sign == 1) {
                        SetSign(&result, 1);
                    }
                } else {
                    ZeroSet(&result);
                    result.value_type = dNAN;
                }
            }
        }
    }
    return result;
}

bit96 fun_mod(bit96 src1, bit96 src2) {
    bit96 result;
    Bit96Init(&result);
    result.value_type = mod_errcheck(src1, src2);
        long3 result_int = { 0, 0, 0 };
        long3 dst1_int = Bit96ToLong3(src1);
        long3 dst2_int = Bit96ToLong3(src2);
        unsigned char rate1 = GetRate(src1);
        unsigned char rate2 = GetRate(src2);
        char rate_result;
        // двигаем делимое максимально влево, делитель максимально вправо
        while (long3_comp(dst2_int, dst1_int)) {
            long3 x_int = { dst2_int.x, dst2_int.y, dst2_int.z };
            long3 count = { 1, 0, 0};
            while (long3_comp(x_int, dst1_int)) {
                long3_mul(&x_int, 10);
            }
            long3_div(&x_int, 10);
            dst1_int = long3_sub(dst1_int, x_int);
        }
        result_int.x = dst1_int.x;
        result_int.y = dst1_int.y;
        result_int.z = dst1_int.z;
        rate_result = rate1 - rate2;
        finish_preparing_l(&result, result_int, rate_result,
                GetSign(src1) ^ GetSign(src2));
        rate_result = rate1 - rate2;
        finish_preparing_l(&result, result_int, rate_result,
                GetSign(src1) ^ GetSign(src2));
    return result;
}

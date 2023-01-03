#include "bit96.h"

// src1 < src2, 0 positive, 1 negative
// 0 TRUE 1 FALSE
int is_less(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNORMAL_VALUE && src2.value_type == dNORMAL_VALUE) {
        if (GetSign(src1) < GetSign(src2)) {
            result = 1;
        } else if (GetSign(src1) == GetSign(src2)) {
            bit96 src3 = sub(src1, src2);
            if (GetSign(src3) != 1 || (src3.bits[0] == 0 && src3.bits[1] == 0 && src3.bits[2] == 0)) {
                result = 1;
            }
        }
    } else if (src1.value_type == dNAN || src2.value_type == dNAN) {
        result = 1;
    } else if (src1.value_type == dINFINITY || src2.value_type == dNEGATIVE_INFINITY) {
        result = 1;
    }
    return result;
}

int is_greater(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNORMAL_VALUE && src2.value_type == dNORMAL_VALUE) {
        result = is_less(src2, src1);
    } else if (src1.value_type == dNAN || src2.value_type == dNAN) {
        result = 1;
    } else if (src2.value_type == dINFINITY || src1.value_type == dNEGATIVE_INFINITY) {
        result = 1;
    }
    return result;
}

int is_less_or_equal(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNAN || src2.value_type == dNAN) {
        result = 1;
    } else {
        result = !is_greater(src1, src2);
    }
    return result;
}

int is_greater_or_equal(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNAN || src2.value_type == dNAN) {
        result = 1;
    } else {
        result = !is_less(src1, src2);
    }
    return result;
}

int is_equal(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNORMAL_VALUE && src2.value_type == dNORMAL_VALUE) {
        if (GetSign(src1) != GetSign(src2)) {
            result = 1;
        } else {
            bit96 src3 = sub(src1, src2);
            if ((src3.bits[0] != 0 || src3.bits[1] != 0 && src3.bits[2] != 0)) {
                result = 1;
            }
        }
    } else if (src1.value_type == dINFINITY && src2.value_type == dINFINITY) {
    } else if (src1.value_type == dNEGATIVE_INFINITY && src2.value_type == dNEGATIVE_INFINITY) {
    } else {
        result = 1;
    }
    return result;
}

int is_not_equal(bit96 src1, bit96 src2) {
    return !is_equal(src1, src2);
}

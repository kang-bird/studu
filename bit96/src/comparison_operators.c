#include "bit96.h"

// src1 < src2, 0 positive, 1 negative
// 0 TRUE 1 FALSE
int IsLess(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNORMAL_VALUE && src2.value_type == dNORMAL_VALUE) {
        if (GetSign(src1) < GetSign(src2)) {
            result = 1;
        } else if (GetSign(src1) == GetSign(src2)) {
            bit96 src3 = Sub(src1, src2);
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

int IsGreater(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNORMAL_VALUE && src2.value_type == dNORMAL_VALUE) {
        result = IsLess(src2, src1);
    } else if (src1.value_type == dNAN || src2.value_type == dNAN) {
        result = 1;
    } else if (src2.value_type == dINFINITY || src1.value_type == dNEGATIVE_INFINITY) {
        result = 1;
    }
    return result;
}

int IsLessOrEqual(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNAN || src2.value_type == dNAN) {
        result = 1;
    } else {
        result = !IsGreater(src1, src2);
    }
    return result;
}

int IsGreaterOrEqual(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNAN || src2.value_type == dNAN) {
        result = 1;
    } else {
        result = !IsLess(src1, src2);
    }
    return result;
}

int IsEqual(bit96 src1, bit96 src2) {
    int result = 0;
    if (src1.value_type == dNORMAL_VALUE && src2.value_type == dNORMAL_VALUE) {
        if (GetSign(src1) != GetSign(src2)) {
            result = 1;
        } else {
            bit96 src3 = Sub(src1, src2);
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

int IsNotEqual(bit96 src1, bit96 src2) {
    return !IsEqual(src1, src2);
}

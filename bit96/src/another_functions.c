#include "bit96.h"

bit96 Negate(bit96 src) {
    if (src.value_type == dNORMAL_VALUE) {
        SetSign(&src, !GetSign(src));
    } else if (src.value_type == dINFINITY) {
        src.value_type = dNEGATIVE_INFINITY;
        ZeroSet(&src);
    } else if (src.value_type == dNEGATIVE_INFINITY) {
        src.value_type = dINFINITY;
        ZeroSet(&src);
    } else {
        ZeroSet(&src);
    }
    return src;
}

bit96 Truncate(bit96 src) {
    if (src.value_type == dNORMAL_VALUE) {
        long3 src1 = Bit96ToLong3(src);
        unsigned char rate = GetRate(src);
        for (int i = 0; i < rate; i++) {
            long3_div(&src1, 10);
        }
        int_split_l(&src, src1);
        SetRate(&src, 0);
    } else {
        ZeroSet(&src);
    }
    return src;
}

bit96 Round(bit96 src) {
    if (src.value_type == dNORMAL_VALUE) {
        int sign = GetSign(src);
        SetSign(&src, 0);
        bit96 one = { { 1, 0, 0, 0 }, dNORMAL_VALUE };
        bit96 half = { { 5, 0, 0, 0x0010000 }, dNORMAL_VALUE };
        long3 src1 = Bit96ToLong3(src);
        bit96 src2 = src;
        unsigned char rate = GetRate(src);
        for (int i = 0; i < rate; i++) {
            long3_div(&src1, 10);
        }
        int_split_l(&src, src1);
        SetRate(&src, 0);
        src2 = sub(src2, src);
        if (is_greater_or_equal(src2, half) == 0) {
            src = add(src, one);
        }
        if (sign != 0) {
            SetSign(&src, 1);
        }
    } else {
        ZeroSet(&src);
    }
    return src;
}

bit96 Floor(bit96 src) {
    if (src.value_type == dNORMAL_VALUE) {
        int sign = GetSign(src);
        SetSign(&src, 0);
        bit96 one = { { 1, 0, 0, 0 }, dNORMAL_VALUE };
        bit96 nul = { { 0, 0, 0, 0x0000000 }, dNORMAL_VALUE };
        long3 src1 = Bit96ToLong3(src);
        bit96 src2 = src;
        unsigned char rate = GetRate(src);
        for (int i = 0; i < rate; i++) {
            long3_div(&src1, 10);
        }
        int_split_l(&src, src1);
        SetRate(&src, 0);
        src2 = sub(src2, src);
        if (is_greater(src2, nul) == 0 && sign != 0) {
            src = add(src, one);
        }
        if (sign != 0) {
            SetSign(&src, 1);
        }
    } else {
        ZeroSet(&src);
    }
    return src;
}

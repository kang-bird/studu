#include "bit96.h"

int from_int_to_bit96(int src, bit96 *dst) {
    int result = 0;
    if (dst == 0) {
        result = 1;
    } else {
        Bit96Init(dst);
        dst->value_type = dNORMAL_VALUE;
        if (src > 0) {
            dst->bits[0] = src;
            SetSign(dst, 0);
        } else {
            src = src * -1;
            dst->bits[0] = src;
            SetSign(dst, 1);
        }
    }
    return result;
}

int from_bit96_to_int(bit96 src, int *dst) {
    int result = 0;
    if (dst == 0) {
        result = 1;
    } else {
        if (src.value_type == 0) {
            src = Truncate(src);
            if (src.bits[0] < 2147483647 && src.bits[0] > -2147483647 && src.bits[1] == 0
                && src.bits[2] == 0 && (src.bits[0] & 0x80000000) == 0) {
                if (GetSign(src) == 1) {
                    *dst = src.bits[0];
                    *dst = *dst * (-1);
                } else {
                    *dst = src.bits[0];
                }
            } else {
                result = 1;
            }
        } else {
            result = 1;
        }
    }
    return result;
}

int from_float_to_bit96(float src, bit96 *dst) {
    int result = 0;
    if (dst == 0) {
        result = 1;
    } else {
        float src1 = 0;
        int ch_sign = 0;
        Bit96Init(dst);
        if (src < 0) {
            src1 = src * -1;
            ch_sign = 1;
        } else {
            src1 = src;
        }
        if (isinf(src) == 0) {
            if (isnan(src) != 0 || (src1 > 79228162514264337593543950335.0 || (src1 > 0 && src1 < 1e-28))) {
                result = 1;
                if (src1 > 0 && src1 < 1e-28) {
                    dst->value_type = 0;
                } else if (src1 > 79228162514264337593543950335.0) {
                    if (ch_sign == 1) {
                        dst->value_type = dNEGATIVE_INFINITY;
                    } else {
                        dst->value_type = dINFINITY;
                    }
                } else {
                    dst->value_type = dNAN;
                }
            } else {
                float x, m;
                int n;
                x = src;
                m = frexpf(x, &n);
                bit96 dec1 = { { 2, 0, 0, 0x0000000 }, dNORMAL_VALUE };
                dst->bits[0] = 2;
                if (n > 1) {
                    for (int j = 0; j < n - 1; j++) {
                        *dst = mul(*dst, dec1);
                    }
                } else if (n <= 0) {
                    dec1.bits[0] = 5;
                    SetRate(&dec1, 1);
                    for (int j = n; j <= 0; j++) {
                        *dst = mul(*dst, dec1);
                    }
                }
                int r2 = 0;
                r2 = 8;
                m = m * 100000000.0;
                bit96 dec3 = { { 1, 0, 0, 0x0000000 }, dNORMAL_VALUE };
                if (m < 0) {
                    SetSign(&dec3, 1);
                    m = m * (-1);
                }
                long3 dec4 = Bit96ToLong3(dec3);
                long3_mul(&dec4, m);
                int_split_l(&dec3, dec4);
                SetRate(&dec3, r2);
                *dst = mul(*dst, dec3);
                if (src > 0) {
                    SetSign(dst, 0);
                } else {
                    SetSign(dst, 1);
                }
                dst->value_type = dNORMAL_VALUE;
            }
        } else {
            result = 1;
            if (ch_sign == 1) {
                dst->value_type = dNEGATIVE_INFINITY;
            } else {
                dst->value_type = dINFINITY;
            }
        }
    }
    return result;
}


int from_bit96_to_float(bit96 src, float *dst) {
    int result = 0;
    if (!dst) {
        result = 1;
    } else {
        if (src.value_type == 0) {
            double res;
            unsigned char rate = GetRate(src);
            res = pow(2, 64) * src.bits[2];
            res += pow(2, 32) * src.bits[1];
            res += src.bits[0];
            while (rate != 0) {
                res = res / 10;
                rate--;
            }
            if (GetSign(src) == 1) {
                res = -res;
            }
            *dst = res;
        } else {
            result = 1;
        }
    }
    return result;
}

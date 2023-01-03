#include "bit96.h"
#include <check.h>
#include <stdio.h>

// MARK: - Convertors

START_TEST(from_int_to_bit96_test) {
    int src1 = 2000;
    bit96 dec1;
    from_int_to_bit96(src1, &dec1);
    int x = 0, y = 0, z = 2000;
    ck_assert_int_eq(GetRate(dec1), 0);
    ck_assert_int_eq(GetSign(dec1), 0);
    ck_assert_mem_eq(dec1.bits + 2, &x, 4);
    ck_assert_mem_eq(dec1.bits + 1, &y, 4);
    ck_assert_mem_eq(dec1.bits, &z, 4);
    int src2 = -2000;
    bit96 dec2;
    from_int_to_bit96(src2, &dec2);
    x = 0, y = 0, z = 2000;
    ck_assert_int_eq(GetRate(dec2), 0);
    ck_assert_int_eq(GetSign(dec2), 1);
    ck_assert_mem_eq(dec2.bits + 2, &x, 4);
    ck_assert_mem_eq(dec2.bits + 1, &y, 4);
    ck_assert_mem_eq(dec2.bits, &z, 4);
}
END_TEST

START_TEST(from_bit96_to_int_test) {
    bit96 dec1 = { { 2000, 0, 0, 0x0000000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 2000, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 2000, 0, 0, 0x80000000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 2000, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 2000, 20, 20, 0x0000000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 2000, 20, 0, 0x0000000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec11 = { { 0xffffffff, 0, 0, 0x0000000 }, dNORMAL_VALUE };
    int dst1, dst2, dst3, dst4, dst5;
    ck_assert_int_eq(from_bit96_to_int(dec1, &dst1), 0);
    ck_assert_int_eq(from_bit96_to_int(dec2, &dst2), 0);
    ck_assert_int_eq(from_bit96_to_int(dec3, &dst3), 0);
    ck_assert_int_eq(from_bit96_to_int(dec4, &dst4), 0);
    ck_assert_int_eq(from_bit96_to_int(dec5, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_int(dec6, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_int(dec7, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_int(dec8, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_int(dec9, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_int(dec10, &dst5), 0);
    ck_assert_int_eq(from_bit96_to_int(dec11, &dst1), 1);
    ck_assert_int_eq(dst1, 2000);
    ck_assert_int_eq(dst2, 20);
    ck_assert_int_eq(dst3, -2000);
    ck_assert_int_eq(dst4, -20);
    ck_assert_int_eq(dst5, 0);
}
END_TEST

START_TEST(from_float_to_bit96_test) {
    float src1 = 0.25e26;
    bit96 dec1;
    ck_assert_int_eq(from_float_to_bit96(src1, &dec1), 0);
    int x = 1355252771, y = 265257180, z = 863116627;
    ck_assert_int_eq(GetRate(dec1), 3);
    ck_assert_int_eq(GetSign(dec1), 0);
    ck_assert_mem_eq(dec1.bits + 2, &x, 4);
    ck_assert_mem_eq(dec1.bits + 1, &y, 4);
    ck_assert_mem_eq(dec1.bits, &z, 4);
    float src2 = 7.9e30;
    bit96 dec2;
    ck_assert_int_eq(from_float_to_bit96(src2, &dec2), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec2), 0);
    ck_assert_int_eq(GetSign(dec2), 0);
    ck_assert_mem_eq(dec2.bits + 2, &x, 4);
    ck_assert_mem_eq(dec2.bits + 1, &y, 4);
    ck_assert_mem_eq(dec2.bits, &z, 4);
    ck_assert_int_eq(dec2.value_type, 1);
    float src3 = dINFINITY;
    bit96 dec3;
    ck_assert_int_eq(from_float_to_bit96(src3, &dec3), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec3), 0);
    ck_assert_int_eq(GetSign(dec3), 0);
    ck_assert_mem_eq(dec3.bits + 2, &x, 4);
    ck_assert_mem_eq(dec3.bits + 1, &y, 4);
    ck_assert_mem_eq(dec3.bits, &z, 4);
    ck_assert_int_eq(dec3.value_type, 1);
    float src4 = dNAN;
    bit96 dec4;
    ck_assert_int_eq(from_float_to_bit96(src4, &dec4), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec4), 0);
    ck_assert_int_eq(GetSign(dec4), 0);
    ck_assert_mem_eq(dec4.bits + 2, &x, 4);
    ck_assert_mem_eq(dec4.bits + 1, &y, 4);
    ck_assert_mem_eq(dec4.bits, &z, 4);
    ck_assert_int_eq(dec4.value_type, 3);
    float src5 = -0.25;
    bit96 dec5;
    ck_assert_int_eq(from_float_to_bit96(src5, &dec5), 0);
    x = 0, y = 0, z = 25;
    ck_assert_int_eq(GetRate(dec5), 2);
    ck_assert_int_eq(GetSign(dec5), 1);
    ck_assert_mem_eq(dec5.bits + 2, &x, 4);
    ck_assert_mem_eq(dec5.bits + 1, &y, 4);
    ck_assert_mem_eq(dec5.bits, &z, 4);
    ck_assert_int_eq(from_float_to_bit96(src5, NULL), 1);
    float src6 = 0.25e-28;
    bit96 dec6;
    ck_assert_int_eq(from_float_to_bit96(src6, &dec6), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec6), 0);
    ck_assert_int_eq(GetSign(dec6), 0);
    ck_assert_mem_eq(dec6.bits + 2, &x, 4);
    ck_assert_mem_eq(dec6.bits + 1, &y, 4);
    ck_assert_mem_eq(dec6.bits, &z, 4);
    ck_assert_int_eq(dec6.value_type, 0);
    float src7 = -7.9e30;
    bit96 dec7;
    ck_assert_int_eq(from_float_to_bit96(src7, &dec7), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec7), 0);
    ck_assert_int_eq(GetSign(dec7), 0);
    ck_assert_mem_eq(dec7.bits + 2, &x, 4);
    ck_assert_mem_eq(dec7.bits + 1, &y, 4);
    ck_assert_mem_eq(dec7.bits, &z, 4);
    ck_assert_int_eq(dec7.value_type, 2);
}
END_TEST

START_TEST(from_bit96_to_float_test) {
    bit96 dec1 = { { 3923312640, 58207660, 0, 0x80120000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 3923312640, 58207660, 0, 0x00120000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 1874293453, 3448970907, 3486583653, 0x007F0000 }, dNORMAL_VALUE };
    float dst1, dst2, dst5;
    ck_assert_int_eq(from_bit96_to_float(dec1, &dst1), 0);
    ck_assert_int_eq(from_bit96_to_float(dec2, &dst2), 0);
    ck_assert_int_eq(from_bit96_to_float(dec7, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_float(dec8, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_float(dec9, &dst1), 1);
    ck_assert_int_eq(from_bit96_to_float(dec10, &dst5), 0);
    ck_assert_int_eq(dst1, -0.25);
    ck_assert_int_eq(dst2, 0.25);
    ck_assert_int_eq(dst5, 0.0);
}
END_TEST

// MARK: - Comparison Operators

START_TEST(is_less_test) {
    bit96 dec1 = { { 212121, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 1, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 212121, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 1, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 212121, 0, 0, 0x000140000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 1, 0, 1, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec11 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x0050000 }, dNORMAL_VALUE };
    bit96 dec12 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    ck_assert_int_eq(is_less(dec1, dec2), 1);
    ck_assert_int_eq(is_less(dec3, dec4), 0);
    ck_assert_int_eq(is_less(dec1, dec3), 1);
    ck_assert_int_eq(is_less(dec4, dec2), 0);
    ck_assert_int_eq(is_less(dec1, dec5), 1);
    ck_assert_int_eq(is_less(dec1, dec6), 0);
    ck_assert_int_eq(is_less(dec7, dec10), 1);
    ck_assert_int_eq(is_less(dec10, dec8), 0);
    ck_assert_int_eq(is_less(dec9, dec1), 0);
    ck_assert_int_eq(is_less(dec11, dec10), 1);
    ck_assert_int_eq(is_less(dec12, dec11), 0);
    ck_assert_int_eq(is_less(dec11, dec11), 1);
}
END_TEST

START_TEST(is_greater_test) {
    bit96 dec1 = { { 212121, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 1, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 212121, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 1, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 212121, 0, 0, 0x000140000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 1, 0, 1, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec11 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x0050000 }, dNORMAL_VALUE };
    bit96 dec12 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    ck_assert_int_eq(is_greater(dec1, dec2), 0);
    ck_assert_int_eq(is_greater(dec3, dec4), 1);
    ck_assert_int_eq(is_greater(dec1, dec3), 0);
    ck_assert_int_eq(is_greater(dec4, dec2), 1);
    ck_assert_int_eq(is_greater(dec1, dec5), 0);
    ck_assert_int_eq(is_greater(dec1, dec6), 1);
    ck_assert_int_eq(is_greater(dec7, dec10), 1);
    ck_assert_int_eq(is_greater(dec8, dec10), 0);
    ck_assert_int_eq(is_greater(dec9, dec1), 1);
    ck_assert_int_eq(is_greater(dec11, dec10), 0);
    ck_assert_int_eq(is_greater(dec12, dec11), 1);
    ck_assert_int_eq(is_greater(dec11, dec11), 1);
}
END_TEST

START_TEST(is_less_or_equal_test) {
    bit96 dec1 = { { 212121, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 1, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 212121, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 1, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 212121, 0, 0, 0x000140000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 1, 0, 1, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec11 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x0050000 }, dNORMAL_VALUE };
    bit96 dec12 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    ck_assert_int_eq(is_less_or_equal(dec1, dec2), 1);
    ck_assert_int_eq(is_less_or_equal(dec3, dec4), 0);
    ck_assert_int_eq(is_less_or_equal(dec1, dec3), 1);
    ck_assert_int_eq(is_less_or_equal(dec4, dec2), 0);
    ck_assert_int_eq(is_less_or_equal(dec1, dec5), 1);
    ck_assert_int_eq(is_less_or_equal(dec1, dec6), 0);
    ck_assert_int_eq(is_less_or_equal(dec6, dec6), 0);
    ck_assert_int_eq(is_less_or_equal(dec7, dec10), 1);
    ck_assert_int_eq(is_less_or_equal(dec10, dec8), 0);
    ck_assert_int_eq(is_less_or_equal(dec9, dec1), 0);
    ck_assert_int_eq(is_less_or_equal(dec11, dec10), 1);
    ck_assert_int_eq(is_less_or_equal(dec12, dec11), 0);
    ck_assert_int_eq(is_less_or_equal(dec11, dec11), 0);
}
END_TEST

START_TEST(is_greater_or_equal_test) {
    bit96 dec1 = { { 212121, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 1, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 212121, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 1, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 212121, 0, 0, 0x000140000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 1, 0, 1, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec11 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x0050000 }, dNORMAL_VALUE };
    bit96 dec12 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    ck_assert_int_eq(is_greater_or_equal(dec1, dec2), 0);
    ck_assert_int_eq(is_greater_or_equal(dec3, dec4), 1);
    ck_assert_int_eq(is_greater_or_equal(dec1, dec3), 0);
    ck_assert_int_eq(is_greater_or_equal(dec4, dec2), 1);
    ck_assert_int_eq(is_greater_or_equal(dec1, dec5), 0);
    ck_assert_int_eq(is_greater_or_equal(dec1, dec6), 1);
    ck_assert_int_eq(is_greater_or_equal(dec7, dec10), 1);
    ck_assert_int_eq(is_greater_or_equal(dec8, dec10), 0);
    ck_assert_int_eq(is_greater_or_equal(dec9, dec1), 1);
    ck_assert_int_eq(is_greater_or_equal(dec6, dec6), 0);
    ck_assert_int_eq(is_greater_or_equal(dec11, dec10), 0);
    ck_assert_int_eq(is_greater_or_equal(dec12, dec11), 1);
    ck_assert_int_eq(is_greater_or_equal(dec11, dec11), 0);
}
END_TEST


START_TEST(is_equal_test) {
    bit96 dec1 = { { 212121, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 1, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 212121, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 1, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 0, 0, 0, 0x000140000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 0, 0, 0, 0x00040000 }, dNORMAL_VALUE };
    bit96 dec11 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x0050000 }, dNORMAL_VALUE };
    bit96 dec12 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    ck_assert_int_eq(is_equal(dec1, dec2), 1);
    ck_assert_int_eq(is_equal(dec1, dec1), 0);
    ck_assert_int_eq(is_equal(dec3, dec4), 1);
    ck_assert_int_eq(is_equal(dec4, dec4), 0);
    ck_assert_int_eq(is_equal(dec1, dec3), 1);
    ck_assert_int_eq(is_equal(dec10, dec5), 0);
    ck_assert_int_eq(is_equal(dec7, dec10), 1);
    ck_assert_int_eq(is_equal(dec10, dec8), 1);
    ck_assert_int_eq(is_equal(dec10, dec8), 1);
    ck_assert_int_eq(is_equal(dec10, dec10), 0);
    ck_assert_int_eq(is_equal(dec11, dec10), 1);
    ck_assert_int_eq(is_equal(dec12, dec11), 1);
    ck_assert_int_eq(is_equal(dec11, dec11), 0);
    ck_assert_int_eq(is_equal(dec9, dec10), 1);
}
END_TEST

START_TEST(is_not_equal_test) {
    bit96 dec1 = { { 212121, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 1, 0, 0, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 212121, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 1, 0, 0, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 0, 0, 0, 0x000140000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 0, 0, 0, 0x00040000 }, dNORMAL_VALUE };
    bit96 dec11 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x0050000 }, dNORMAL_VALUE };
    bit96 dec12 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    ck_assert_int_eq(is_not_equal(dec1, dec2), 0);
    ck_assert_int_eq(is_not_equal(dec1, dec1), 1);
    ck_assert_int_eq(is_not_equal(dec3, dec4), 0);
    ck_assert_int_eq(is_not_equal(dec4, dec4), 1);
    ck_assert_int_eq(is_not_equal(dec1, dec3), 0);
    ck_assert_int_eq(is_not_equal(dec10, dec5), 1);
    ck_assert_int_eq(is_not_equal(dec7, dec10), 0);
    ck_assert_int_eq(is_not_equal(dec10, dec8), 0);
    ck_assert_int_eq(is_not_equal(dec10, dec8), 0);
    ck_assert_int_eq(is_not_equal(dec10, dec10), 1);
    ck_assert_int_eq(is_not_equal(dec11, dec10), 0);
    ck_assert_int_eq(is_not_equal(dec12, dec11), 0);
    ck_assert_int_eq(is_not_equal(dec11, dec11), 1);
    ck_assert_int_eq(is_not_equal(dec9, dec10), 0);
}
END_TEST

// MARK: - Another functions
START_TEST(negate_test) {
    bit96 dec1 = { { 21, 1, 21, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 21, 1, 21, 0x0020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 0, 0, 0, 0 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0, 0, 0, 0 }, dINFINITY };
    bit96 dec5 = { { 0, 0, 0, 0 }, dNAN };
    bit96 dec6 = { { 0, 0, 0, 0 }, dNEGATIVE_INFINITY };
    bit96 dec7 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x0050000 }, dNORMAL_VALUE };
    ck_assert_int_eq(GetSign(Negate(dec1)), 0);
    ck_assert_int_eq(GetSign(Negate(dec2)), 1);
    ck_assert_int_eq(GetSign(Negate(dec3)), 1);
    ck_assert_int_eq(Negate(dec4).value_type, 2);
    ck_assert_int_eq(GetSign(Negate(dec5)), 0);
    ck_assert_int_eq(Negate(dec6).value_type, 1);
    ck_assert_int_eq(GetSign(Negate(dec7)), 1);
}
END_TEST

START_TEST(truncate_test) {
    bit96 dec1 = { { 21, 1, 21, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 0xffffffff, 0xffffffff , 0xffffffff, 0x00050000 }, dNORMAL_VALUE};
    bit96 dec3 = { { 21, 0, 0, 0x00180000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0, 0, 0, 0 }, dNORMAL_VALUE };
    bit96 dec5 = { { 1, 1, 1, 0 }, dINFINITY };
    bit96 dec6 = { { 1, 1, 1, 0 }, dNAN };
    bit96 dec7 = { { 1, 1, 1, 0 }, dNEGATIVE_INFINITY };

    int x = 0, y = 901943132, z = 730144440;

    dec1 = Truncate(dec1);
    ck_assert_int_eq(GetRate(dec1), 0);
    ck_assert_mem_eq(dec1.bits + 2, &x, 4);
    ck_assert_mem_eq(dec1.bits + 1, &y, 4);
    ck_assert_mem_eq(dec1.bits, &z, 4);

    dec2 = Truncate(dec2);
    x = 42949, y = 2890341191, z = 2216890319;
    ck_assert_int_eq(GetRate(dec2), 0);
    ck_assert_mem_eq(dec2.bits + 2, &x, 4);
    ck_assert_mem_eq(dec2.bits + 1, &y, 4);
    ck_assert_mem_eq(dec2.bits, &z, 4);

    dec3 = Truncate(dec3);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec3), 0);
    ck_assert_mem_eq(dec3.bits + 2, &x, 4);
    ck_assert_mem_eq(dec3.bits + 1, &y, 4);
    ck_assert_mem_eq(dec3.bits, &z, 4);

    dec4 = Truncate(dec4);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec4), 0);
    ck_assert_mem_eq(dec4.bits + 2, &x, 4);
    ck_assert_mem_eq(dec4.bits + 1, &y, 4);
    ck_assert_mem_eq(dec4.bits, &z, 4);

    dec5 = Truncate(dec5);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec5), 0);
    ck_assert_mem_eq(dec5.bits + 2, &x, 4);
    ck_assert_mem_eq(dec5.bits + 1, &y, 4);
    ck_assert_mem_eq(dec5.bits, &z, 4);

    dec6 = Truncate(dec6);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec6), 0);
    ck_assert_mem_eq(dec6.bits + 2, &x, 4);
    ck_assert_mem_eq(dec6.bits + 1, &y, 4);
    ck_assert_mem_eq(dec6.bits, &z, 4);

    dec7 = Truncate(dec7);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec7), 0);
    ck_assert_mem_eq(dec7.bits + 2, &x, 4);
    ck_assert_mem_eq(dec7.bits + 1, &y, 4);
    ck_assert_mem_eq(dec7.bits, &z, 4);
}
END_TEST

START_TEST(round_test) {
    bit96 dec1 = { { 21, 1, 21, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 0xffffffff, 0xffffffff , 0xffffffff, 0x00050000 }, dNORMAL_VALUE};
    bit96 dec3 = { { 21, 0, 0, 0x00180000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0, 0, 0, 0 }, dNORMAL_VALUE };
    bit96 dec5 = { { 1, 1, 1, 0 }, dINFINITY };
    bit96 dec6 = { { 1, 1, 1, 0 }, dNAN };
    bit96 dec7 = { { 1, 1, 1, 0 }, dNEGATIVE_INFINITY };


    int x = 0, y = 901943132, z = 730144441;
    dec1 = Round(dec1);
    ck_assert_int_eq(GetRate(dec1), 0);
    ck_assert_mem_eq(dec1.bits + 2, &x, 4);
    ck_assert_mem_eq(dec1.bits + 1, &y, 4);
    ck_assert_mem_eq(dec1.bits, &z, 4);

    dec2 = Round(dec2);
    x = 42949, y = 2890341191, z = 2216890320;
    ck_assert_int_eq(GetRate(dec2), 0);
    ck_assert_mem_eq(dec2.bits + 2, &x, 4);
    ck_assert_mem_eq(dec2.bits + 1, &y, 4);
    ck_assert_mem_eq(dec2.bits, &z, 4);

    dec3 = Round(dec3);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec3), 0);
    ck_assert_mem_eq(dec3.bits + 2, &x, 4);
    ck_assert_mem_eq(dec3.bits + 1, &y, 4);
    ck_assert_mem_eq(dec3.bits, &z, 4);

    dec4 = Round(dec4);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec4), 0);
    ck_assert_mem_eq(dec4.bits + 2, &x, 4);
    ck_assert_mem_eq(dec4.bits + 1, &y, 4);
    ck_assert_mem_eq(dec4.bits, &z, 4);

    dec5 = Round(dec5);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec5), 0);
    ck_assert_mem_eq(dec5.bits + 2, &x, 4);
    ck_assert_mem_eq(dec5.bits + 1, &y, 4);
    ck_assert_mem_eq(dec5.bits, &z, 4);

    dec6 = Round(dec6);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec6), 0);
    ck_assert_mem_eq(dec6.bits + 2, &x, 4);
    ck_assert_mem_eq(dec6.bits + 1, &y, 4);
    ck_assert_mem_eq(dec6.bits, &z, 4);

    dec7 = Round(dec7);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec7), 0);
    ck_assert_mem_eq(dec7.bits + 2, &x, 4);
    ck_assert_mem_eq(dec7.bits + 1, &y, 4);
    ck_assert_mem_eq(dec7.bits, &z, 4);
}
END_TEST

START_TEST(floor_test) {
    bit96 dec1 = { { 21, 1, 21, 0x80020000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 0xffffffff, 0xffffffff , 0xffffffff, 0x00050000 }, dNORMAL_VALUE};
    bit96 dec3 = { { 21, 0, 0, 0x00180000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0, 0, 0, 0 }, dNORMAL_VALUE };
    bit96 dec5 = { { 1, 1, 1, 0 }, dINFINITY };
    bit96 dec6 = { { 1, 1, 1, 0 }, dNAN };
    bit96 dec7 = { { 1, 1, 1, 0 }, dNEGATIVE_INFINITY };
    bit96 dec8 = { { 21, 0, 0, 0x80180000 }, dNORMAL_VALUE };


    int x = 0, y = 901943132, z = 730144441;
    dec1 = Floor(dec1);
    ck_assert_int_eq(GetRate(dec1), 0);
    ck_assert_mem_eq(dec1.bits + 2, &x, 4);
    ck_assert_mem_eq(dec1.bits + 1, &y, 4);
    ck_assert_mem_eq(dec1.bits, &z, 4);

    dec2 = Floor(dec2);
    x = 42949, y = 2890341191, z = 2216890319;
    ck_assert_int_eq(GetRate(dec2), 0);
    ck_assert_mem_eq(dec2.bits + 2, &x, 4);
    ck_assert_mem_eq(dec2.bits + 1, &y, 4);
    ck_assert_mem_eq(dec2.bits, &z, 4);

    dec3 = Floor(dec3);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec3), 0);
    ck_assert_mem_eq(dec3.bits + 2, &x, 4);
    ck_assert_mem_eq(dec3.bits + 1, &y, 4);
    ck_assert_mem_eq(dec3.bits, &z, 4);

    dec4 = Floor(dec4);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec4), 0);
    ck_assert_mem_eq(dec4.bits + 2, &x, 4);
    ck_assert_mem_eq(dec4.bits + 1, &y, 4);
    ck_assert_mem_eq(dec4.bits, &z, 4);

    dec5 = Floor(dec5);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec5), 0);
    ck_assert_mem_eq(dec5.bits + 2, &x, 4);
    ck_assert_mem_eq(dec5.bits + 1, &y, 4);
    ck_assert_mem_eq(dec5.bits, &z, 4);

    dec6 = Floor(dec6);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec6), 0);
    ck_assert_mem_eq(dec6.bits + 2, &x, 4);
    ck_assert_mem_eq(dec6.bits + 1, &y, 4);
    ck_assert_mem_eq(dec6.bits, &z, 4);

    dec7 = Floor(dec7);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec7), 0);
    ck_assert_mem_eq(dec7.bits + 2, &x, 4);
    ck_assert_mem_eq(dec7.bits + 1, &y, 4);
    ck_assert_mem_eq(dec7.bits, &z, 4);

    dec3 = Floor(dec8);
    x = 0, y = 0, z = 1;
    ck_assert_int_eq(GetRate(dec3), 0);
    ck_assert_mem_eq(dec3.bits + 2, &x, 4);
    ck_assert_mem_eq(dec3.bits + 1, &y, 4);
    ck_assert_mem_eq(dec3.bits, &z, 4);
}
END_TEST

START_TEST(add_test) {
    bit96 res;
    bit96 dec1 = { { 21, 0xffffffff, 1, 0x00080000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 21, 1, 0, 0x00020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 0xffffff3C, 0xffffffff, 0xffffffff, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0xffffff3C, 0, 0, 0x0090000 }, dNORMAL_VALUE };
    bit96 dec8 = { { 21, 1, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec11 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };


    res = add(dec1, dec2);
    int x = 2, y = 999999, z = 21000021;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = add(dec2, dec2);
    x = 0, y = 2, z = 42;
    ck_assert_int_eq(GetRate(res), 2);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = add(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = add(res, dec4);                                       // MAX VALUE
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = add(dec1, dec4);                                      // = dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = add(dec5, dec4);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = add(dec6, dec7);
    x = 4294967295, y = 4294967295, z = 4294967104;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = add(dec8, dec5);                                      // = dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = add(dec9, dec9);                                      // dNAN + dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = add(dec9, dec2);                                      // dNAN + dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = add(dec10, dec11);                                      // dINFINITY + dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = add(dec10, dec10);                                      //  dINFINITY + dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = add(dec11, dec11);                 // dNEGATIVE_INFINITY + dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = add(dec10, dec2);                                      // dINFINITY + dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = add(dec11, dec2);                                      // dNEGATIVE_INFINITY + dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);
}
END_TEST

START_TEST(sub_test) {
    bit96 res;
    bit96 dec1 = { { 21, 0xffffffff, 1, 0x00080000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 21, 1, 0, 0x00020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec5 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 0xffffff3C, 0xffffffff, 0xffffffff, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0xffffff3C, 0, 0, 0x80090000 }, dNORMAL_VALUE };
    bit96 dec8 = { { 21, 1, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec11 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };

    res = sub(dec1, dec2);
    int x = 1, y = 4293967294, z = 4273967317;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = sub(dec2, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = sub(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = sub(res, dec4);                                       // MAX VALUE
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = sub(dec1, dec5);                                      // = dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = sub(dec5, dec4);                                      // = dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = sub(dec6, dec7);
    x = 4294967295, y = 4294967295, z = 4294967104;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = sub(dec8, dec4);                                      // = dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = sub(dec9, dec9);                                      // dNAN - dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = sub(dec9, dec2);                                      // dNAN - dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = sub(dec10, dec11);                                      // dINFINITY - dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = sub(dec10, dec10);                                      //  dINFINITY - dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = sub(dec11, dec11);         //  dNEGATIVE_INFINITY - dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = sub(dec10, dec2);                                      // dINFINITY - dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = sub(dec11, dec2);                                      // dNEGATIVE_INFINITY - dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);
}
END_TEST

START_TEST(div_test) {
    bit96 res;
    bit96 dec1 = { { 21, 0xffffffff, 1, 0x00080000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 21, 1, 0, 0x00020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 1, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec8 = { { 21, 1, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec11 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec12 = { { 1000, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec13 = { { 33, 0, 0, 0x00000000 }, dNORMAL_VALUE };

    res = div(dec1, dec2);
    long int x = 0, y = 1999999989, z = 4244640471;
    ck_assert_int_eq(GetRate(res), 15);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec2, dec2);
    x = 0, y = 2328306436, z = 2313682944;
    ck_assert_int_eq(GetRate(res), 19);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec3, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec3, dec3);                                      // 0/0
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = div(dec2, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = div(dec6, dec4);                                       // 1/MAX VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 28);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec4, dec6);                                       // MAX VALUE/1
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec12, dec13);  //  ??
    x = 16427305, y = 2764755334, z = 3522198559;
    ck_assert_int_eq(GetRate(res), 25);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec13, dec12);
    x = 1788933, y = 2510842529, z = 3238002688;
    ck_assert_int_eq(GetRate(res), 27);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec8, dec8);
    x = 0, y = 0, z = 1;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec8, dec6);
    x = 4294967295, y = 1, z = 21;
    ck_assert_int_eq(GetRate(res), 5);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec6, dec8);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 23);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = div(dec9, dec6);                                      // dNAN/NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);
    res = div(dec9, dec9);                                      // dNAN/dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);
    res = div(dec9, dec10);                                      // dNAN/INF
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);
    res = div(dec10, dec9);                                      // INF/dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = div(dec1, dec10);                                      // = NORM/dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = div(dec3, dec10);                                      // = 0/dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = div(dec10, dec3);                                      // = dINFINITY/NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);
    res = div(dec10, dec10);                                      // = dINFINITY/dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = div(dec1, dec11);                                      // = NORM/dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = div(dec3, dec11);                                      // = 0/dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = div(dec11, dec1);                                      // = dNEGATIVE_INFINITY/0
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);
}
END_TEST

START_TEST(mul_test) {
    bit96 res;
    bit96 dec1 = { { 21, 0xffffffff, 1, 0x00080000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 21, 1, 0, 0x00020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 1, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec8 = { { 21, 1, 0xffffffff, 0x80050000 }, dNORMAL_VALUE };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec11 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec12 = { { 1000, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec13 = { { 33, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec14 = { { 1000, 0, 0, 0x80000000 }, dNORMAL_VALUE };

    res = mul(dec1, dec2);
    long int x = 858993463, y = 1288490188, z = 3435973880;
    ck_assert_int_eq(GetRate(res), 9);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    res = mul(dec2, dec2);
    x = 1, y = 42, z = 441;
    ck_assert_int_eq(GetRate(res), 4);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec3, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec2, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec6, dec4);                                       // 1*MAX VALUE
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec4, dec4);                                       // MAX VALUE*MAX VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = mul(dec12, dec13);
    x = 0, y = 0, z = 33000;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec2, dec14);
    x = 0, y = 1000, z = 21000;
    ck_assert_int_eq(GetRate(res), 2);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec8, dec6);
    x = 4294967295, y = 1, z = 21;
    ck_assert_int_eq(GetRate(res), 5);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec6, dec8);
    x = 4294967295, y = 1, z = 21;
    ck_assert_int_eq(GetRate(res), 5);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mul(dec9, dec6);                                      // dNAN*NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mul(dec9, dec9);                                      // dNAN*dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mul(dec9, dec10);                                      // dNAN*INF
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mul(dec10, dec9);                                      // INF*dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mul(dec1, dec10);                                      // = NORM*dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = mul(dec3, dec10);                                      // = 0*dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mul(dec10, dec1);                                      // = dINFINITY*NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = mul(dec10, dec10);                                      // = dINFINITY*dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = mul(dec1, dec11);                                      // = NORM*dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = mul(dec3, dec11);                                      // = 0*dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);
}
END_TEST

START_TEST(mod_test) {
    bit96 res;
    bit96 dec1 = { { 21, 0xffffffff, 1, 0x00080000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 21, 1, 0, 0x00020000 }, dNORMAL_VALUE };
    bit96 dec3 = { { 0, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec4 = { { 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec6 = { { 1, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec8 = { { 21, 1, 0xffffffff, 0x80000000 }, dNORMAL_VALUE };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec10 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec11 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec12 = { { 1000, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec13 = { { 33, 0, 0, 0x00000000 }, dNORMAL_VALUE };
    bit96 dec14 = { { 1000, 0, 0, 0x80000000 }, dNORMAL_VALUE };

    res = mod(dec1, dec2);
    long int x = 0, y = 934549, z = 19626453;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec2, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec3, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec2, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec6, dec4);                                       // 1%MAX VALUE
    x = 0, y = 0, z = 1;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec4, dec4);                                       // MAX VALUE%MAX VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = mod(dec12, dec13);
    x = 0, y = 0, z = 10;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec13, dec12);
    x = 0, y = 0, z = 33;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec2, dec14);
    x = 0, y = 0, z = 67317;
    ck_assert_int_eq(GetRate(res), 2);
    ck_assert_int_eq(GetSign(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec14, dec2);
    x = 0, y = 0, z = 1000;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec8, dec6);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec6, dec8);
    x = 0, y = 0, z = 1;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = mod(dec9, dec6);                                      // dNAN%NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec9, dec9);                                      // dNAN%dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec9, dec10);                                      // dNAN%INF
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec10, dec9);                                      // INF%dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec1, dec10);                                      // = NORM%dINFINITY
    x = 1, y = 4294967295, z = 21;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = mod(dec3, dec10);                                      // = 0%dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = mod(dec10, dec3);                                      // = dINFINITY%0
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec10, dec1);                                      // = dINFINITY%NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = mod(dec10, dec10);                                      // = dINFINITY%dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = mod(dec1, dec11);                                      // = NORM%dNEGATIVE_INFINITY
    x = 1, y = 4294967295, z = 21;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = mod(dec3, dec11);                                      // = 0%dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
}
END_TEST

int main() {
    Suite *s1 = suite_create("bit96");
    TCase *is_lessCase = tcase_create("is_less test");
    TCase *is_greaterCase = tcase_create("is_greater test");
    TCase *is_less_or_equalCase = tcase_create("is_less_or_equal test");
    TCase *is_greater_or_equalCase = tcase_create("is_greater_or_equal test");
    TCase *is_equalCase = tcase_create("is_equal test");
    TCase *is_not_equalCase = tcase_create("is_not_equal test");
    TCase *negateCase = tcase_create("negate test");
    TCase *truncateCase = tcase_create("truncate test");
    TCase *roundCase = tcase_create("round test");
    TCase *floorCase = tcase_create("floor test");
    TCase *addCase = tcase_create("add test");
    TCase *subCase = tcase_create("sub test");
    TCase *divCase = tcase_create("div test");
    TCase *mulCase = tcase_create("mul test");
    TCase *modCase = tcase_create("mod test");
    TCase *from_int_to_bit96_Case = tcase_create("from_int_to_bit96_test");
    TCase *from_bit96_to_int_Case = tcase_create("from_bit96_to_int_test");
    TCase *from_float_to_bit96_Case = tcase_create("from_float_to_bit96_test");
    TCase *from_bit96_to_float_Case = tcase_create("from_bit96_to_float_test");
    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, from_int_to_bit96_Case);
    tcase_add_test(from_int_to_bit96_Case, from_int_to_bit96_test);
    suite_add_tcase(s1, from_bit96_to_int_Case);
    tcase_add_test(from_bit96_to_int_Case, from_bit96_to_int_test);
    suite_add_tcase(s1, from_float_to_bit96_Case);
    tcase_add_test(from_float_to_bit96_Case, from_float_to_bit96_test);
    suite_add_tcase(s1, from_bit96_to_float_Case);
    tcase_add_test(from_bit96_to_float_Case, from_bit96_to_float_test);
    suite_add_tcase(s1, is_lessCase);
    tcase_add_test(is_lessCase, is_less_test);
    suite_add_tcase(s1, is_greaterCase);
    tcase_add_test(is_greaterCase, is_greater_test);
    suite_add_tcase(s1, is_less_or_equalCase);
    tcase_add_test(is_less_or_equalCase, is_less_or_equal_test);
    suite_add_tcase(s1, is_greater_or_equalCase);
    tcase_add_test(is_greater_or_equalCase, is_greater_or_equal_test);
    suite_add_tcase(s1, is_equalCase);
    tcase_add_test(is_equalCase, is_equal_test);
    suite_add_tcase(s1, is_not_equalCase);
    tcase_add_test(is_not_equalCase, is_not_equal_test);

    suite_add_tcase(s1, negateCase);
    tcase_add_test(negateCase, negate_test);
    suite_add_tcase(s1, truncateCase);
    tcase_add_test(truncateCase, truncate_test);
    suite_add_tcase(s1, roundCase);
    tcase_add_test(roundCase, round_test);
    suite_add_tcase(s1, floorCase);
    tcase_add_test(floorCase, floor_test);

    suite_add_tcase(s1, addCase);
    tcase_add_test(addCase, add_test);
    suite_add_tcase(s1, subCase);
    tcase_add_test(subCase, sub_test);
    suite_add_tcase(s1, divCase);
    tcase_add_test(divCase, div_test);
    suite_add_tcase(s1, mulCase);
    tcase_add_test(mulCase, mul_test);
    suite_add_tcase(s1, modCase);
    tcase_add_test(modCase, mod_test);

    srunner_run_all(sr, CK_VERBOSE);
    srunner_free(sr);
    return 0;
}

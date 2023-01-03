#include "bit96.h"
#include <check.h>
#include <stdio.h>

// MARK: - Convertors

START_TEST(IntToBit96_test) {
    int src1 = 2000;
    bit96 dec1;
    IntToBit96(src1, &dec1);
    int x = 0, y = 0, z = 2000;
    ck_assert_int_eq(GetRate(dec1), 0);
    ck_assert_int_eq(GetSign(dec1), 0);
    ck_assert_mem_eq(dec1.bits + 2, &x, 4);
    ck_assert_mem_eq(dec1.bits + 1, &y, 4);
    ck_assert_mem_eq(dec1.bits, &z, 4);
    int src2 = -2000;
    bit96 dec2;
    IntToBit96(src2, &dec2);
    x = 0, y = 0, z = 2000;
    ck_assert_int_eq(GetRate(dec2), 0);
    ck_assert_int_eq(GetSign(dec2), 1);
    ck_assert_mem_eq(dec2.bits + 2, &x, 4);
    ck_assert_mem_eq(dec2.bits + 1, &y, 4);
    ck_assert_mem_eq(dec2.bits, &z, 4);
}
END_TEST

START_TEST(Bit96ToInt_test) {
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
    ck_assert_int_eq(Bit96ToInt(dec1, &dst1), 0);
    ck_assert_int_eq(Bit96ToInt(dec2, &dst2), 0);
    ck_assert_int_eq(Bit96ToInt(dec3, &dst3), 0);
    ck_assert_int_eq(Bit96ToInt(dec4, &dst4), 0);
    ck_assert_int_eq(Bit96ToInt(dec5, &dst1), 1);
    ck_assert_int_eq(Bit96ToInt(dec6, &dst1), 1);
    ck_assert_int_eq(Bit96ToInt(dec7, &dst1), 1);
    ck_assert_int_eq(Bit96ToInt(dec8, &dst1), 1);
    ck_assert_int_eq(Bit96ToInt(dec9, &dst1), 1);
    ck_assert_int_eq(Bit96ToInt(dec10, &dst5), 0);
    ck_assert_int_eq(Bit96ToInt(dec11, &dst1), 1);
    ck_assert_int_eq(dst1, 2000);
    ck_assert_int_eq(dst2, 20);
    ck_assert_int_eq(dst3, -2000);
    ck_assert_int_eq(dst4, -20);
    ck_assert_int_eq(dst5, 0);
}
END_TEST

START_TEST(FloatToBit96_test) {
    float src1 = 0.25e26;
    bit96 dec1;
    ck_assert_int_eq(FloatToBit96(src1, &dec1), 0);
    int x = 1355252771, y = 265257180, z = 863116627;
    ck_assert_int_eq(GetRate(dec1), 3);
    ck_assert_int_eq(GetSign(dec1), 0);
    ck_assert_mem_eq(dec1.bits + 2, &x, 4);
    ck_assert_mem_eq(dec1.bits + 1, &y, 4);
    ck_assert_mem_eq(dec1.bits, &z, 4);
    float src2 = 7.9e30;
    bit96 dec2;
    ck_assert_int_eq(FloatToBit96(src2, &dec2), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec2), 0);
    ck_assert_int_eq(GetSign(dec2), 0);
    ck_assert_mem_eq(dec2.bits + 2, &x, 4);
    ck_assert_mem_eq(dec2.bits + 1, &y, 4);
    ck_assert_mem_eq(dec2.bits, &z, 4);
    ck_assert_int_eq(dec2.value_type, 1);
    float src3 = dINFINITY;
    bit96 dec3;
    ck_assert_int_eq(FloatToBit96(src3, &dec3), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec3), 0);
    ck_assert_int_eq(GetSign(dec3), 0);
    ck_assert_mem_eq(dec3.bits + 2, &x, 4);
    ck_assert_mem_eq(dec3.bits + 1, &y, 4);
    ck_assert_mem_eq(dec3.bits, &z, 4);
    ck_assert_int_eq(dec3.value_type, 1);
    float src4 = dNAN;
    bit96 dec4;
    ck_assert_int_eq(FloatToBit96(src4, &dec4), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec4), 0);
    ck_assert_int_eq(GetSign(dec4), 0);
    ck_assert_mem_eq(dec4.bits + 2, &x, 4);
    ck_assert_mem_eq(dec4.bits + 1, &y, 4);
    ck_assert_mem_eq(dec4.bits, &z, 4);
    ck_assert_int_eq(dec4.value_type, 3);
    float src5 = -0.25;
    bit96 dec5;
    ck_assert_int_eq(FloatToBit96(src5, &dec5), 0);
    x = 0, y = 0, z = 25;
    ck_assert_int_eq(GetRate(dec5), 2);
    ck_assert_int_eq(GetSign(dec5), 1);
    ck_assert_mem_eq(dec5.bits + 2, &x, 4);
    ck_assert_mem_eq(dec5.bits + 1, &y, 4);
    ck_assert_mem_eq(dec5.bits, &z, 4);
    ck_assert_int_eq(FloatToBit96(src5, NULL), 1);
    float src6 = 0.25e-28;
    bit96 dec6;
    ck_assert_int_eq(FloatToBit96(src6, &dec6), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec6), 0);
    ck_assert_int_eq(GetSign(dec6), 0);
    ck_assert_mem_eq(dec6.bits + 2, &x, 4);
    ck_assert_mem_eq(dec6.bits + 1, &y, 4);
    ck_assert_mem_eq(dec6.bits, &z, 4);
    ck_assert_int_eq(dec6.value_type, 0);
    float src7 = -7.9e30;
    bit96 dec7;
    ck_assert_int_eq(FloatToBit96(src7, &dec7), 1);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(dec7), 0);
    ck_assert_int_eq(GetSign(dec7), 0);
    ck_assert_mem_eq(dec7.bits + 2, &x, 4);
    ck_assert_mem_eq(dec7.bits + 1, &y, 4);
    ck_assert_mem_eq(dec7.bits, &z, 4);
    ck_assert_int_eq(dec7.value_type, 2);
}
END_TEST

START_TEST(Bit96ToFloat_test) {
    bit96 dec1 = { { 3923312640, 58207660, 0, 0x80120000 }, dNORMAL_VALUE };
    bit96 dec2 = { { 3923312640, 58207660, 0, 0x00120000 }, dNORMAL_VALUE };
    bit96 dec7 = { { 0, 0, 0, 0x00000000 }, dNAN };
    bit96 dec8 = { { 0, 0, 0, 0x00000000 }, dINFINITY };
    bit96 dec9 = { { 0, 0, 0, 0x00000000 }, dNEGATIVE_INFINITY };
    bit96 dec10 = { { 1874293453, 3448970907, 3486583653, 0x007F0000 }, dNORMAL_VALUE };
    float dst1, dst2, dst5;
    ck_assert_int_eq(Bit96ToFloat(dec1, &dst1), 0);
    ck_assert_int_eq(Bit96ToFloat(dec2, &dst2), 0);
    ck_assert_int_eq(Bit96ToFloat(dec7, &dst1), 1);
    ck_assert_int_eq(Bit96ToFloat(dec8, &dst1), 1);
    ck_assert_int_eq(Bit96ToFloat(dec9, &dst1), 1);
    ck_assert_int_eq(Bit96ToFloat(dec10, &dst5), 0);
    ck_assert_int_eq(dst1, -0.25);
    ck_assert_int_eq(dst2, 0.25);
    ck_assert_int_eq(dst5, 0.0);
}
END_TEST

// MARK: - Comparison Operators

START_TEST(IsLess_test) {
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
    ck_assert_int_eq(IsLess(dec1, dec2), 1);
    ck_assert_int_eq(IsLess(dec3, dec4), 0);
    ck_assert_int_eq(IsLess(dec1, dec3), 1);
    ck_assert_int_eq(IsLess(dec4, dec2), 0);
    ck_assert_int_eq(IsLess(dec1, dec5), 1);
    ck_assert_int_eq(IsLess(dec1, dec6), 0);
    ck_assert_int_eq(IsLess(dec7, dec10), 1);
    ck_assert_int_eq(IsLess(dec10, dec8), 0);
    ck_assert_int_eq(IsLess(dec9, dec1), 0);
    ck_assert_int_eq(IsLess(dec11, dec10), 1);
    ck_assert_int_eq(IsLess(dec12, dec11), 0);
    ck_assert_int_eq(IsLess(dec11, dec11), 1);
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
    ck_assert_int_eq(IsGreater(dec1, dec2), 0);
    ck_assert_int_eq(IsGreater(dec3, dec4), 1);
    ck_assert_int_eq(IsGreater(dec1, dec3), 0);
    ck_assert_int_eq(IsGreater(dec4, dec2), 1);
    ck_assert_int_eq(IsGreater(dec1, dec5), 0);
    ck_assert_int_eq(IsGreater(dec1, dec6), 1);
    ck_assert_int_eq(IsGreater(dec7, dec10), 1);
    ck_assert_int_eq(IsGreater(dec8, dec10), 0);
    ck_assert_int_eq(IsGreater(dec9, dec1), 1);
    ck_assert_int_eq(IsGreater(dec11, dec10), 0);
    ck_assert_int_eq(IsGreater(dec12, dec11), 1);
    ck_assert_int_eq(IsGreater(dec11, dec11), 1);
}
END_TEST

START_TEST(IsLessOrEqual_test) {
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
    ck_assert_int_eq(IsLessOrEqual(dec1, dec2), 1);
    ck_assert_int_eq(IsLessOrEqual(dec3, dec4), 0);
    ck_assert_int_eq(IsLessOrEqual(dec1, dec3), 1);
    ck_assert_int_eq(IsLessOrEqual(dec4, dec2), 0);
    ck_assert_int_eq(IsLessOrEqual(dec1, dec5), 1);
    ck_assert_int_eq(IsLessOrEqual(dec1, dec6), 0);
    ck_assert_int_eq(IsLessOrEqual(dec6, dec6), 0);
    ck_assert_int_eq(IsLessOrEqual(dec7, dec10), 1);
    ck_assert_int_eq(IsLessOrEqual(dec10, dec8), 0);
    ck_assert_int_eq(IsLessOrEqual(dec9, dec1), 0);
    ck_assert_int_eq(IsLessOrEqual(dec11, dec10), 1);
    ck_assert_int_eq(IsLessOrEqual(dec12, dec11), 0);
    ck_assert_int_eq(IsLessOrEqual(dec11, dec11), 0);
}
END_TEST

START_TEST(IsGreaterOrEqual_test) {
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
    ck_assert_int_eq(IsGreaterOrEqual(dec1, dec2), 0);
    ck_assert_int_eq(IsGreaterOrEqual(dec3, dec4), 1);
    ck_assert_int_eq(IsGreaterOrEqual(dec1, dec3), 0);
    ck_assert_int_eq(IsGreaterOrEqual(dec4, dec2), 1);
    ck_assert_int_eq(IsGreaterOrEqual(dec1, dec5), 0);
    ck_assert_int_eq(IsGreaterOrEqual(dec1, dec6), 1);
    ck_assert_int_eq(IsGreaterOrEqual(dec7, dec10), 1);
    ck_assert_int_eq(IsGreaterOrEqual(dec8, dec10), 0);
    ck_assert_int_eq(IsGreaterOrEqual(dec9, dec1), 1);
    ck_assert_int_eq(IsGreaterOrEqual(dec6, dec6), 0);
    ck_assert_int_eq(IsGreaterOrEqual(dec11, dec10), 0);
    ck_assert_int_eq(IsGreaterOrEqual(dec12, dec11), 1);
    ck_assert_int_eq(IsGreaterOrEqual(dec11, dec11), 0);
}
END_TEST


START_TEST(IsEqual_test) {
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
    ck_assert_int_eq(IsEqual(dec1, dec2), 1);
    ck_assert_int_eq(IsEqual(dec1, dec1), 0);
    ck_assert_int_eq(IsEqual(dec3, dec4), 1);
    ck_assert_int_eq(IsEqual(dec4, dec4), 0);
    ck_assert_int_eq(IsEqual(dec1, dec3), 1);
    ck_assert_int_eq(IsEqual(dec10, dec5), 0);
    ck_assert_int_eq(IsEqual(dec7, dec10), 1);
    ck_assert_int_eq(IsEqual(dec10, dec8), 1);
    ck_assert_int_eq(IsEqual(dec10, dec8), 1);
    ck_assert_int_eq(IsEqual(dec10, dec10), 0);
    ck_assert_int_eq(IsEqual(dec11, dec10), 1);
    ck_assert_int_eq(IsEqual(dec12, dec11), 1);
    ck_assert_int_eq(IsEqual(dec11, dec11), 0);
    ck_assert_int_eq(IsEqual(dec9, dec10), 1);
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
    ck_assert_int_eq(IsNotEqual(dec1, dec2), 0);
    ck_assert_int_eq(IsNotEqual(dec1, dec1), 1);
    ck_assert_int_eq(IsNotEqual(dec3, dec4), 0);
    ck_assert_int_eq(IsNotEqual(dec4, dec4), 1);
    ck_assert_int_eq(IsNotEqual(dec1, dec3), 0);
    ck_assert_int_eq(IsNotEqual(dec10, dec5), 1);
    ck_assert_int_eq(IsNotEqual(dec7, dec10), 0);
    ck_assert_int_eq(IsNotEqual(dec10, dec8), 0);
    ck_assert_int_eq(IsNotEqual(dec10, dec8), 0);
    ck_assert_int_eq(IsNotEqual(dec10, dec10), 1);
    ck_assert_int_eq(IsNotEqual(dec11, dec10), 0);
    ck_assert_int_eq(IsNotEqual(dec12, dec11), 0);
    ck_assert_int_eq(IsNotEqual(dec11, dec11), 1);
    ck_assert_int_eq(IsNotEqual(dec9, dec10), 0);
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


    res = Add(dec1, dec2);
    int x = 2, y = 999999, z = 21000021;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Add(dec2, dec2);
    x = 0, y = 2, z = 42;
    ck_assert_int_eq(GetRate(res), 2);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Add(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Add(res, dec4);                                       // MAX VALUE
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Add(dec1, dec4);                                      // = dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Add(dec5, dec4);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Add(dec6, dec7);
    x = 4294967295, y = 4294967295, z = 4294967104;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Add(dec8, dec5);                                      // = dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = Add(dec9, dec9);                                      // dNAN + dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Add(dec9, dec2);                                      // dNAN + dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Add(dec10, dec11);                                      // dINFINITY + dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Add(dec10, dec10);                                      //  dINFINITY + dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Add(dec11, dec11);                 // dNEGATIVE_INFINITY + dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = Add(dec10, dec2);                                      // dINFINITY + dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Add(dec11, dec2);                                      // dNEGATIVE_INFINITY + dNORMAL_VALUE
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

    res = Sub(dec1, dec2);
    int x = 1, y = 4293967294, z = 4273967317;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Sub(dec2, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Sub(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Sub(res, dec4);                                       // MAX VALUE
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Sub(dec1, dec5);                                      // = dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Sub(dec5, dec4);                                      // = dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = Sub(dec6, dec7);
    x = 4294967295, y = 4294967295, z = 4294967104;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Sub(dec8, dec4);                                      // = dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = Sub(dec9, dec9);                                      // dNAN - dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Sub(dec9, dec2);                                      // dNAN - dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Sub(dec10, dec11);                                      // dINFINITY - dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Sub(dec10, dec10);                                      //  dINFINITY - dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Sub(dec11, dec11);         //  dNEGATIVE_INFINITY - dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Sub(dec10, dec2);                                      // dINFINITY - dNORMAL_VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Sub(dec11, dec2);                                      // dNEGATIVE_INFINITY - dNORMAL_VALUE
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

    res = Div(dec1, dec2);
    long int x = 0, y = 1999999989, z = 4244640471;
    ck_assert_int_eq(GetRate(res), 15);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec2, dec2);
    x = 0, y = 2328306436, z = 2313682944;
    ck_assert_int_eq(GetRate(res), 19);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec3, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec3, dec3);                                      // 0/0
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Div(dec2, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Div(dec6, dec4);                                       // 1/MAX VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 28);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec4, dec6);                                       // MAX VALUE/1
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec12, dec13);  //  ??
    x = 16427305, y = 2764755334, z = 3522198559;
    ck_assert_int_eq(GetRate(res), 25);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec13, dec12);
    x = 1788933, y = 2510842529, z = 3238002688;
    ck_assert_int_eq(GetRate(res), 27);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec8, dec8);
    x = 0, y = 0, z = 1;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec8, dec6);
    x = 4294967295, y = 1, z = 21;
    ck_assert_int_eq(GetRate(res), 5);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec6, dec8);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 23);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Div(dec9, dec6);                                      // dNAN/NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);
    res = Div(dec9, dec9);                                      // dNAN/dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);
    res = Div(dec9, dec10);                                      // dNAN/INF
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);
    res = Div(dec10, dec9);                                      // INF/dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Div(dec1, dec10);                                      // = NORM/dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = Div(dec3, dec10);                                      // = 0/dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = Div(dec10, dec3);                                      // = dINFINITY/NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);
    res = Div(dec10, dec10);                                      // = dINFINITY/dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Div(dec1, dec11);                                      // = NORM/dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = Div(dec3, dec11);                                      // = 0/dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);
    res = Div(dec11, dec1);                                      // = dNEGATIVE_INFINITY/0
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

    res = Mul(dec1, dec2);
    long int x = 858993463, y = 1288490188, z = 3435973880;
    ck_assert_int_eq(GetRate(res), 9);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    res = Mul(dec2, dec2);
    x = 1, y = 42, z = 441;
    ck_assert_int_eq(GetRate(res), 4);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec3, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec2, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec6, dec4);                                       // 1*MAX VALUE
    x = 4294967295, y = 4294967295, z = 4294967295;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec4, dec4);                                       // MAX VALUE*MAX VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Mul(dec12, dec13);
    x = 0, y = 0, z = 33000;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec2, dec14);
    x = 0, y = 1000, z = 21000;
    ck_assert_int_eq(GetRate(res), 2);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec8, dec6);
    x = 4294967295, y = 1, z = 21;
    ck_assert_int_eq(GetRate(res), 5);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec6, dec8);
    x = 4294967295, y = 1, z = 21;
    ck_assert_int_eq(GetRate(res), 5);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mul(dec9, dec6);                                      // dNAN*NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mul(dec9, dec9);                                      // dNAN*dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mul(dec9, dec10);                                      // dNAN*INF
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mul(dec10, dec9);                                      // INF*dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mul(dec1, dec10);                                      // = NORM*dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Mul(dec3, dec10);                                      // = 0*dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mul(dec10, dec1);                                      // = dINFINITY*NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Mul(dec10, dec10);                                      // = dINFINITY*dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Mul(dec1, dec11);                                      // = NORM*dNEGATIVE_INFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 2);

    res = Mul(dec3, dec11);                                      // = 0*dNEGATIVE_INFINITY
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

    res = Mod(dec1, dec2);
    long int x = 0, y = 934549, z = 19626453;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec2, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec3, dec2);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec3, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec2, dec3);
    x = 0, y = 0, z = 0;
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec6, dec4);                                       // 1%MAX VALUE
    x = 0, y = 0, z = 1;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec4, dec4);                                       // MAX VALUE%MAX VALUE
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = Mod(dec12, dec13);
    x = 0, y = 0, z = 10;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec13, dec12);
    x = 0, y = 0, z = 33;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec2, dec14);
    x = 0, y = 0, z = 67317;
    ck_assert_int_eq(GetRate(res), 2);
    ck_assert_int_eq(GetSign(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec14, dec2);
    x = 0, y = 0, z = 1000;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec8, dec6);
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 1);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec6, dec8);
    x = 0, y = 0, z = 1;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_int_eq(GetSign(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);

    res = Mod(dec9, dec6);                                      // dNAN%NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec9, dec9);                                      // dNAN%dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec9, dec10);                                      // dNAN%INF
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec10, dec9);                                      // INF%dNAN
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec1, dec10);                                      // = NORM%dINFINITY
    x = 1, y = 4294967295, z = 21;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = Mod(dec3, dec10);                                      // = 0%dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = Mod(dec10, dec3);                                      // = dINFINITY%0
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec10, dec1);                                      // = dINFINITY%NORM
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 1);

    res = Mod(dec10, dec10);                                      // = dINFINITY%dINFINITY
    x = 0, y = 0, z = 0;
    ck_assert_int_eq(GetRate(res), 0);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 3);

    res = Mod(dec1, dec11);                                      // = NORM%dNEGATIVE_INFINITY
    x = 1, y = 4294967295, z = 21;
    ck_assert_int_eq(GetRate(res), 8);
    ck_assert_mem_eq(res.bits + 2, &x, 4);
    ck_assert_mem_eq(res.bits + 1, &y, 4);
    ck_assert_mem_eq(res.bits, &z, 4);
    ck_assert_int_eq(res.value_type, 0);

    res = Mod(dec3, dec11);                                      // = 0%dNEGATIVE_INFINITY
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
    TCase *IsLessCase = tcase_create("IsLess test");
    TCase *is_greaterCase = tcase_create("is_greater test");
    TCase *IsLessOrEqualCase = tcase_create("IsLessOrEqual test");
    TCase *IsGreaterOrEqualCase = tcase_create("IsGreaterOrEqual test");
    TCase *IsEqualCase = tcase_create("IsEqual test");
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
    TCase *IntToBit96_Case = tcase_create("IntToBit96_test");
    TCase *Bit96ToInt_Case = tcase_create("Bit96ToInt_test");
    TCase *FloatToBit96_Case = tcase_create("FloatToBit96_test");
    TCase *Bit96ToFloat_Case = tcase_create("Bit96ToFloat_test");
    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, IntToBit96_Case);
    tcase_add_test(IntToBit96_Case, IntToBit96_test);
    suite_add_tcase(s1, Bit96ToInt_Case);
    tcase_add_test(Bit96ToInt_Case, Bit96ToInt_test);
    suite_add_tcase(s1, FloatToBit96_Case);
    tcase_add_test(FloatToBit96_Case, FloatToBit96_test);
    suite_add_tcase(s1, Bit96ToFloat_Case);
    tcase_add_test(Bit96ToFloat_Case, Bit96ToFloat_test);
    suite_add_tcase(s1, IsLessCase);
    tcase_add_test(IsLessCase, IsLess_test);
    suite_add_tcase(s1, is_greaterCase);
    tcase_add_test(is_greaterCase, is_greater_test);
    suite_add_tcase(s1, IsLessOrEqualCase);
    tcase_add_test(IsLessOrEqualCase, IsLessOrEqual_test);
    suite_add_tcase(s1, IsGreaterOrEqualCase);
    tcase_add_test(IsGreaterOrEqualCase, IsGreaterOrEqual_test);
    suite_add_tcase(s1, IsEqualCase);
    tcase_add_test(IsEqualCase, IsEqual_test);
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

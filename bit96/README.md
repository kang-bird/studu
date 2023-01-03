# bit96 

Implementation of your own bit96.h library.

## Information

The bit96 value type represents decimal numbers ranging from positive 79,228,162,514,264,337,593,543,950,335 to negative 79,228,162,514,264,337,593,543,950,335. The default value of a bit96 is 0. The bit96 value type is appropriate for financial calculations that require large numbers of significant integral and fractional digits and no round-off errors. The bit96 type does not eliminate the need for rounding. Rather, it minimizes errors due to rounding.

When the result of the division and multiplication is passed to the Round method, the result suffers no loss of precision.

A bit96 number is a floating-point value that consists of a sign, a numeric value where each digit in the value ranges from 0 to 9, and a scaling factor that indicates the position of a floating decimal point that separates the integral and fractional parts of the numeric value.

The binary representation of a bit96 value consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the 96-bit integer and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28. Therefore, the binary representation of a bit96 value the form, ((-2^96 to 2^96) / 10^(0 to 28)), where -(2^96-1) is equal to MinValue, and 2^96-1 is equal to MaxValue.

The scaling factor also can preserve any trailing zeros in a bit96 number. Trailing zeros do not affect the value of a bit96 number in arithmetic or comparison operations. 

### Binary representation

The binary representation of a bit96 number consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the integer number and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28.

bit96 number can be implemented as a four-element array of 32-bit signed integers (`int bits[4];`).

`bits[0]`, `bits[1]`, and `bits[2]` contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.

`bits[3]` contains the scale factor and sign, and consists of following parts:
- Bits 0 to 15, the lower word, are unused and must be zero.
- Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
- Bits 24 to 30 are unused and must be zero.
- Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

Note that the bit representation differentiates between negative and positive zero. These values can be treated as being equal in all operations.

### Example:

```c
typedef enum {
    dNORMAL_VALUE = 0,
    dINFINITY = 1,
    dNEGATIVE_INFINITY = 2,
    dNAN = 3
} value_type_t;

typedef struct 
{
    int bits[4];
    value_type_t value_type;
} bit96;
```

The value_type field contains information about the type of number, with the dNORMAL_VALUE value, the bits array contains a number, with other values, all elements of the bits array are 0  

### Arithmetic Operators

| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Addition | + | bit96 Add(bit96, bit96) |
| Subtraction | - | bit96 Sub(bit96, bit96) |
| Multiplication | * | bit96 Mul(bit96, bit96) | 
| Division | / | bit96 Div(bit96, bit96) |
| Modulo | Mod | bit96 Mod(bit96, bit96) |

If an error occurs during the operation, the error type is written to the value_type variable  

### Comparison Operators (implemented by  [ExpectoPatronus](https://github.com/ExpectoPatronus))

| Operator name | Operators  | Function | 
| ------ | ------ | ------ |
| Less than | < | int IsLess(bit96, bit96) |
| Less than or equal to | <= | int IsLessOrEqual(bit96, bit96) | 
| Greater than | > |  int IsGreater(bit96, bit96) |
| Greater than or equal to | >= | int IsGreaterOrEqual(bit96, bit96) | 
| Equal to | == |  int IsEqual(bit96, bit96) |
| Not equal to | != |  int IsNotEqual(bit96, bit96) |

Return value:
- 0 - TRUE
- 1 - FALSE

### Convertors and parsers (implemented by rleonard)

| Convertor/parser | Function | 
| ------ | ------ |
| From int  | int IntToBit96(int src, bit96 *dst) |
| From float  | int FloatToBit96(float src, bit96 *dst) |
| To int  | int Bit96ToInt(bit96 src, int *dst) |
| To float  | int Bit96ToFloat(bit96 src, float *dst) |

Return value - code error:
- 0 - SUCCESS
- 1 - CONVERTING ERROR

*Note on the conversion of a float type number:*
- *If the numbers are too small (0 < |x| < 1e-28), return an error and value equal to 0, value_type = 0*
- *If the numbers are too large (|x| > 79,228,162,514,264,337,593,543,950,335) or are equal to infinity, return an error and value_type of infinity with the corresponding sign*
- *When processing a number with the float type, convert all the digits contained in it*

### Another functions (implemented by  [ExpectoPatronus](https://github.com/ExpectoPatronus))

| Description | Function | 
| ------ | ------ |
| Rounds a specified bit96 number to the closest integer toward negative infinity. | bit96 Floor(bit96) |	
| Rounds a bit96 value to the nearest integer. | bit96 Round(bit96) |
| Returns the integral digits of the specified bit96; any fractional digits are discarded, including trailing zeroes. | bit96 Truncate(bit96) |
| Returns the result of multiplying the specified bit96 value by negative one. | bit96 Negate(bit96) |
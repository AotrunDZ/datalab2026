/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {    
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(x && y){
        return !(x>>31 ^ y>>31);
    }
    if(!x && !y){
        return 1;
    }
    return 0;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a=(v>>16>0)<<4;
    v=v>>a;
    int b=(v>>8>0)<<3;
    v=v>>b;
    int c=(v>>4>0)<<2;
    v=v>>c;
    int d=(v>>2>0)<<1;
    v=v>>d;
    return a|b|c|d|(v>>1);
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int ns=n<<3;
    int ms=m<<3;
    int a=(x >> ns)&0xFF;
    int b=(x >> ms)&0xFF;
    x=x&~((0xFF<<ns)|(0xFF<<ms));
    return x|(a<<ms)|(b<<ns);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    int count=31;
    int temp=0;
    unsigned int reversed=0;
    temp=v&1;
    reversed=reversed|temp;
    while(count){
        count-=1;
        reversed=reversed<<1;
        v=v>>1;
        temp=v&1;
        reversed=reversed|temp;
    }
    return reversed;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask=0x7FFFFFFF;
    int m=n+0xFFFFFFFF+(!n);
    mask=(mask<<(!n)|1);
    mask=mask>>m;
    return mask&(x>>n);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count=0;
    int judge=0;
    int add=0;
    judge=!(~(x>>16));
    add=judge<<4;
    count+=add;
    x=x<<(add);
    judge=!(~(x>>24));
    add=judge<<3;
    count+=add;
    x=x<<(add);
    judge=!(~(x>>28));
    add=judge<<2;
    count+=add;
    x=x<<(add);
    judge=!(~(x>>30));
    add=judge<<1;
    count+=add;
    x=x<<(add);
    judge=!(~(x>>31));
    add=judge;
    count+=add;
    x=x<<(add);
    judge=!(~(x>>31));
    add=judge;
    count+=add;
    return count;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned int sign=x&0x80000000;
    unsigned int num=x;
    int exponent=0;
    unsigned int fraction;
    unsigned int round;
    if(sign){num=-x;}
    if(num==0){return num;}
    fraction=num;
    while(num!=1){
        exponent+=1;
        num=num>>1;
    }
    if(exponent<=23){
        fraction=(fraction<<(23-exponent))&0x7fffff;
    }
    else{
        int shift=exponent-23;
        round=fraction&((1<<shift)-1);
        unsigned int half=1<<(shift-1);
        fraction=fraction>>shift;
        if((round>half) |
           ((round==half) & (fraction&1))){
            fraction=fraction+1;
        }
        if(fraction>>24){
            exponent=exponent+1;
        }
        fraction=fraction&0x7fffff;
    }
    return sign|((exponent+127)<<23)|fraction;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign=uf & 0x80000000;
    unsigned exponent=uf & 0x7f800000;
    unsigned fraction=uf & 0x007fffff;
    if(exponent==0x7f800000){return uf;}
    if(exponent==0){
        if(fraction>=0x00400000){
            exponent+=0x00800000;
        }
        fraction=(fraction<<1)& 0x007fffff;
    }
    else{
        exponent+=0x00800000;
    }
    unsigned answer=sign|exponent|fraction;
    return answer;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1,unsigned uf2){
    int sign=(uf2>>31)&1;
    int exp=(uf2>>20)&0x7ff;
    int E=exp-1023;
    unsigned frac;
    if(exp>=0x7ff)return 0x80000000;
    if(E<0)return 0;
    if(E>31)return 0x80000000;
    frac=(uf2&0xfffff)|0x100000;
    if(E<=20){
        frac=frac>>(20-E);
    }
    else{
        frac=(frac<<(E-20))|(uf1>>(52-E));
    }
    if(sign)return -frac;
    if(E>=31)return 0x80000000;
    return frac;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    unsigned exponent;
    unsigned fraction;
    if(x<-149){return 0;}
    if(x<-126){
        fraction=1;
        fraction=fraction<<(x+149);
        return fraction;
    }
    if(x>127){return 0x7f800000;}
    exponent=x+127;
    return exponent<<23;
}

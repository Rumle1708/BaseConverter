#include <stdio.h>
#include <stdint.h>
//#include <stdlib.h>

const uint8_t HEX_LUT[16] =
{
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
};

typedef struct number
{
    uint64_t bits; // Bits of the input number
    uint8_t isSigned;
    uint8_t numOfBytes; // Bytes required to represent number
    uint8_t isFloat;
} number;

uint8_t isSigned(const char *str)
{
    // Function to determine if string as decimal is signed
    if (str[0] == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint64_t strLen(const char *str)
{
    // Function that determines length of string does not count NULL termination
    int strLen = 0;
    while ((str[strLen] != 0) || strLen > 100) // 100 added to prevent infinite loop
    {
        strLen++;
    }
    return strLen;
}

int64_t powerOf(int64_t base, int64_t exp)
{
    // Function that computes a base lifted to the power of an exponent
    int64_t result = base;
    if (exp == 0)
    {
        return 1;
    }
    for (int i = 1; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

uint64_t decStringToInt(const char *str)
{
    // Function that returns an unsigned integer from a string
    uint64_t value = 0;
    int i;
    int negFlag;
    if (isSigned(str))
    {
        i = 1;
        negFlag = 1;
    }
    else
    {
        i = 0;
        negFlag = 0;
    }
    for (; i < strLen(str); i++)
    {
        value += powerOf(10, strLen(str) - i - 1) * (str[i] - 48);
    }
    if (negFlag)
    {
        value = ~value + 1;
    }
    return value;
}

void numOfBytes(number *n)
{
    // Function to determine number of bytes required to represent value
    int8_t numOfBytes;

    if (n->bits < 0x100)
    {
        numOfBytes = 1;
    }
    else if (n->bits < 0x10000)
    {
        numOfBytes = 2;
    }
    else if (n->bits < 0x100000000)
    {
        numOfBytes = 4;
    }
    else
    {
        numOfBytes = 8;
    }
    n->numOfBytes = numOfBytes;
}

void decStringToNumber(number *n, const char *str)
{
    // Function that returns a number struct from input string
    n->bits = 0;
    int i;
    if (isSigned(str))
    {
        i = 1;
        n->isSigned = 1;
    }
    else
    {
        i = 0;
        n->isSigned = 0;
    }
    for (; i < strLen(str); i++)
    {
        n->bits += powerOf(10, strLen(str) - i - 1) * (str[i] - 48);
    }

    numOfBytes(n);

    n->isFloat = 0;
}

void printNumber(number *n)
{
    printf("Absolute decimal value is %lu\n", n->bits);
    printf("The sign of value is %u\n", n->isSigned);
    printf("The number of bytes required are %u\n", n->numOfBytes);
    printf("Is number a float %u\n", n->isFloat);
}

void printNumberBinary(number *n)
{
    // Prints a number as a binary string
    uint64_t bitsToPrint;

    if (n->isSigned)
    {
        bitsToPrint = ~n->bits + 1;
    }
    else
    {
        bitsToPrint = n->bits;
    }
    for (uint8_t i = n->numOfBytes * 8; i > 0; i--)
    {
        if (i % 8 == 7 && i != n->numOfBytes * 8 - 1)
        {
            printf(" ");
        }
        
        printf("%llu", 1LLU & (bitsToPrint >> (i - 1)));
    }
    printf("\n");
}

void printNumberDecimal(number *n)
{
    // Prints number in decimal representation
    if (n->isSigned)
    {
        printf("-");
    }
    printf("%lu\n", n->bits);
}

void printNumberHex(number *n)
{
    // Prints number as hexadecimal
    uint64_t bitsToPrint;
    if (n->isSigned)
    {
        bitsToPrint = ~n->bits + 1;
    }
    else
    {
        bitsToPrint = n->bits;
    }

    uint8_t i = n->numOfBytes * 2;

    for (; i > 0; i--)
    {
        //printf("kugle\n");
        printf("%c", HEX_LUT[0xFLLU & (bitsToPrint >> (i - 1)*4)]);
    }
    printf("\n");
}

void printInfo()
{
    printf("base 1.0\n");
    printf("2022 Mads Rumle Nordstroem.\n");
}

void printHelp()
{
    // Function to help user
    printf("usage: base [-options] [number]\n");
}

void printOptions()
{
    printf("-v              Print version info\n");
    printf("-h              Print this help screen\n");
}

int main(int argc, const char *argv[])
{
    printf("\033[1;31m");
    printf("--------BASE CONVERTER--------\n");
    printf("\033[0;33m");
    if (argc < 2)
    {
        // TODO print help
        printHelp();
        //exit(1);
    }

    number n;
    decStringToNumber(&n, argv[1]);

    printf("Converting number %s\n", argv[1]);

    printf("Bin: ");
    printNumberBinary(&n);
    printf("Dec: ");
    printNumberDecimal(&n);
    printf("Hex: ");
    printNumberHex(&n);

    
    printf("\033[1;31m");
    printf("--------END OF PROGRAM--------\n");
    printf("\033[0m");
    return 0;
}

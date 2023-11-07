#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printInfo()
{
    printf("base version 1.0 - Mads Rumle Nordstrøm\n");
}

void printHelp()
{
    // Function to help user
    printf("usage: base [0b|0o|0d|0x][number]\n");
    printf("Example: base 0xaf20\n");
}

void printNumberBinary(long long n)
{
    // Prints a number as a binary string
    while (n) {
        if (n & 1LLU) {
            printf("1");
        } else {
            printf("0");
        }
        n >>= 1;
    }
    printf("\n");
}

char* itostr(char *dest, size_t size, int a, int base) {
  // Max text needs occur with itostr(dest, size, INT_MIN, 2)
  char buffer[sizeof a * 8 + 1 + 1]; 
  static const char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  if (base < 2 || base > 36) {
    fprintf(stderr, "Invalid base");
    return NULL;
  }

  // Start filling from the end
  char* p = &buffer[sizeof buffer - 1];
  *p = '\0';

  // Work with negative `int`
  int an = a < 0 ? a : -a;  

  do {
    *(--p) = digits[-(an % base)];
    an /= base;
  } while (an);

  if (a < 0) {
    *(--p) = '-';
  }

  size_t size_used = &buffer[sizeof(buffer)] - p;
  if (size_used > size) {
    fprintf(stderr, "Scan buffer %zu > %zu", size_used , size);
    return NULL;
  }
  return memcpy(dest, p, size_used);
}

int getBaseFromChar(char c)
{
    if (c == 'b') {
        return 2;
    }
    if (c == 'o') {
        return 8;
    }
    if (c == 'd') {
        return 10;
    }
    if (c == 'x') {
        return 16;
    }
    return 0;
}

int getbaseFromString(char* str, int fallback)
{
    char* charPtr = str;
    int base = fallback;

    while (*charPtr != 0) {
        if (getBaseFromChar(*charPtr)) {
            base = getBaseFromChar(*charPtr);
            break;
        }
        charPtr++;
    }

    return base;
}

void removeBaseIndicator(char* str)
{
    char* baseIndicatorPtr = NULL;
    char* charPtr = str;

    while (*charPtr != 0) {
        if (getBaseFromChar(*charPtr)) {
            baseIndicatorPtr = charPtr;
            break;
        }
        charPtr++;
    }

    if (baseIndicatorPtr == NULL) {
        return;
    }

    int i = 0;
    charPtr = ++baseIndicatorPtr;
    while (*charPtr != 0) {
        str[i] = *charPtr;
        charPtr++;
        i++;
    }
    str[i] = *charPtr;
}

// 2 base indicator bits + 64 bits + string termination
#define BUFFER_SIZE 67

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printInfo();
        printHelp();
        exit(1);
    }

    char strBuffer[BUFFER_SIZE];
    char printBuffer[BUFFER_SIZE];

    strncpy(strBuffer, argv[1], BUFFER_SIZE);
    printf("Input: %s\n", strBuffer);

    int base = getbaseFromString(strBuffer, 10);
    printf("Base: %d\n", base);

    removeBaseIndicator(strBuffer);
    printf("Removed base: %s\n", strBuffer);

    long long number = strtoll(strBuffer, NULL, base);
    printf("Number as lld: %lld\n", number);

    itostr(printBuffer, BUFFER_SIZE, number, 2);
    printf("0b%s\n", printBuffer);
    itostr(printBuffer, BUFFER_SIZE, number, 8);
    printf("0o%s\n", printBuffer);
    itostr(printBuffer, BUFFER_SIZE, number, 10);
    printf("0d%s\n", printBuffer);
    itostr(printBuffer, BUFFER_SIZE, number, 16);
    printf("0x%s\n", printBuffer);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "decimal.h"

int64_t myPow(int64_t x,int64_t n)
{
    int64_t i; /* Variable used in loop counter */
    int64_t number = 1;

    for (i = 0; i < n; ++i)
        number *= x;

    return(number);
}

int main(int argc, char const *argv[])
{
    char *test = "-255";
    if (!illegalDecStr(test))
    {
        decToBin(test);
        decToHex(test);
    }

    int64_t two = 2;

    for (int64_t i = 0; i < 64; i++)
    {
        printf("%ld\n", myPow(two,i));
    }
    char buffer [33];
    sprintf(8,buffer,2);
    printf ("binary: %s\n",buffer);
    return 0;
}

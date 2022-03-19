#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int64_t getBit(int64_t n, int64_t k){
    return (n >> k) & 1;
}

int illegalDecStr(const char *str){

    // Function that checks if the string contains illegal characters

    int i = 0;
    while (str[i] != 0)
    {
        if (str[i] < 48 || str[i] > 57) // Check ASCII values of string
        {
            if (str[i] != '-') // Check if minus sign
            {
                return 1; // Return error
            }
        }
        i++;
    }
    return 0; // Number is ok
}

void decToBin(const char *str){
    
    //Function that takes decimal number as string and prints it as binary
    
    int64_t value = strtol(str, NULL, 10); // Convert string to int

    int64_t max = 0b10000000;
    int64_t bytes = 1;
    int64_t shift = 1; // Needed to specify 64 bit

    while ((value >= max || value <= -(max + 1)) && bytes < 8)
    {
        bytes = bytes << 1;
        max = shift << (bytes*8);
    }

    for (int i = 8*bytes - 1; i >= 0; i--)
    {
        printf("%ld", getBit(value, i)); // Maybe optimize with buffer
        if (i%8 == 0)
        {
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    char *test = "485";
    if (!illegalDecStr(test))
    {
        decToBin(test);
    }
    return 0;
}

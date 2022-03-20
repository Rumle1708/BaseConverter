#include <stdint.h>

int64_t getBit(int64_t n, int64_t k){
    return (n >> k) & 1;
}
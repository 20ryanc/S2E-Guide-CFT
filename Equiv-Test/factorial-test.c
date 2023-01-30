#include <inttypes.h>
#include <stdio.h>

/**
 *  Computes x!
 *  If x > max, computes max!
 */
uint64_t factorial1(uint64_t x, uint64_t max) {
    uint64_t ret = 1;
    for (uint64_t i = 1; i<=x && i<=max; ++i) {
        ret = ret * i;
    }
    return ret;
}

/**
 *  Computes x!
 *  If x > max, computes max!
 */
uint64_t factorial2(uint64_t x, uint64_t max) {
    if (x > max) {
        return max;
    }

    if (x == 1) {
        return x;
    }
    return x * factorial2(x-1, max);
}

int main() {
    uint64_t max = 10;
    printf("%" PRId64 "\n", factorial1(11, max));
    printf("%" PRId64 "\n", factorial2(11, max));
    
    return 0;
}


#include "cryptonight_turtle.h"

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

long long current_timestamp()
{
    struct timespec te;
    clock_gettime(CLOCK_REALTIME, &te);
    return (long long) 10000LL*te.tv_sec + round(te.tv_nsec/1e5);
}

int main()
{
    uint32_t in[20], out[8];
    for (int i=0; i<sizeof(in); i++) in[i] = 0x00;
    for (int j=0; j<sizeof(out); j++) out[j] = 0x00;

    long long average = 0;
    long long begin = current_timestamp();
    while (1) {
        ++in[19];
        long long sample1 = current_timestamp();
        cryptonightturtle_hash(&in, &out, 80, 0);
        long long sample2 = current_timestamp();
        if (sample2-begin>10000) {
            average = (average + (sample2 - sample1)) / 2;
            printf("%d hashes/sec\n", 10000/average);
            begin = current_timestamp();
        }
    }

    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

/* define 100KB mem limit */
#define MEM_LIMIT 100*1024

/* Find the cycle len for n using lookup table */
int cycle_len(uint16_t *cache, int len, unsigned int n) {
    int clen = 0;
    while (n > 1) {
        /* Already found in lookup table */
        if (n <= len+1 && cache[n-2] != 0) {
            return cache[n-2] + clen;
        /* Power of 2 */
        } else if (n&(n-1) == 0) {
            return log2(n) + clen;
        }

        int is_even = n&1 ? 0 : 1;
        if (is_even) {
            n >>=1;
        } else {
            n = 3*n + 1;
        }
        clen++;
    }

    /* At n = 1 */
    return clen + 1;
}

/* Find max cycle len over a range of n */
int max_cyclelen(uint16_t *cache, int len, int i, int j) {
    /* We need i < j */
    if (j < i) {
        j = j^i;
        i = j^i;
        j = j^i;
    }

    int max_clen = 0;
    int t;
    while (i <= j) {
        t = cycle_len(cache, len, i);
        if (t > max_clen) {
            max_clen = t;
        }
        i++;
    }

    return max_clen;
}

int main() {
    int i, j, clen, cachelen;
    cachelen = MEM_LIMIT/sizeof(uint16_t);
    uint16_t *cache = (uint16_t *) calloc(cachelen, sizeof(uint16_t));

    /* Build lookup table */
    for (i=2; i <= cachelen + 1; i++) {
        /* Let's save 2 ints by mapping index 0 => 2 */
        cache[i-2] = cycle_len(cache, cachelen, i);
    }

    /* Read and display results */
    while (scanf("%d %d\n", &i, &j) == 2) {
        clen = max_cyclelen(cache, cachelen, i, j);
        printf("%d %d %d\n", i, j, clen);
    }

    free(cache);

    return 0;
}

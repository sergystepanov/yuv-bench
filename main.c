#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "conv.h"
#include "gen.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define BOLD  "\033[1m"
#define RESET "\x1B[0m"

int main(void) {
	const int w = 2000;
	const int h = 1000;

    const int ss = 4 * w * h;
    const int ds = w * h * 3 / 2;
    unsigned char *src = malloc(ss * sizeof(unsigned char));
    unsigned char *dst = malloc(ds * sizeof(unsigned char));

    // cpu
    system("cat /proc/cpuinfo | grep \"model name\" | head -1");
    printf("image: %dx%d\nsrc: %d bytes, dst: %d bytes\n\n", w, h, ss, ds);

    some_rgba(w, h, src);

    clock_t start, end;
    double wasted;
    double mean = 0;
    int runs = 100;
    double vals[100];

    for (int i = 1; i <= runs; i++) {
        start = clock();
        rgbaToYuv(dst, src, w, h, BETWEEN_FOUR);
        end = clock();
        wasted = (double) (end - start) / CLOCKS_PER_SEC * 1000;
        mean += (wasted - mean) / i;
        printf("| %5.2f", wasted);
        printf(GRN "ms " RESET);
        if (i % 6 == 0) printf("\n");
        vals[i - 1] = wasted;
    }

    double sum = 0;
    for (int i = 0; i < runs; i++) {
        sum += pow((vals[i] - mean), 2);
    }
    double std_deviation = sqrt(sum / runs);
    printf("\n------------\n");
    printf(BOLD "%.2fms" RESET, mean);
    printf(" (+-%.2fms)\n", std_deviation);

    free(src);
    free(dst);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "conv/conv.h"
#include "image/gen.h"
#include "hardware/hardware.h"
#include "tui/term.h"
#include "stats/stats.h"

int main(void) {
    const int w = 1920;
    const int h = 1080;

    const int ss = 4 * w * h;
    const int ds = w * h * 3 / 2;
    unsigned char *src = malloc(ss * sizeof(unsigned char));
    unsigned char *dst = malloc(ds * sizeof(unsigned char));

    printCpuInfo();
    printf("image: %dx%d\nsrc: %dKB, dst: %dKB\n\n", w, h, ss / 1000, ds / 1000);

    some_rgba(w, h, src);

    convFn fn1 = rgbaToYuvDumb;
    convFn fn2 = rgbaToYuvLut;
    int runs = 200;
    runStats stats;
    newRunStats(&stats, runs);
    runStats lutStats;
    newRunStats(&lutStats, runs);

    // fastest
    for (int i = 1; i <= runs; i++) {
        startTime(&stats);
        fn1(dst, src, w, h, BETWEEN_FOUR);
        stopTime(&stats);
        startTime(&lutStats);
        fn2(dst, src, w, h, BETWEEN_FOUR);
        stopTime(&lutStats);
    }

    for (int i = 0; i < runs; i++) {
        if (stats.runs[i] == stats.max) {
            printf(RED);
        } else {
            if (stats.runs[i] == stats.min) {
                printf(GRN);
            } else {
                if (stats.runs[i] <= stats.sigma + stats.std_deviation) {
                    printf(GRN);
                } else {
                    if (stats.runs[i] > stats.sigma + stats.std_deviation) {
                        printf(YEL);
                    }
                }
            }
        }

        printf("%6.2f", stats.runs[i]);
        //printf(GRN "ms " RESET);
        if ((i + 1) % 10 == 0) printf("\n");
    }

    printf(RESET "\n------------\n");
    printf("fast: ");
    printf(BOLD "%.2fms" RESET, stats.mean);
    printf(" (+-%.2fms)\n", stats.std_deviation);

    printf("lut:  ");
    printf(BOLD "%.2fms" RESET, lutStats.mean);
    printf(" (+-%.2fms)\n", lutStats.std_deviation);

    clearRunStats(&stats);
    clearRunStats(&lutStats);

    free(src);
    free(dst);

    return 0;
}

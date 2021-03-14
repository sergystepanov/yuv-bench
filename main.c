#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <float.h>

#include "conv.h"
#include "gen.h"

#if defined(_WIN32) || defined(_WIN64)
const char *os = "win";
#else
#ifdef __linux
const char* os = "nix";
#else
const char* os = "";
#endif
#endif

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
    const int w = 1920;
    const int h = 1080;

    const int ss = 4 * w * h;
    const int ds = w * h * 3 / 2;
    unsigned char *src = malloc(ss * sizeof(unsigned char));
    unsigned char *dst = malloc(ds * sizeof(unsigned char));

    // cpu
    if (strcmp(os, "win") != 0) {
        system("cat /proc/cpuinfo | grep \"model name\" | head -1");
    } else {
        system("for /f \"usebackq skip=1 tokens=*\" %i in (`wmic cpu get name ^| findstr /r /v \"^$\"`) do @echo %i");
    }
    printf("image: %dx%d\nsrc: %dKB, dst: %dKB\n\n", w, h, ss / 1000, ds / 1000);

    some_rgba(w, h, src);

    clock_t start, end;
    double wasted, mean = 0, min = DBL_MAX, max = 0;
    int runs = 200;
    double vals[200];

    for (int i = 1; i <= runs; i++) {
        start = clock();
        rgbaToYuv(dst, src, w, h, BETWEEN_FOUR);
        end = clock();
        wasted = (double) (end - start) / CLOCKS_PER_SEC * 1000;
        mean += (wasted - mean) / i;
        vals[i - 1] = wasted;
        if (wasted < min) {
            min = wasted;
        }
        if (wasted > max) {
            max = wasted;
        }
    }

    double sum = 0;
    for (int i = 0; i < runs; i++) {
        sum += pow((vals[i] - mean), 2);
    }
    double std_deviation = sqrt(sum / runs);
    double sigma = (/*min + max*/mean);

    for (int i = 0; i < runs; i++) {
        if (vals[i] == max) {
            printf(RED);
        } else {
            if (vals[i] == min) {
                printf(GRN);
            } else {
                if (vals[i] <= sigma + std_deviation) {
                    printf(GRN);
                } else {
                    if (vals[i] > sigma + std_deviation) {
                        printf(YEL);
                    }
                }
            }
        }

        printf("%6.2f", vals[i]);
        //printf(GRN "ms " RESET);
        if ((i + 1) % 10 == 0) printf("\n");
    }

    printf(RESET "\n------------\n");
    printf(BOLD "%.2fms" RESET, mean);
    printf(" (+-%.2fms)\n", std_deviation);

    free(src);
    free(dst);

    return 0;
}

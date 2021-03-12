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
  // use call stack, babyyyyy
  unsigned char src[4*800*600] = {0};
  unsigned char dst[800*600*3/2] = {0};

  const int w = 800;
  const int h = 600;

  // cpu
  system("cat /proc/cpuinfo | grep \"model name\" | head -1");
  printf("image: %dx%d\nsrc: %d bytes, dst: %d bytes\n\n", w, h, (int) sizeof(src), (int) sizeof(dst));

  some_rgba(w, h, src);

  clock_t start;
  int wasted;
  double mean = 0;
  int runs = 100;
  int vals[runs];
     
  for (int i = 1; i <= runs; i++) {
    start = clock();
    rgbaToYuv(dst, src, w, h, BETWEEN_FOUR);
    wasted = ((double) (clock() - start)) / (CLOCKS_PER_SEC/1000000);
    mean += (wasted - mean)/i;
    printf("| %5d", wasted);
    printf(GRN "μs " RESET);
    if (i % 6 == 0) printf("\n");
    vals[i-1] = wasted;
  }

  int sum = 0;
  for (int i = 0; i < runs; i++) {
    sum += pow((vals[i] - mean), 2);
  }
  double std_deviation = sqrt(sum/runs);
  printf("\n------------\n");
  printf(BOLD "%dμs" RESET, (int) mean);
  printf("+-(%dμs)\n", (int) std_deviation);

  return 0;
}


#ifndef YUV_BENCH_CONV_H
#define YUV_BENCH_CONV_H

#include <stdint.h>

typedef enum {
    // It will take each TL pixel for chroma values.
    // XO  X   XO  X
    // X   X   X   X
    TOP_LEFT = 0,
    // It will take an average color from the 2x2 pixel group for chroma values.
    // X   X   X   X
    //   O       O
    // X   X   X   X
    BETWEEN_FOUR = 1
} chromaPos;

typedef void (*convFn)(void *, void *, int, int, chromaPos);

void rgbaToYuvDumb(void *destination, void *source, int width, int height, chromaPos chroma);

#endif //YUV_BENCH_CONV_H
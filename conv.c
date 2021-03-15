#include "conv.h"

void rgbaToYuv(void *destination, void *source, int width, int height, chromaPos chroma) {
    const int image_size = width * height;
    unsigned char *rgba = source;
    unsigned char *dst_y = destination;
    unsigned char *dst_u = dst_y + image_size;
    unsigned char *dst_v = dst_y + image_size + image_size / 4;

    // Y plane
    for (int i = 0, len = image_size; i < len; i += 4 * 4) {
        *dst_y++ = ((66 * rgba[i] + 129 * rgba[i + 1] + 25 * rgba[i + 2]) >> 8) + 16;
        *dst_y++ = ((66 * rgba[i + 4] + 129 * rgba[i + 4 + 1] + 25 * rgba[i + 4 + 2]) >> 8) + 16;
        *dst_y++ = ((66 * rgba[i + 8] + 129 * rgba[i + 8 + 1] + 25 * rgba[i + 8 + 2]) >> 8) + 16;
        *dst_y++ = ((66 * rgba[i + 12] + 129 * rgba[i + 12 + 1] + 25 * rgba[i + 12 + 2]) >> 8) + 16;
    }

    return;

    int r1, g1, b1, stride;
    // U+V plane
    if (chroma == TOP_LEFT) {
        for (int y = 0; y < height; y += 2) {
            stride = 4 * y * width;
            for (int x = 0; x < width; x += 2) {
                r1 = 4 * x + stride;
                g1 = r1 + 1;
                b1 = g1 + 1;
                *dst_u++ = ((-38 * rgba[r1] + -74 * rgba[g1] + 112 * rgba[b1]) >> 8) + 128;
                *dst_v++ = ((112 * rgba[r1] + -94 * rgba[g1] + -18 * rgba[b1]) >> 8) + 128;
            }
        }
    } else if (chroma == BETWEEN_FOUR) {
        int r2, g2, b2, r3, g3, b3, r4, g4, b4;

        for (int y = 0; y < height; y += 2) {
            stride = 4 * y * width;
            for (int x = 0; x < width; x += 2) {
                // (1 2) x x
                //  x x  x x
                r1 = 4 * x + stride;
                g1 = r1 + 1;
                b1 = g1 + 1;
                r2 = r1 + 4;
                g2 = r2 + 1;
                b2 = g2 + 1;
                //  x x  x x
                // (3 4) x x
                r3 = r1 + 4 * width;

                g3 = r3 + 1;
                b3 = g3 + 1;
                r4 = r3 + 4;
                g4 = r4 + 1;
                b4 = g4 + 1;
                *dst_u++ = (((-38 * rgba[r1] + -74 * rgba[g1] + 112 * rgba[b1]) >> 8) +
                            ((-38 * rgba[r2] + -74 * rgba[g2] + 112 * rgba[b2]) >> 8) +
                            ((-38 * rgba[r3] + -74 * rgba[g3] + 112 * rgba[b3]) >> 8) +
                            ((-38 * rgba[r4] + -74 * rgba[g4] + 112 * rgba[b4]) >> 8) + 512) >> 2;
                *dst_v++ = (((112 * rgba[r1] + -94 * rgba[g1] + -18 * rgba[b1]) >> 8) +
                            ((112 * rgba[r2] + -94 * rgba[g2] + -18 * rgba[b2]) >> 8) +
                            ((112 * rgba[r3] + -94 * rgba[g3] + -18 * rgba[b3]) >> 8) +
                            ((112 * rgba[r4] + -94 * rgba[g4] + -18 * rgba[b4]) >> 8) + 512) >> 2;
            }
        }
    }
}

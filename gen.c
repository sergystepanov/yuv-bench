#include <stdint.h>

//   8x4
// xxxxrrrr
// xxxxrrrr
// ggggbbbb
// ggggbbbb
//
uint8_t* some_rgba(int w, int h, uint8_t *rgb) {
    int x, y, i, stride;
    int halfH = h / 2;
    int halfW = w / 2;

    for (y = 0; y < h; y++) {
        stride = 4 * y * w;
        for (x = 0; x < w; x++) {
            i = stride + x;
            rgb[i+0] = 000;
            rgb[i+1] = 000;
            rgb[i+2] = 000;
            rgb[i+3] = 255;
            if (y < halfH) {
                if (x > halfW) {
                    rgb[i+0] = 255;
                }
            } else {
                if (x < halfW) {
                  rgb[i+1] = 255;
                } else {
                  rgb[i+2] = 255;
                }
            }
        }
    }
    return rgb;
}
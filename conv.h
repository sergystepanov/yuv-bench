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

void rgbaToYuv(void *destination, void *source, int width, int height, chromaPos chroma);
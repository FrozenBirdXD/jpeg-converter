#include <stdio.h>
#include <stdlib.h>

#include "bitmaps.h"

int
main(int argc, char const* argv[]) {
    image_t* image = read_file("../test-image.bmp");

    for (int i = 0; i < image->width; ++i) {
        free(image->data[i]);
    }
    free(image->data);
    return 0;
}

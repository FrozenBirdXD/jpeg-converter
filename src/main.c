#include <stdio.h>
#include <stdlib.h>

#include "bitmaps.h"
#include "color_space_transform.h"

int
main(int argc, char const* argv[]) {
    rgbimage_t* rgb_image = read_bitmap("../test-image.bmp");
    ycbcr_image_t* ycbcr_image = color_space_transform(rgb_image);

    free_rgb_image(rgb_image);
    return 0;
}

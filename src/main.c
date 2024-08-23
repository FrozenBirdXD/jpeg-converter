#include <stdio.h>
#include <stdlib.h>

#include "bitmaps.h"
#include "color_space_transform.h"

int
main(int argc, char const* argv[]) {
    rgbimage_t* rgb_image = read_bitmap("../test-image.bmp");
    if (rgb_image == NULL) {
        return 1;
    }
    ycbcr_image_t* ycbcr_image = color_space_transform(rgb_image);
    if (ycbcr_image == NULL) {
        free_rgb_image(rgb_image);
        return 1;
    }
    printf("\npixel values ycbcr: %d %d %d", ycbcr_image->data[1919][1079].y, ycbcr_image->data[1919][1079].cb,
           ycbcr_image->data[1919][1079].cr);

    free_ycbcr_image(ycbcr_image);
    free_rgb_image(rgb_image);
    return 0;
}

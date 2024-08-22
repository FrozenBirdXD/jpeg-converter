#ifndef COLOR_SPACE_TRANSFORM_H
#define COLOR_SPACE_TRANSFORM_H

#include <stdint.h>
#include "bitmaps.h"

typedef struct {
    uint8_t y;    
    uint8_t cb;
    uint8_t cr; 
} ycbcr_pixel_t;

typedef struct {
    ycbcr_pixel_t** data;
    uint32_t width;
    uint32_t height;
} ycbcr_image_t;

ycbcr_image_t* color_space_transform(const rgbimage_t* rgb_image);

#endif /* COLOR_SPACE_TRANSFORM_H */
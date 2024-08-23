#include <stdlib.h>
#include <stdio.h>

#include "bitmaps.h"
#include "color_space_transform.h"

ycbcr_image_t*
color_space_transform(const rgbimage_t* rgb_image) {
    ycbcr_image_t* ycbcr_image;
    uint32_t height = rgb_image->height, width = rgb_image->width;

    ycbcr_image = malloc(sizeof(ycbcr_image_t));
    if (ycbcr_image == NULL) {
        printf("Memory allocation failed");
        return NULL;
    }
    ycbcr_image->height = height;
    ycbcr_image->width = width;
    ycbcr_image->data = malloc(width * sizeof(ycbcr_pixel_t*));
    if (ycbcr_image->data == NULL) {
        printf("Memory allocation failed");
        free(ycbcr_image);
        return NULL;
    }

    for (size_t i = 0; i < width; ++i) {
        ycbcr_image->data[i] = malloc(height * sizeof(ycbcr_pixel_t));
        if (ycbcr_image->data[i] == NULL) {
            printf("Memory allocation failed");
            for (size_t j = 0; j < i; ++j) {
                free(ycbcr_image->data[j]);
            }
            free(ycbcr_image->data);
            free(ycbcr_image);
            return NULL;
        }
    }

    for (size_t i = 0; i < rgb_image->width; ++i) {
        for (size_t j = 0; j < rgb_image->height; ++j) {
            uint8_t r = rgb_image->data[i][j].r;
            uint8_t g = rgb_image->data[i][j].g;
            uint8_t b = rgb_image->data[i][j].b;
            /* Convert rgb to ycbcr */
            ycbcr_image->data[i][j].y = 16 + (((r << 6) + (r << 1) + (g << 7) + g + (b << 4) + (b << 3) + b) >> 8);
            ycbcr_image->data[i][j].cb =
                128
                + ((-((r << 5) + (r << 2) + (r << 1)) - ((g << 6) + (g << 3) + (g << 1)) + (b << 7) - (b << 4)) >> 8);
            ycbcr_image->data[i][j].cr =
                128 + (((r << 7) - (r << 4) - ((g << 6) + (g << 5) - (g << 1)) - ((b << 4) + (b << 1))) >> 8);
        }
    }
    return ycbcr_image;
}

void
free_ycbcr_image(ycbcr_image_t* ycbcr_image) {
    if (ycbcr_image == NULL) {
        return;
    }
    for (size_t i = 0; i < ycbcr_image->width; ++i) {
        free(ycbcr_image->data[i]);
    }
    free(ycbcr_image->data);
    free(ycbcr_image);
}
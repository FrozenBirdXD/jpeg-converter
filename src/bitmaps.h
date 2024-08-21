#ifndef BITMAPS_H
#define BITMAPS_H

#include <stdint.h>

#pragma pack(push, 1)

typedef struct {
    /* Magic identifier: 0x4d42 */
    uint16_t header_field;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    /* Offset = Starting address, of the byte where image data (pixel array) is */
    uint32_t data_offset;
} bmp_fileheader_t;

typedef struct {
    uint32_t infoheader_size;
    int32_t image_width;
    int32_t image_height;
    /* Must be 1 */
    uint16_t num_color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t bitmap_data_size;
    /* In pixels per meter */
    int32_t horizontal_resolution;
    /* In pixels per meter */
    int32_t vertical_resolution;
    uint32_t num_of_colors;
    uint32_t num_of_important_colors;
} bmp_infoheader_t;

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} rgb_pixel_t;

#pragma pack(pop)

void read_file(const char* file_name);

#endif /* BITMAPS_H */

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

#pragma pack(pop)

void read_file(const char* file_name);

#endif /* BITMAPS_H */

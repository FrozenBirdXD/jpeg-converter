#include <stdio.h>

#include "bitmaps.h"

void
read_file(const char* file_name) {
    FILE* file;

    file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Error reading file '%s'", file_name);
        fclose(file);
        return;
    } else {
        printf("File reading successful!");
    }

    bmp_fileheader_t fileheader;
    fread(&fileheader, sizeof(fileheader), 1, file);

    if (fileheader.header_field != 19778) {
        printf("\nError, provided file is not a bitmap file. Has magic identifier: 0x%x", fileheader.header_field);
        fclose(file);
        return;
    }
    printf("\nMagic num: 0x%x", fileheader.header_field);
    printf("\nFilesize: %.2lfMB", fileheader.file_size / (double)1048576);
    printf("\nDataoffset (byte): %d", fileheader.data_offset);
    printf("\n");

    bmp_infoheader_t infoheader;
    fread(&infoheader, sizeof(infoheader), 1, file);

    if (infoheader.infoheader_size != 40) {
        printf("\nError, infoheader has unsupported size: %dbytes", infoheader.infoheader_size);
        fclose(file);
        return;
    }

    printf("\nImage pixel resolution: %d x %d", infoheader.image_width, infoheader.image_height);
    if (infoheader.num_color_planes != 1) {
        printf("\nError, number of color planes not supported: %d", infoheader.num_color_planes);
        fclose(file);
        return;
    }

    printf("\nColor depth (bits per pixel): %d", infoheader.bits_per_pixel);
    if (infoheader.bits_per_pixel != 24) {
        printf("\nError, color depth of %d is not supported, only 24 is supported", infoheader.bits_per_pixel);
        fclose(file);
        return;
    }

    if (infoheader.compression_method != 0) {
        printf("\nError, compression method unsupported, header value: %d", infoheader.compression_method);
        fclose(file);
        return;
    }

    fclose(file);
    printf("\nFile closed");
}
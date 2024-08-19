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
    printf("\nMagic num: 0x%d", fileheader.header_field);

    printf("\nFilesize: %.2lfMB", fileheader.file_size / 1048576.0);

    fclose(file);
    printf("\nFile closed");
}
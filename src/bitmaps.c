#include <stdio.h>
#include <stdlib.h>

#include "bitmaps.h"

rgbimage_t*
read_bitmap(const char* file_name) {
    bmp_fileheader_t fileheader;
    bmp_infoheader_t infoheader;
    rgbimage_t* image;
    FILE* file;

    file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Error reading file '%s'", file_name);
        fclose(file);
        return NULL;
    } else {
        printf("Reading file '%s' successful!", file_name);
    }

    fread(&fileheader, sizeof(fileheader), 1, file);

    if (fileheader.header_field != 19778) {
        printf("\nError, provided file is not a bitmap file. Has magic identifier: 0x%x", fileheader.header_field);
        fclose(file);
        return NULL;
    }
    printf("\nMagic num: 0x%x", fileheader.header_field);
    printf("\nFilesize: %.2lfMB", fileheader.file_size / (double)1048576);
    printf("\nDataoffset (byte): %d", fileheader.data_offset);
    printf("\n");

    fread(&infoheader, sizeof(infoheader), 1, file);

    if (infoheader.infoheader_size != 40) {
        printf("\nError, infoheader has unsupported size: %dbytes", infoheader.infoheader_size);
        fclose(file);
        return NULL;
    }

    printf("\nImage pixel resolution: %d x %d", infoheader.image_width, infoheader.image_height);
    if (infoheader.num_color_planes != 1) {
        printf("\nError, number of color planes not supported: %d", infoheader.num_color_planes);
        fclose(file);
        return NULL;
    }

    printf("\nColor depth (bits per pixel): %d", infoheader.bits_per_pixel);
    if (infoheader.bits_per_pixel != 24) {
        printf("\nError, color depth of %d is not supported, only 24 is supported", infoheader.bits_per_pixel);
        fclose(file);
        return NULL;
    }

    if (infoheader.compression_method != 0) {
        printf("\nError, compression method unsupported, header value: %d", infoheader.compression_method);
        fclose(file);
        return NULL;
    }

    /* Allocate memory for 2d array with image data */
    image = malloc(sizeof(rgbimage_t));
    if (image == NULL) {
        printf("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    image->height = infoheader.image_height;
    image->width = infoheader.image_width;

    image->data = malloc(infoheader.image_width * sizeof(rgb_pixel_t*));
    if (image->data == NULL) {
        printf("Memory allocation failed");
        free(image);
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < infoheader.image_width; ++i) {
        image->data[i] = malloc(infoheader.image_height * sizeof(rgb_pixel_t));
        if (image->data[i] == NULL) {
            printf("Memory allocation failed");
            // Free previously allocated rows
            for (size_t k = 0; k < i; ++k) {
                free(image->data[k]);
            }
            free(image->data);
            free(image);
            fclose(file);
            return NULL;
        }
    }

    /* Skip to data */
    fseek(file, fileheader.data_offset, SEEK_SET);

    uint8_t padding = (4 - (infoheader.image_width * sizeof(rgb_pixel_t)) % 4) % 4;
    for (int32_t i = infoheader.image_height - 1; i >= 0; --i) {
        for (size_t j = 0; j < infoheader.image_width; ++j) {
            fread(&image->data[j][i], sizeof(rgb_pixel_t), 1, file);
        }
        /* Skip padding from bmp */
        fseek(file, padding, SEEK_CUR);
    }

    /* printf("\npixel values rgb %d %d %d", image_data[1919][0].r, image_data[1919][0].g, image_data[1919][0].b); */

    fclose(file);
    printf("\nFile closed");
    return image;
}

void
free_rgb_image(rgbimage_t* image) {
    for (int i = 0; i < image->width; ++i) {
        free(image->data[i]);
    }
    free(image->data);
}
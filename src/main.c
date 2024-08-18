#include <stdio.h>

void read_file(const char* file_name);

int
main(int argc, char const* argv[]) {
    read_file("../test-image.bmp");
    return 0;
}

void
read_file(const char* file_name) {
    FILE* file;

    file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Error reading file '%s'", file_name);
        return;
    } else {
        printf("File reading successful!");
    }

    fclose(file);
    printf("\nFile closed");
}

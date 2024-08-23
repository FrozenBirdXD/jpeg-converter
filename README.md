# JPEG Compression from Scratch in C

This project is an implementation of JPEG image compression written in C, without using external libraries. The goal for me is to understand the steps in the JPEG compression algorithm, including color space transformation, discrete cosine transform (DCT), quantization, entropy coding, and more.

## Finished Steps

- **Bitmap Input Image**: Reads the pixel data from a 24-bit BMP image
- **Color Space Transfromation**: Converts the RGB image data to YCbCr
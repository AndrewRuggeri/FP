#include "Image.h"

Image::Image(uint32_t width, uint32_t height) : Matrix(width, height) {
    minValue = 0;
    maxValue = 255;
}


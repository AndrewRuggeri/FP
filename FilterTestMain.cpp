#include <iostream>

#include "ImageIO.h"
#include "Filter.h"
#include "FilterChain.h"


int main(int argc, char* argv[]) {
    std::cout << "Hello World" << std::endl;

    Image testimage = ImageRead::pgm("101_1.pgm");

    return 0;
}
#include <iostream>

#include "ImageIO.h"
#include "Filter.h"
#include "FilterChain.h"


int main(int argc, char* argv[]) {
    std::cout << "Hello World" << std::endl;

    Image testimage = ImageRead::pgm("101_1.pgm");

	    int8_t gaus[] = { 1,  4,  7,  4,  1,
	                      4, 16, 26, 16,  4,
	                      7, 26, 41, 26,  7,
	                      4, 16, 26, 16,  4,
	                      1,  4,  7,  4,  1};
	    Kernel KernelGaussBlur(5, 5);
	    KernelGaussBlur.setValue((uint8_t*)&gaus[0]);

		Matrix<int32_t> gasMtx5 = Filter::Convolution<int32_t, uint8_t>(testimage, KernelGaussBlur);
		ImageWrite::pgm<uint8_t>(Filter::Normalize<uint8_t, int32_t>(gasMtx5), "101_1Gaus5.pgm");


    return 0;
}
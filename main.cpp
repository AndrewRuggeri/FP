#include <iostream>
#include <limits>
#include "ImageIO.h"
#include "Filter.h"
#include "FilterChain.h"






int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    
    char* path = "101_1.pgm";
    Image testImage = ImageRead::pgm(path);
    

    
    int8_t emboss[] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
    Kernel KernelEmboss(3,3);
    KernelEmboss.setValue((uint8_t*)&emboss[0]);
    
    int8_t edge[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
    Kernel KernelEdge(3,3);
    KernelEdge.setValue((uint8_t*)&edge[0]);

//    int8_t gaus[] = { 1,  2,  1,
//                      2,  4,  2,
//                      1,  2,  1 };
//    Kernel KernelGaussBlur(3, 3);
//    KernelGaussBlur.setValue((uint8_t*)&gaus[0]);


//    int8_t gaus[] = { 1,  4,  7,  4,  1,
//                      4, 16, 26, 16,  4,
//                      7, 26, 41, 26,  7,
//                      4, 16, 26, 16,  4,
//                      1,  4,  7,  4,  1};
//    Kernel KernelGaussBlur(5, 5);
//    KernelGaussBlur.setValue((uint8_t*)&gaus[0]);

    int8_t inv[] = { -1 };
    Kernel KernelInvert(1, 1);
    KernelInvert.setValue((uint8_t*)&inv[0]);


    Matrix<uint8_t> finalNo = FilterChain::Unsharpen(testImage);
    ImageWrite::pgm(finalNo, "101_1_FINAL.pgm");


    
    std::cout << std::endl << "Et Fin." << std::endl;
    return 0;
}

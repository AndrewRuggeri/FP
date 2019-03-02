#include <iostream>
#include "Image.h"
#include "ImageIO.h"
#include "Convolution.h"



#include <limits>

// https://stackoverflow.com/questions/41452226/c-2d-convolution
// https://www.allaboutcircuits.com/technical-articles/two-dimensional-convolution-in-image-processing/
// http://songho.ca/dsp/convolution/convolution2d_example.html

// http://www.hjort.co/2015/12/evaluating-nbis-using-fvc2004-databases-part2.html

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    
    char* path = "101_1.pgm";
    Image testImage = ImageRead::pgm(path);
    
    
    
//     uint8_t image[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//     Image temp(3,3);
//     temp.setValue(&image[0]);
//     
//     int8_t kenel[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
//     Kernel krn(3,3);
//     krn.setValue((uint8_t*)&kenel[0]);
//     
    
    int8_t emboss[] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
    Kernel KernelEmboss(3,3);
    KernelEmboss.setValue((uint8_t*)&emboss[0]);
    
    int8_t edge[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
    Kernel KernelEdge(3,3);
    KernelEdge.setValue((uint8_t*)&edge[0]);

    int8_t gaus[] = { 1,  2,  1,
                      2,  4,  2,
                      1,  2,  1 };
    Kernel KernelGaussBlur(3, 3);
    KernelGaussBlur.setValue((uint8_t*)&gaus[0]);

    int8_t inv[] = { -1 };
    Kernel KernelInvert(1, 1);
    KernelInvert.setValue((uint8_t*)&inv[0]);



    Matrix<int16_t> blur = Convolution::Convolution<int16_t>(testImage, KernelGaussBlur);
    Matrix<uint8_t> blurNo = Convolution::Normalize<uint8_t, int16_t>(blur);
    ImageWrite::pgm(blurNo, "101_1_BLUR.pgm");


    Matrix<int16_t> sub = Convolution::Subtract<int16_t, uint8_t, uint8_t>(testImage, blurNo);

    Matrix<uint8_t> subNo = Convolution::Normalize<uint8_t, int16_t>(sub);
    ImageWrite::pgm(subNo, "101_1_SUB.pgm");


    Matrix<uint16_t> final = Convolution::Add<uint16_t, uint8_t, int16_t>(testImage, sub);
    Matrix<uint8_t> FinalNo = Convolution::Normalize<uint8_t, uint16_t>(final);
    ImageWrite::pgm(FinalNo, "101_1_FINAL.pgm");


    
    std::cout << std::endl << "Et Fin." << std::endl;
    return 0;
}

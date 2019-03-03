#ifndef FP_FILTERCHAIN_H
#define FP_FILTERCHAIN_H

#include "Filter.h"


namespace FilterChain {


    Matrix<uint8_t> Unsharpen(Image image);

}


Matrix<uint8_t> FilterChain::Unsharpen(Image image) {


    // TODO: remove kernel
    int8_t gaus[] = { 1,  2,  1,
                      2,  4,  2,
                      1,  2,  1 };
    Kernel KernelGaussBlur(3, 3);
    KernelGaussBlur.setValue((uint8_t*)&gaus[0]);



    Matrix<uint8_t> median = Filter::Median<uint8_t>(image);

    Matrix<int32_t> blur = Filter::Convolution<int32_t>(median, KernelGaussBlur);
    Matrix<uint8_t> blurNo = Filter::Normalize<uint8_t, int32_t>(blur);

    Matrix<int16_t> sub = Filter::Subtract<int16_t, uint8_t, uint8_t>(image, blurNo);


    int16_t min = std::numeric_limits<int16_t>::min();
    Matrix<int16_t> final = Filter::Add<int16_t, uint8_t, int16_t>(image, sub, -32768, 255); // from -(2^15) to (2^8)
    return Filter::Normalize<uint8_t, int16_t>(final);

}




#endif //FP_FILTERCHAIN_H

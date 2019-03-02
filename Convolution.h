#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <iostream>
#include <limits>
#include "Matrix.h"
#include "Kernel.h"
#include "Image.h"


namespace Convolution {

template <class T>
Matrix<T> Convolution(Image img, Kernel kernel);

template <class N, class T>
Matrix<N> Normalize(Matrix<T> matrix);

template <class N, class T, class S>
Matrix<N> Subtract(Matrix<T> matrix1, Matrix<S> matrix2);

template <class N, class T, class S>
Matrix<N> Add(Matrix<T> matrix1, Matrix<S> matrix2);
};

template <class T>
Matrix<T> Convolution::Convolution(Image img, Kernel kernel) {

	uint32_t height = img.getHeight();
	uint32_t width = img.getWidth();

	uint32_t imageIndex = 0;
	Matrix<T> convMatrix(width, height);
	T* outputData = convMatrix.getData();
	T maxValue = 0;
	T minValue = 0;


	// find center position of kernel (half of kernel size)
	uint32_t kernHeight = kernel.getHeight();
	uint32_t kernWidth  = kernel.getWidth();

	uint32_t kernCenterX = kernWidth / 2;
	uint32_t kernCenterY = kernHeight / 2;

	for (uint32_t imgY = 0; imgY < height; ++imgY)          // columns
	{
		for (uint32_t imgX = 0; imgX < width; ++imgX)       // rows
		{
            
            for (uint32_t kernY = 0; kernY < kernHeight; ++kernY) // kernel columns
			{
                uint32_t nn = kernHeight - 1 - kernY;  // column index of flipped kernel
				

				for (uint32_t kernX = 0; kernX < kernWidth; ++kernX)
				{
					int32_t mm = kernWidth - 1 - kernX;      // row index of flipped kernel

					int32_t ii = imgX + (kernCenterX - mm);
					int32_t jj = imgY + (kernCenterY - nn);

					// ignore input samples which are out of bound
					if (ii >= 0 && ii < width && jj >= 0 && jj < height) {
                        
						int32_t testValue = img.getValue(ii, jj) * kernel.getValue(mm, nn);

						outputData[imageIndex] += testValue;
					}
				}
			}
			// Detect potentail max an dmin
			if (minValue > outputData[imageIndex])
				minValue = outputData[imageIndex];
			if (maxValue < outputData[imageIndex])
				maxValue = outputData[imageIndex];

			imageIndex++;
		}
	}

	// set max and min values
	convMatrix.setMin(minValue);
	convMatrix.setMax(maxValue);


	return convMatrix;
}

template<class N, class T>
Matrix<N> Convolution::Normalize(Matrix<T> matrix) {
    int32_t normMin = std::numeric_limits<N>::min();
    int32_t normMax = std::numeric_limits<N>::max();
    int32_t normRange = normMax - normMin;
    
    
    T inMax = matrix.getMax();
    T inMin = matrix.getMin();
    int32_t inRange = inMax - inMin;
    
    float adjValue = (float)normRange/(float)inRange;
    uint32_t shiftValue = normMin - inMin;
    
    
    Matrix<N> norm(matrix.getWidth(), matrix.getHeight());
    
    T* inputData = (T*)matrix.getData();
    N* outputData = (N*)norm.getData();
    
    uint32_t size = matrix.getHeight() * matrix.getWidth();
    
    for(int i = 0; i < size; i++) {
        outputData[i] = (inputData[i] + shiftValue) * adjValue;
    }
    
    
    return norm;
}


template <class N, class T, class S>
Matrix<N> Convolution::Subtract(Matrix<T> matrix1, Matrix<S> matrix2) {
    
    if(matrix1.getHeight() != matrix2.getHeight()) {
        return Matrix<N>(0,0);
    }
    
    if(matrix1.getWidth() != matrix2.getWidth()) {
        return Matrix<N>(0,0);
    }    
    
    
    Matrix<N> output(matrix1.getWidth(), matrix1.getHeight());

    N* outputData = output.getData();
    T* m1Data = matrix1.getData();
    S* m2Data = matrix2.getData();

    N max = 0;
    N min = 0;

    uint32_t size = matrix1.getWidth() * matrix1.getHeight();
    for (int i = 0; i < size; i++) {
        outputData[i] = m1Data[i] - m2Data[i];

        // Get max and min
        if (outputData[i] > max)
            max = outputData[i];
        if (outputData[i] < min)
            min = outputData[i];
    }

    output.setMin(min);
    output.setMax(max);
    return output;
}


template <class N, class T, class S>
Matrix<N> Convolution::Add(Matrix<T> matrix1, Matrix<S> matrix2) {

    if (matrix1.getHeight() != matrix2.getHeight()) {
        return Matrix<N>(0, 0);
    }

    if (matrix1.getWidth() != matrix2.getWidth()) {
        return Matrix<N>(0, 0);
    }


    Matrix<N> output(matrix1.getWidth(), matrix1.getHeight());

    N* outputData = output.getData();
    T* m1Data = matrix1.getData();
    S* m2Data = matrix2.getData();


    N max = 0;
    N min = 0;

    uint32_t size = matrix1.getWidth() * matrix1.getHeight();
    for (int i = 0; i < size; i++) {
        outputData[i] = m1Data[i] + m2Data[i];

        // Get max and min
        if (outputData[i] > max)
            max = outputData[i];
        if (outputData[i] < min)
            min = outputData[i];
    }

    output.setMin(min);
    output.setMax(max);
    return output;
}



#endif

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "Matrix.h"
#include "Kernel.h"
#include "Image.h"


namespace Filter {

	template <class N, class T>
	Matrix<N> Convolution(Matrix<T> img, Kernel kernel);

	template<class T>
	Matrix<T> Median(Matrix<T> matrix);

	template <class N, class T>
	Matrix<N> Normalize(Matrix<T> matrix);


	template <class N, class T, class S>
	Matrix<N> Subtract(Matrix<T> matrix1, Matrix<S> matrix2);

	template <class N, class T, class S>
	Matrix<N> Subtract(Matrix<T> matrix1, Matrix<S> matrix2, N minValue, N maxValue);



	template <class N, class T, class S>
	Matrix<N> Add(Matrix<T> matrix1, Matrix<S> matrix2);


	template <class N, class T, class S>
	Matrix<N> Add(Matrix<T> matrix1, Matrix<S> matrix2, N minValue, N maxValue);

};

template <class N, class T>
Matrix<N> Filter::Convolution(Matrix<T> img, Kernel kernel) {

	uint32_t height = img.getHeight();
	uint32_t width = img.getWidth();

	uint32_t imageIndex = 0;
	Matrix<N> convMatrix(width, height);
	N* outputData = convMatrix.getData();
	N maxValue = 0;
	N minValue = 0;


	// find center position of kernel (half of kernel size)
	uint32_t kernHeight = kernel.getHeight();
	uint32_t kernWidth = kernel.getWidth();

	uint32_t kernCenterX = kernWidth / 2;
	uint32_t kernCenterY = kernHeight / 2;

	for (uint32_t imgY = 0; imgY < height; ++imgY)          // columns
	{
		for (uint32_t imgX = 0; imgX < width; ++imgX)       // rows
		{

			for (uint32_t kernY = 0; kernY < kernHeight; ++kernY) // kernel columns
			{
				uint32_t nn = kernHeight - 1 - kernY;  // column index of flipped kernel


				for (uint32_t kernX = 0; kernX < kernWidth; ++kernX) {
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
			// Detect max and min
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


template<class T>
Matrix<T> Filter::Median(Matrix<T> matrix) {

	int32_t width = matrix.getWidth();
	int32_t height = matrix.getHeight();

	Matrix<T> median(width, height);
	T min = std::numeric_limits<T>::max();
	T max = std::numeric_limits<T>::min();
	T* medianData = median.getData();

	int32_t pos = 0;
	std::vector<T> list;
	list.resize(9);
	int listIndex = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			listIndex = 0;

			// Shift around the Window [3x3] from -1 <> 1
			for (int wx = -1; wx <= 1; wx++) {
				for (int wy = -1; wy <= 1; wy++) {
					int xNeig = x + wx; // Get the X Neighbor
					int yNeig = y + wy; // Get the Y Neighbor

					if (xNeig >= 0 && xNeig < matrix.getWidth() &&
						yNeig >= 0 && yNeig < matrix.getHeight()) {
						list[listIndex] = matrix.getValue(xNeig, yNeig);
						listIndex++;
					}

				}
			}

			std::sort(list.begin(), list.begin() + (listIndex - 1));


			// Not a *true* median but ok, and fast.
			if (listIndex > 4)
				medianData[pos] = list[4];
			else
				medianData[pos] = list[3];

			// Get max and min
			if (medianData[pos] > max)
				max = medianData[pos];
			if (medianData[pos] < min)
				min = medianData[pos];

			pos++;
		}
	}

	median.setMin(min);
	median.setMax(max);

	return median;
}


template<class N, class T>
Matrix<N> Filter::Normalize(Matrix<T> matrix) {
	int32_t normMin = std::numeric_limits<N>::min();
	int32_t normMax = std::numeric_limits<N>::max();
	int32_t normRange = normMax - normMin;


	T inMax = matrix.getMax();
	T inMin = matrix.getMin();
	int32_t inRange = inMax - inMin;

	float adjValue = (float)normRange / (float)inRange;
	uint32_t shiftValue = normMin - inMin;


	Matrix<N> norm(matrix.getWidth(), matrix.getHeight());
	norm.setMin(normMin);
	norm.setMax(normMax);

	T* inputData = (T*)matrix.getData();
	N* outputData = (N*)norm.getData();

	uint32_t size = matrix.getHeight() * matrix.getWidth();

	for (int i = 0; i < size; i++) {
		outputData[i] = (inputData[i] + shiftValue) * adjValue;
	}


	return norm;
}


template <class N, class T, class S>
Matrix<N> Filter::Subtract(Matrix<T> matrix1, Matrix<S> matrix2) {
	return Subtract<N, T, S>(matrix1, matrix2, std::numeric_limits<N>::min(), std::numeric_limits<N>::max());
}

template <class N, class T, class S>
Matrix<N> Filter::Subtract(Matrix<T> matrix1, Matrix<S> matrix2, N minValue, N maxValue) {

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

	N max = minValue;
	N min = maxValue;

	uint32_t size = matrix1.getWidth() * matrix1.getHeight();
	int32_t tempValue = 0;
	for (int i = 0; i < size; i++) {
		tempValue = m1Data[i] - m2Data[i];
		outputData[i] = tempValue;

		if (tempValue > maxValue)
			outputData[i] = maxValue;

		if (tempValue < minValue)
			outputData[i] = minValue;

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
Matrix<N> Filter::Add(Matrix<T> matrix1, Matrix<S> matrix2) {
	return Add<N, T, S>(matrix1, matrix2, std::numeric_limits<N>::min(), std::numeric_limits<N>::max());
}

template <class N, class T, class S>
Matrix<N> Filter::Add(Matrix<T> matrix1, Matrix<S> matrix2, N minValue, N maxValue) {
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

	N max = minValue;
	N min = maxValue;

	uint32_t size = matrix1.getWidth() * matrix1.getHeight();
	int32_t tempValue = 0;
	for (int i = 0; i < size; i++) {
		tempValue = m1Data[i] + m2Data[i];
		outputData[i] = tempValue;

		if (tempValue > maxValue)
			outputData[i] = maxValue;

		if (tempValue < minValue)
			outputData[i] = minValue;

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

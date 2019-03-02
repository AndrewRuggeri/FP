#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <stddef.h>
#include <string.h>
#include "log.h"

// forward Declare Matrix to deal with << override
template<class T> class Matrix;
template<class T> std::ostream& operator<< (std::ostream& ostr, const Matrix<T>& matrix);



template <class T>
class Matrix {
    
public:
    
    /**
    * @brief Matrix class constructor, will allocate memory for data.
    * 
    * @param height_ height of matrix, in units of fieldSize
    * @param width_ width of matrix, in units of fieldSize
    * @param fieldSize field size in bytes, default 1
    */
    Matrix(uint32_t height_, uint32_t width_);
    
    
    /**
    * @brief returns the current size of the height of the matrix
    * 
    * @return uint32_t height of the matrix
    */
    uint32_t getHeight() { return height; }
    
    
    /**
    * @brief returns the current size of the width of the matrix
    * 
    * @return uint32_t width of the matrix
    */
    uint32_t getWidth() { return width; }
    
    
    /**
    * @brief return value at provided location
    * 
    * @param x column/width value
    * @param y row/height value
	* @param success true if data found, false if data not found
    * @return uint8_t returned valued at requested position
    */
    T getValue(uint32_t x, uint32_t y, bool* success);


	T getMin() { return minValue; }

	void setMin(T min) { minValue = min; }

	T getMax() { return maxValue; }

	void setMax(T max) { maxValue = max; }


	/**
	* @brief return value at provided location
	*
	* @param x column/width value
	* @param y row/height value
	* @return uint8_t returned valued at requested position
	*/
	T getValue(uint32_t x, uint32_t y);
    
    // Added for testing, should be removed, bad idea.
    void setValue(uint8_t* newData);

	// Bad idea department
	T* getData();
    


	friend std::ostream& operator<< <>(std::ostream& ostr, const Matrix& matrix);
    
protected:
    uint8_t* data;
    size_t dataSize = 0;
    
    uint32_t height = 0;
    uint32_t width = 0;
    
	// Max and Minimium values found within matrix;
	T maxValue = 0;
	T minValue = 0;
private:
    
};


// Template Source

template <class T>
Matrix<T>::Matrix(uint32_t width_, uint32_t height_) {
	this->height = height_;
	this->width = width_;


	dataSize = height * width * sizeof(T);

	// Allocate memory for data
	data = (uint8_t*)malloc(dataSize);
	if (data == nullptr) {
		logging::error("nullpointer retured from malloc");
	}

	// init data to 0
	memset(data, 0, dataSize);
}

template <class T>
T Matrix<T>::getValue(uint32_t x, uint32_t y, bool* success) {
	T value = 0;
	*success = false;

	uint32_t pos = (y * width) + x;
	T* tempDataPtr = (T*)data;

	if (pos < dataSize) {
		value = tempDataPtr[pos];
		*success = true;
	} else {
        char line[128] = {0};
        snprintf(line, 128, "pos: X %d, Y %d = %d, of datasize %d", x, y, pos, dataSize);
		std::cout << "X: " << width << ", Y: " << height << "  " ;
		logging::warning(line);
	}

	return value;
}


template <class T>
T Matrix<T>::getValue(uint32_t x, uint32_t y) {
	bool temp;
	return getValue(x, y, &temp);
}



template <class T>
void Matrix<T>::setValue(uint8_t* newData) {
	memcpy(data, newData, dataSize);
}

template<class T>
inline T * Matrix<T>::getData() {
	return (T*)data;
}





template <class T>
std::ostream& operator<< (std::ostream & ostr, const Matrix<T>& matrix) {
	ostr << "Max: " << matrix.maxValue << ", Min: " << matrix.minValue << "\n"
	     << "Height: " << matrix.height << ", Width: " << matrix.width << "\n";
	// call me old fashion but, printf() is just much easier
	uint32_t index = 0;
	T* typePointer = (T*)matrix.data;
	for (uint32_t y = 0; y < matrix.height; y++) {
		for (uint32_t x = 0; x < matrix.width; x++) {
			std::cout << " " << std::setw(4) << +typePointer[index++];
		}
		std::cout << std::endl; // force buffer clear, in event of bad things happening
	}
	return ostr;
}






#endif

#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <stdio.h>
#include <string>
#include "Image.h"


namespace ImageRead {
    
    /**
    * @brief Read file in pgm formate in as Image type
    * 
    * @param path directory path to file
    * @return Image Image returned, will be empty image if error
    */
    Image pgm(const char* path);
};


namespace ImageWrite {
    
    template <class T>
    void pgm(Matrix<T> matrix, char* path);
    
    //void pgm(Image image, char* path);
};


template <class T>
void ImageWrite::pgm(Matrix<T> matrix, char* path) {
    FILE* file;
    
    file = fopen(path, "wb");
    
    fprintf(file, "P5 ");
    fprintf(file, "%d %d 255 ", matrix.getWidth(), matrix.getHeight());
    
    long size = matrix.getHeight() * matrix.getWidth();
    fwrite(matrix.getData(), 1, size, file);
    
    fclose(file);
}



#endif

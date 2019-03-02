#ifndef IMAGE_H
#define IMAGE_H

#include "Matrix.h"

class Image : public Matrix<uint8_t> {

public:
    Image(uint32_t width, uint32_t height);
    
protected:

private:
    
};


#endif

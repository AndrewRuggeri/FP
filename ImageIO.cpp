#include <stdio.h>
#include <string.h>
#include "log.h"
#include "ImageIO.h"

#define FILE_IMAGE_SIZE (204800)             // size in bytes 200KB
uint8_t imageFileData[FILE_IMAGE_SIZE];      // pre-allocate 200KB of memory



Image ImageRead::pgm(const char* path) {
    FILE* file;
    
    // Open file
    file = fopen(path, "r");
    if(file == nullptr) {
        LOG_ERROR("Failed to open file");
        return Image(0,0);
    }
    
    
    char version[3]; // Should be "P5" = 255 range
    int32_t height = 0;
    int32_t width = 0;
    int32_t maxLevel = 0;
    
    
    fgets(version, 3, file);
    fscanf(file, "%d", &width);
    fscanf(file, "%d", &height);
    fscanf(file, "%d", &maxLevel);

    // offset to the data part of the file
    long int dataPosition = ftell(file) + 1;
    
    
    // Get File size
    // Go to file end, get end position for size/length
    ssize_t fileSize = 0;
    if(fseek(file, 0L, SEEK_END) == 0) {
        fileSize = ftell(file);
        if(fileSize == -1) {
            LOG_ERROR("Failed to find file end");
            return Image(0,0);
        }
        
        if(fileSize > FILE_IMAGE_SIZE) {
            LOG_ERROR("File Image buffer is not large enough");
            return Image(0,0);
            
        }
    }
    
    
    fseek(file, 0L, SEEK_SET);
    
    
    // Read in file
    size_t size = fread(imageFileData, 1, fileSize, file);
    if(ferror(file) != 0) {
        LOG_ERROR("Failed to read image");
        return Image(0,0);
    }
    
    
    fclose(file);
    
    
    Image pgmImage(width, height);
    uint8_t* imageData = pgmImage.getData();
    uint8_t* offsetDataPointer = imageFileData + dataPosition;
    memcpy(imageData, offsetDataPointer, (fileSize - dataPosition));
    
    
    return pgmImage;
}


//void ImageWrite::pgm(Image image, char* path) {
//
//    FILE* file;
//
//    file = fopen(path, "wb");
//
//    fprintf(file, "P5 ");
//    fprintf(file, "%d %d 255 ", image.getWidth(), image.getHeight());
//
//    long size = image.getHeight() * image.getWidth();
//    fwrite(image.getData(), 1, size, file);
//
//    fclose(file);
//
//}

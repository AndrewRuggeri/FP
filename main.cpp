#include <iostream>
#include <limits>
//#include <filesystem> C++ 17 not supported
#include <dirent.h>
#include <vector>
#include <string>
#include "ImageIO.h"
#include "Filter.h"
#include "FilterChain.h"





// TODO: fill in with text
void helpMessage() {
    std::cout << "yadda yadda" << std::endl;
}


std::vector<std::string> GetPGMfiles(char* path){
    std::vector<std::string> fileList;

    struct dirent* ent;
    DIR* dir = opendir(path);
    if(dir != nullptr) {
        while((ent = readdir(dir)) != nullptr){
            if(ent->d_type == DT_REG ) {
                std::string filePath(ent->d_name);
                if(filePath.compare(ent->d_namlen - 3, 3, "pgm") == 0)
                    fileList.push_back(filePath);

            }
        }
    } else {
        logging::error("failed to open directory");
    }

    return fileList;
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, world!" << std::endl;

    char* inputPath = nullptr;
    char* outputPath = nullptr;
    bool process = true;

    // Filter Arguments
    for(int i = 1; i < argc; i++) {
        std::cout << i << " " << argv[i] << std::endl;
        if(strcmp("-od", argv[i]) == 0) {
            outputPath = argv[++i];
            continue;
        }

        if(strcmp("-id", argv[i]) == 0) {
            inputPath = argv[++i];
            continue;
        }

        if(strcmp("-n", argv[i]) == 0) {
            process = false;
            continue;
        }
    }


    // check input path validity
    std::vector<std::string> fileList;
    if(inputPath != nullptr) {
        fileList = GetPGMfiles(inputPath);
    } else {
        helpMessage();
        return 1;
    }


    // check output path validity
    if(outputPath != nullptr) {

    } else {
        helpMessage();
        return 1;
    }

    // Process
    if(process) {
        for(auto file : fileList){
            std::string fileInputPath(inputPath);
            fileInputPath.append(file);
            Image image = ImageRead::pgm(fileInputPath.c_str());
        }
    }

    // writeout pgm files



//    char* path = "101_1.pgm";
//    Image testImage = ImageRead::pgm(path);
//
//
//
//    Matrix<uint8_t> finalNo = FilterChain::Unsharpen(testImage);
//    ImageWrite::pgm(finalNo, "101_1_FINAL.pgm");


    
    std::cout << std::endl << "Et Fin." << std::endl;
    return 0;
}

#include <iostream>
#include <limits>
//#include <filesystem> C++ 17 not supported
#include <dirent.h>
#include <vector>
#include <string>
#include "ImageIO.h"
#include "Filter.h"
#include "FilterChain.h"
#include "log.h"



void helpMessage() {
    std::cout << "Command line arguments" << std::endl;
    std::cout << std::endl;
    std::cout << " -in <dir>    : input file directory" << std::endl;
    std::cout << " -od <dir>    : output file directory" << std::endl;
    std::cout << " -n           : nominal IO test" << std::endl;
    std::cout << std::endl;
}


std::vector<std::string> GetPGMfiles(char* path){
    std::vector<std::string> fileList;

    struct dirent* ent;
    DIR* dir = opendir(path);
    if(dir != nullptr) {
        while((ent = readdir(dir)) != nullptr){
            if(ent->d_type == DT_REG ) {
                std::string filePath(ent->d_name);
                if(filePath.compare(strlen(ent->d_name) - 3, 3, "pgm") == 0)
                    fileList.push_back(filePath);

            }
        }
    } else {
        LOG_ERROR("failed to open directory");
    }

    return fileList;
}

int main(int argc, char* argv[]) {
    LOG_DEBUG("Hello world!");
    LOG_INFO("Fingerprint Enhancer!");

    char* inputPath = nullptr;
    char* outputPath = nullptr;
    bool process = true;

    // Filter Arguments
    for(int i = 1; i < argc; i++) {
        LOG_DEBUG( i << " " << argv[i]);
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

        if(strcmp("-h", argv[i]) == 0) {
            helpMessage();
            return 0;
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
    for(auto file : fileList){
        std::string fileInputPath(inputPath);
        fileInputPath.append(file);

        std::string fileOutputpath(outputPath);
        fileOutputpath.append(file);

        Image image = ImageRead::pgm(fileInputPath.c_str());

        // if we want to process all the images
        if(process) {
            Matrix<uint8_t> sharpen = FilterChain::Unsharpen(image);
            ImageWrite::pgm(sharpen, fileOutputpath.c_str());

        // else if we want a IO benchmark/baseline
        } else {
            ImageWrite::pgm(image, fileOutputpath.c_str());
        }
    }

    
    std::cout << std::endl << "Et Fin." << std::endl;
    return 0;
}

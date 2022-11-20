//
// Created by drosaca on 18/11/22.
//

#include "Error.h"
#include "Config.h"

Config::Config(const std::string &imagePath, int imageWidth, int imageHeight) {
    std::string outputPath;
    this->height = imageHeight;
    this->width = imageWidth;
    this->inputFile.assign(imagePath);
    if (!exists(this->inputFile)) {
        throw Error("Input File not found");
    }
    outputPath = this->inputFile.stem().string();
    this->outputFile.assign(outputPath + ".tif");
}


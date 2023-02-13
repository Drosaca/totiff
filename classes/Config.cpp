//
// Created by drosaca on 18/11/22.
//

#include "Error.h"
#include "Config.h"
#include "pathSolver.h"

Config::Config(const std::string &imagePath, int imageWidth, int imageHeight, ImageColorType color) {
    std::string outputPath;
    this->height = imageHeight;
    this->width = imageWidth;
    this->inputFiles = pathSolver::resolve(imagePath);
    this->color = color;
    //outputPath = this->inputFile.stem().string();
    //this->outputFile.assign(outputPath + ".tif");
}


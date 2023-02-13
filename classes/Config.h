//
// Created by drosaca on 18/11/22.
//

#ifndef TOTIFF_CONFIG_H
#define TOTIFF_CONFIG_H

#include <filesystem>
#include <vector>
#include "RawImage.h"

class Config {
public:
    Config(const std::string &imagePath, int imageWidth, int height, ImageColorType color = ImageColorType::MONO);
    std::vector<std::filesystem::path> inputFiles;
    std::filesystem::path outputDir = "";
    unsigned int height;
    ImageColorType color;
    unsigned int width;
};


#endif //TOTIFF_CONFIG_H

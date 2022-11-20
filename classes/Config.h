//
// Created by drosaca on 18/11/22.
//

#ifndef TOTIFF_CONFIG_H
#define TOTIFF_CONFIG_H

#include <filesystem>
#include <vector>

class Config {
public:
    Config(const std::string &imagePath, int imageWidth, int height);
    std::filesystem::path inputFile;
    std::filesystem::path outputFile;
    unsigned int height;
    unsigned int width;
};


#endif //TOTIFF_CONFIG_H

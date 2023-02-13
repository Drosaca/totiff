#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Config.h"
#include "RawImage.h"
#include "Tif.h"
#include "Error.h"


std::string getOutputFile(const Config &config, const std::string &inputFile) {
    std::filesystem::path inFile(inputFile);
    std::filesystem::path outputFile(inFile.stem().string());
    outputFile += ".tif";
    outputFile = inFile.parent_path() / outputFile;
    return outputFile.string();
}

void convert(const Config &config, const std::string &inputFile) {
    RawImage imsRgb(inputFile, config.width, config.height);
    if(config.color == ImageColorType::RGB) {
        imsRgb = imsRgb.toRGB();
    }
    std::vector<uint16_t> pixels = imsRgb.getPixels();
    Tif outputImage;
    outputImage.fromRaw(imsRgb);
    std::string outputPath = getOutputFile(config, inputFile);
    outputImage.write(outputPath);
    std::cout << outputPath << " written" << std::endl;
}


int main(int argc, char **argv) {
    if (argc < 4) {
        std::cout << "usage totiff path/to/img.ims_rgb width height [--rgb]" << std::endl;
        exit(0);
    }
    bool rgb = argc > 4 && std::string(argv[4]) == "--rgb";
    try {
        Config config(argv[1], std::stoi(argv[2]), std::stoi(argv[3]),
                      rgb ? ImageColorType::RGB : ImageColorType::MONO);
        for (const auto &file: config.inputFiles) {
            convert(config, file.string());
        }
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

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


void convert(const Config &config) {
    RawImage imsRgb(config.inputFile);
    std::vector<uint16_t> pixels = imsRgb.getPixels();
    Tif outputImage(config.width, config.height);
    outputImage.setPixels(pixels);
    outputImage.write(config.outputFile);

}

int main(int argc, char** argv) {
    if(argc != 4) {
        std::cout << "usage totiff path/to/img.ims_rgb width height" << std::endl;
        exit(0);
    }
    try {
        Config config(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
        convert(config);
    } catch (Error &e){
        std::cerr << e.what() << std::endl;
    }
}
